#include <gtest/gtest.h>
#include <atomic>
#include <cerrno>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <limits>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
typedef huobi_futures::linear_swap::restful::OrderClient OrderClient;
#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"
#include "huobi_futures/json_struct/json_struct.h"
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 trade + position 接口（私有，需 key）。
// 写操作用 SPX500-USDT 远价限价单（7300，市价≈7700）挂单后立即撤单，0 成交 0 损失。
// dual_side 模式下单必带 position_side。空数据接口用前置数据复测。

static const string V5_CONTRACT = "SPX500-USDT";
static const string V5_FAR_PRICE = "7300"; // 远低于市价（约 7700）的限价买单，挂单后立即撤销

// HTX V5 的 client_order_id 只接受数字；统一使用 7 位测试前缀 + 秒级时间戳 + 2 位序列。
// 19 位数字保持在 int64 范围内，且前缀可明确识别为测试创建。
static const string V5_TRADE_TEST_CLIENT_ID_PREFIX = "9090909";

// SDK 的 SwapTradePositionOpensResponse 把 lever_rate 声明成 string，但真实响应是数字，
// 有持仓时会导致解析失败。测试内用最小结构只取清理所需的字符串字段。
namespace
{
    struct V5OpenPositionItem
    {
        std::optional<std::string> contract_code;
        std::optional<std::string> position_side;
        std::optional<std::string> margin_mode;
        std::optional<std::string> volume;
        std::optional<std::string> available;

        JS_OBJ(contract_code, position_side, margin_mode, volume, available);
    };

    struct V5OpenPositionsResponse
    {
        std::optional<int32_t> code;
        std::optional<std::string> message;
        std::optional<std::vector<V5OpenPositionItem>> data;
        std::optional<int64_t> ts;

        JS_OBJ(code, message, data, ts);
    };
}

static string MakeTestTradeClientOrderId()
{
    static std::atomic<uint64_t> sequence{0};
    const auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    const string seq = std::to_string(100 + (sequence.fetch_add(1) % 100)).substr(1);
    return V5_TRADE_TEST_CLIENT_ID_PREFIX + std::to_string(now_seconds) + seq;
}

static bool IsTestTradeClientOrderId(const string &client_order_id)
{
    return client_order_id.size() == 19 &&
           client_order_id.rfind(V5_TRADE_TEST_CLIENT_ID_PREFIX, 0) == 0;
}

using V5PositionResponseFetcher = std::function<bool(V5OpenPositionsResponse &, string &)>;

// 严格解析非负金额：必须整串都是合法数字，拒绝空白、非有限值、负数和溢出。
static bool ParseStrictNonNegativeAmount(const string &text, double &value, string &error)
{
    if (text.empty())
    {
        error = "amount is empty";
        return false;
    }
    for (char ch : text)
    {
        const unsigned char byte = static_cast<unsigned char>(ch);
        if (std::isspace(byte))
        {
            error = "amount contains whitespace";
            return false;
        }
        if (!(std::isdigit(byte) || ch == '.' || ch == 'e' || ch == 'E' || ch == '+' || ch == '-'))
        {
            error = "amount contains invalid characters";
            return false;
        }
    }

    errno = 0;
    char *end = nullptr;
    const double parsed = std::strtod(text.c_str(), &end);
    if (end != text.c_str() + text.size())
    {
        error = "amount is not a complete number";
        return false;
    }
    if (errno == ERANGE)
    {
        error = "amount is out of range";
        return false;
    }
    if (!std::isfinite(parsed))
    {
        error = "amount is not finite";
        return false;
    }
    if (parsed < 0 || std::signbit(parsed))
    {
        error = "amount is negative";
        return false;
    }
    value = parsed;
    return true;
}

// 纯判定逻辑：data 必须存在；每行合约必须可识别，目标合约必须有合法方向和金额。
static bool EvaluateSpxLongVolume(const V5OpenPositionsResponse &response, double &long_volume,
                                  string &error)
{
    if (response.code.value_or(0) != 200)
    {
        error = "position query code=" + std::to_string(response.code.value_or(0)) +
                " message=" + response.message.value_or("");
        return false;
    }
    if (!response.data.has_value())
    {
        error = "position query response is missing data; cannot determine exposure";
        return false;
    }

    long_volume = 0;
    for (const auto &position : response.data.value())
    {
        if (!position.contract_code.has_value() || position.contract_code->empty())
        {
            error = "position row cannot be identified: missing contract_code";
            return false;
        }
        for (char ch : position.contract_code.value())
        {
            if (std::isspace(static_cast<unsigned char>(ch)))
            {
                error = "position row cannot be identified: invalid contract_code";
                return false;
            }
        }
        if (position.contract_code.value() != V5_CONTRACT) continue;

        if (!position.position_side.has_value() ||
            (position.position_side.value() != "long" &&
             position.position_side.value() != "short"))
        {
            error = "target position row has missing or invalid position_side";
            return false;
        }
        if (!position.volume.has_value())
        {
            error = "target position row is missing volume";
            return false;
        }

        double volume = 0;
        string parse_error;
        if (!ParseStrictNonNegativeAmount(position.volume.value(), volume, parse_error))
        {
            error = "target position row has invalid volume: " + parse_error;
            return false;
        }
        if (position.position_side.value() == "long")
        {
            long_volume += volume;
            if (!std::isfinite(long_volume))
            {
                error = "long volume sum is not finite";
                return false;
            }
        }
    }
    return true;
}

static bool ReadSpxLongVolumeWithFetcher(const V5PositionResponseFetcher &fetch,
                                         double &long_volume, string &error)
{
    V5OpenPositionsResponse response;
    if (!fetch(response, error)) return false;
    return EvaluateSpxLongVolume(response, long_volume, error);
}

// 读取 SPX500-USDT 多头持仓总量；不打印账户标识。
static bool ReadSpxLongVolume(double &long_volume, string &error)
{
    init_config();
    const V5PositionResponseFetcher fetch = [](V5OpenPositionsResponse &response, string &error) {
        huobi_futures::url_base::PrivateUrlBuilder builder(
            config["AccessKey"], config["SecretKey"], config["Host"]);
        map<string, string> params;
        const string url = builder.Build(
            "GET", huobi_futures::utils::V5_TRADE_POSITION_OPENS, params);
        auto r = huobi_futures::url_base::HttpRequest::Instance()
                     .Get<V5OpenPositionsResponse>(url);
        if (!r)
        {
            error = "position query returned no response";
            return false;
        }
        response = *r;
        return true;
    };
    return ReadSpxLongVolumeWithFetcher(fetch, long_volume, error);
}

static bool WaitForSpxLongVolume(double expected, double &observed, string &error,
                                 int attempts = 20)
{
    for (int attempt = 0; attempt < attempts; ++attempt)
    {
        if (!ReadSpxLongVolume(observed, error)) return false;
        if (std::fabs(observed - expected) < 1e-9) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    error = "timed out waiting for SPX500-USDT long volume " + std::to_string(expected) +
            ", observed " + std::to_string(observed);
    return false;
}

struct V5RestMarketFillAssessment
{
    bool confirmed = false;
    double volume = 0;
    string error;
};

// 只按本测试的 client_order_id/order_id 和终态成交信息确认归属与成交量。
static V5RestMarketFillAssessment EvaluateRestMarketFill(
    const GetTradeOrderResponse &response, const string &expected_client_order_id,
    const string &expected_order_id)
{
    V5RestMarketFillAssessment result;
    if (response.code.value_or(0) != 200)
    {
        result.error = "order query code=" + std::to_string(response.code.value_or(0)) +
                       " message=" + response.msg.value_or("");
        return result;
    }
    if (!response.data.has_value())
    {
        result.error = "order query response is missing data";
        return result;
    }

    const auto &order = response.data.value();
    if (!order.client_order_id.has_value() ||
        order.client_order_id.value() != expected_client_order_id)
    {
        result.error = "client_order_id mismatch";
        return result;
    }
    if (!expected_order_id.empty() &&
        (!order.order_id.has_value() || order.order_id.value() != expected_order_id))
    {
        result.error = "order_id mismatch";
        return result;
    }
    if (!order.contract_code.has_value() || order.contract_code.value() != V5_CONTRACT)
    {
        result.error = "contract_code mismatch";
        return result;
    }
    if (!order.side.has_value() || order.side.value() != "buy")
    {
        result.error = "order side mismatch";
        return result;
    }
    if (!order.position_side.has_value() || order.position_side.value() != "long")
    {
        result.error = "order position_side mismatch";
        return result;
    }
    if (!order.state.has_value())
    {
        result.error = "order state is missing";
        return result;
    }

    const string state = order.state.value();
    if (state == "new" || state == "partial_filled")
    {
        result.error = "order is not terminal yet (state=" + state + ")";
        return result;
    }
    if (state != "filled" && state != "canceled" && state != "rejected")
    {
        result.error = "unknown order state=" + state;
        return result;
    }
    if (!order.volume.has_value())
    {
        result.error = "order volume is missing";
        return result;
    }

    double order_volume = 0;
    string parse_error;
    if (!ParseStrictNonNegativeAmount(order.volume.value(), order_volume, parse_error))
    {
        result.error = "order volume is invalid: " + parse_error;
        return result;
    }
    if (order_volume > 1.0)
    {
        result.error = "order volume exceeds the 1-contract test cap";
        return result;
    }
    if (!order.trade_volume.has_value())
    {
        result.error = "trade_volume is missing";
        return result;
    }

    double fill_volume = 0;
    if (!ParseStrictNonNegativeAmount(order.trade_volume.value(), fill_volume, parse_error))
    {
        result.error = "trade_volume is invalid: " + parse_error;
        return result;
    }
    if (fill_volume > 1.0)
    {
        result.error = "confirmed fill exceeds the 1-contract test cap";
        return result;
    }
    if (fill_volume > order_volume)
    {
        result.error = "confirmed fill exceeds order volume";
        return result;
    }
    if (state == "filled" && fill_volume <= 0)
    {
        result.error = "filled order has zero trade_volume";
        return result;
    }

    result.confirmed = true;
    result.volume = fill_volume;
    return result;
}

static string FormatRestVolume(double volume)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(16) << volume;
    string text = out.str();
    while (!text.empty() && text.back() == '0') text.pop_back();
    if (!text.empty() && text.back() == '.') text.pop_back();
    if (text.empty()) text = "0";
    return text;
}

static bool IsSafeRestFillVolume(double volume)
{
    return std::isfinite(volume) && volume > 0 && volume <= 1.0;
}

// 有界查询本测试订单，确认终态和成交数量；不读取聚合持仓来推断归属。
static bool ConfirmRestMarketFill(OrderClient &client, const string &client_order_id,
                                  const string &order_id, double &fill_volume,
                                  string &error)
{
    string last_error;
    for (int attempt = 0; attempt < 10; ++attempt)
    {
        auto order = client.GetTradeOrder(V5_CONTRACT, "cross", order_id, client_order_id);
        if (!order)
        {
            last_error = "order query returned no response";
        }
        else
        {
            const V5RestMarketFillAssessment assessment =
                EvaluateRestMarketFill(*order, client_order_id, order_id);
            if (assessment.confirmed)
            {
                fill_volume = assessment.volume;
                return true;
            }
            last_error = assessment.error;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    error = "could not establish fill for test-owned client_order_id/order_id: " +
            last_error;
    return false;
}

// 只按已确认的成交量平仓，严格 <= 1 张；不根据账户仓位推断归属。
static bool CloseConfirmedSpxLongExposure(OrderClient &client, double volume,
                                          string &error)
{
    if (volume <= 0) return true;
    if (!IsSafeRestFillVolume(volume))
    {
        error = "refusing to close a non-finite or over-1-contract confirmed fill";
        return false;
    }

    const string client_order_id = MakeTestTradeClientOrderId();
    const string volume_text = FormatRestVolume(volume);
    auto close = client.TradeOrder(V5_CONTRACT, "cross", "long", "sell", "market", "",
                                   client_order_id, "", volume_text, "1", "", "", "", "", "",
                                   "", "", "", "", "", "");
    const int close_code = close ? close->code.value_or(0) : -1;

    double observed = 0;
    string verify_error;
    if (!WaitForSpxLongVolume(0.0, observed, verify_error, 20))
    {
        error = "reduce-only close submitted (code=" + std::to_string(close_code) +
                ") but position verification failed: " + verify_error;
        return false;
    }
    return true;
}

// 辅助：挂一个远价限价单，返回 order_id（供后续撤单/查询）
static string PlaceFarOrder(OrderClient &client, const string &position_side = "long")
{
    auto r = client.TradeOrder(V5_CONTRACT, "cross", position_side, "buy", "limit", "",
                               "", V5_FAR_PRICE, "1", "", "", "", "", "", "", "", "",
                               "", "", "", "");
    EXPECT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    // order_id 在 data 里
    if (r->data.has_value())
    {
        return r->data->order_id;
    }
    return "";
}

TEST(V5Trade, TradeOrderFarPrice)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradeOrder(V5_CONTRACT, "cross", "long", "buy", "limit", "",
                               "", V5_FAR_PRICE, "1", "", "", "", "", "", "", "", "",
                               "", "", "", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    // 挂单成功后立即撤单
    string oid = r->data.has_value() ? r->data->order_id : "";
    if (!oid.empty())
    {
        auto c = client.CancelTradeOrder(V5_CONTRACT, oid, "");
        EXPECT_EQ(c->code.value_or(0), 200);
    }
}

// #8 POST /v5/trade/batch_orders - 批量下单（Java 权威：SPX500 远价单，挂后即撤）
TEST(V5Trade, TradeBatchOrders)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradeBatchOrders(V5_CONTRACT, "cross", "long", "buy", "limit", "",
                                    "", V5_FAR_PRICE, "1", "", "", "", "", "", "", "",
                                    "", "", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data != nullptr);
    ASSERT_FALSE(r->data->empty());
    string oid = r->data->at(0).order_id.value_or("");
    EXPECT_FALSE(oid.empty());
    // 挂单成功后立即撤单
    if (!oid.empty())
    {
        auto c = client.CancelTradeOrder(V5_CONTRACT, oid, "");
        EXPECT_EQ(c->code.value_or(0), 200);
    }
}

// #10 POST /v5/trade/cancel_batch_orders - 批量撤单（前置挂单再撤）
TEST(V5Trade, CancelTradeBatchOrders)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    string oid = PlaceFarOrder(client);
    ASSERT_FALSE(oid.empty()) << "前置挂单失败";
    auto r = client.CancelTradeBatchOrders(V5_CONTRACT, oid, "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data != nullptr);
    ASSERT_FALSE(r->data->empty());
    EXPECT_EQ(r->data->at(0).order_id.value_or(""), oid);
}

// #12 POST /v5/trade/position - 全平（Java 权威：无持仓时 1048，安全）
TEST(V5Trade, TradePosition)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradePosition(V5_CONTRACT, "cross", "long", "");
    ASSERT_NE(r, nullptr);
    int code = r->code.value_or(0);
    // 200=有持仓已平，1048=无持仓可平。两者皆接口可达+参数合法
    EXPECT_TRUE(code == 200 || code == 1048) << "code=" << code << " msg=" << r->message.value_or("");
}

// #13 POST /v5/trade/position_all - 一键全平（Java 权威：code=200，data 空数组合法）
TEST(V5Trade, TradePositionAll)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradePositionAll();
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

// #15 GET /v5/trade/order/details - 查询成交明细（Java 权威：市价买 1 张成交→查明细→平掉测试仓位）
TEST(V5Trade, TradeOrderDetails)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);

    // 只有在 SPX500-USDT 没有既有 long 仓位时才交易，确保后续只平测试创建的 1 张。
    double baseline_long = 0;
    string error;
    ASSERT_TRUE(ReadSpxLongVolume(baseline_long, error)) << error;
    if (baseline_long > 0)
    {
        GTEST_SKIP() << "prerequisite not met: pre-existing SPX500-USDT long position; "
                        "refusing to trade because cleanup cannot be scoped safely";
    }

    const string client_order_id = MakeTestTradeClientOrderId();
    auto place = client.TradeOrder(V5_CONTRACT, "cross", "long", "buy", "market", "",
                                   client_order_id, "", "1", "", "", "", "", "", "", "", "",
                                   "", "", "", "");
    const string oid =
        (place && place->data.has_value()) ? place->data->order_id : "";

    // 归属与成交量只从本测试订单确认，不从聚合持仓推断。
    double fill_volume = 0;
    string confirm_error;
    const bool fill_confirmed =
        ConfirmRestMarketFill(client, client_order_id, oid, fill_volume, confirm_error);

    // 先按已确认成交量清理；清理独立于后续 TradeOrderDetails 查询。
    string cleanup_error;
    if (fill_confirmed)
    {
        if (fill_volume <= 0)
        {
            cleanup_error = "order confirmed zero fill; nothing was closed";
        }
        else if (!CloseConfirmedSpxLongExposure(client, fill_volume, cleanup_error))
        {
            // 保留 cleanup_error 供断言展示
        }
    }
    else
    {
        cleanup_error = "cleanup not attempted: fill could not be established; "
                        "residual risk, cleanup target was not widened";
    }

    // 必须在可能提前返回的 place 响应断言之前记录 residual risk。
    if (!fill_confirmed)
    {
        ADD_FAILURE() << "could not establish fill for this test order; residual risk, "
                         "cleanup not widened: "
                      << confirm_error;
    }

    // 保留 endpoint 断言；即使清理或查询失败，也不改变已确认成交量的清理范围。
    std::shared_ptr<GetOrderTradesResponse> r;
    const string detail_order_id = !oid.empty() ? oid : "";
    const string detail_client_order_id = oid.empty() ? client_order_id : "";
    if (!detail_order_id.empty() || !detail_client_order_id.empty())
    {
        r = client.TradeOrderDetails(V5_CONTRACT, detail_order_id, detail_client_order_id,
                                     "", "", "", "", "");
        for (int attempt = 0; attempt < 10 && (!r || !r->data || r->data->empty()); ++attempt)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            r = client.TradeOrderDetails(V5_CONTRACT, detail_order_id,
                                         detail_client_order_id, "", "", "", "", "");
        }
    }

    ASSERT_NE(place, nullptr);
    EXPECT_EQ(place->code.value_or(0), 200);
    ASSERT_TRUE(place->data.has_value());
    ASSERT_FALSE(place->data->order_id.empty());
    EXPECT_GT(fill_volume, 0.0);
    EXPECT_TRUE(cleanup_error.empty()) << cleanup_error;
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data != nullptr);
    ASSERT_FALSE(r->data->empty());
    EXPECT_FALSE(r->data->at(0).trade_id.value_or("").empty());
    EXPECT_TRUE(IsTestTradeClientOrderId(client_order_id));
}

TEST(V5Trade, CancelAllOrders)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.CancelAllOrders(V5_CONTRACT, "buy", "long");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Trade, TradeCancelAfter)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // on_off=0 关闭自动撤单（空参接口 404，需显式 on_off）
    auto r = client.TradeCancelAfter("0", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Trade, TradeOrderOpens)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // 前置挂单再查当前委托
    string oid = PlaceFarOrder(client);
    auto r = client.TradeOrderOpens(V5_CONTRACT, "cross", "", "", "", "", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    if (!oid.empty())
    {
        client.CancelTradeOrder(V5_CONTRACT, oid, "");
    }
}

TEST(V5Trade, GetTradeOrder)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    string oid = PlaceFarOrder(client);
    if (!oid.empty())
    {
        auto r = client.GetTradeOrder(V5_CONTRACT, "cross", oid, "");
        ASSERT_NE(r, nullptr);
        EXPECT_EQ(r->code.value_or(0), 200);
        client.CancelTradeOrder(V5_CONTRACT, oid, "");
    }
}

TEST(V5Trade, TradeOrderHistory)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradeOrderHistory(V5_CONTRACT, "cross", "", "", "", "", "", "", "", "", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Trade, TradePositionOpens)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.TradePositionOpens(V5_CONTRACT);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

// V5 position 接口

TEST(V5Position, PositionLever)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.PositionLever(V5_CONTRACT, "cross", "long");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Position, SetPositionLever)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // Java 权威：BTC-USDT + isolated + lever 5（BTC 无挂单，可调杠杆；SPX500 有远价挂单会 1493）
    auto before = client.PositionLever("BTC-USDT", "isolated", "long");
    ASSERT_NE(before, nullptr);
    ASSERT_EQ(before->code.value_or(0), 200);
    ASSERT_TRUE(before->data.has_value());
    ASSERT_FALSE(before->data->empty());
    const string original_lever = before->data->front().lever_rate.value_or("");
    ASSERT_FALSE(original_lever.empty()) << "cannot read baseline leverage";

    auto r = client.SetPositionLever("BTC-USDT", "isolated", "5", "long");
    // 无论设置结果如何都恢复基线杠杆，避免改变账户既有设置。
    auto restore = client.SetPositionLever("BTC-USDT", "isolated", original_lever, "long");
    std::shared_ptr<PositionLeverResponse> verify;
    for (int attempt = 0; attempt < 10; ++attempt)
    {
        verify = client.PositionLever("BTC-USDT", "isolated", "long");
        if (verify && verify->code.value_or(0) == 200 && verify->data.has_value() &&
            !verify->data->empty() &&
            verify->data->front().lever_rate.value_or("") == original_lever)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_NE(restore, nullptr);
    EXPECT_EQ(restore->code.value_or(0), 200);
    ASSERT_NE(verify, nullptr);
    EXPECT_EQ(verify->code.value_or(0), 200);
    ASSERT_TRUE(verify->data.has_value());
    ASSERT_FALSE(verify->data->empty());
    EXPECT_EQ(verify->data->front().lever_rate.value_or(""), original_lever);
}

TEST(V5Position, PositionMode)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.PositionMode();
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

// #23 POST /v5/position/mode - 设置持仓模式（Java 权威：dual_side，幂等设当前值）
TEST(V5Position, SetPositionMode)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.SetPositionMode("dual_side");
    ASSERT_NE(r, nullptr);
    int code = r->code.value_or(0);
    // 200=成功（含已为该模式），1493=有挂单不许改。两者皆接口可达+签名正确
    EXPECT_TRUE(code == 200 || code == 1493) << "code=" << code << " msg=" << r->message.value_or("");
}

TEST(V5Position, PositionRiskLimit)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // Java 权威：contract_code=BTC-USDT，不传 margin_mode/position_side
    auto r = client.PositionRiskLimit("ETH-USDT", "cross", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Position, PositionRiskLimitTier)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // Java 权威：contract_code=BTC-USDT，不传 margin_mode
    auto r = client.PositionRiskLimitTier("ETH-USDT", "cross");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

// #26 POST /v5/position/margin - 调整逐仓保证金（Java 权威：仅 contract_code，弱验证接口可达）
// 无 isolated 持仓或缺 position_side 时 1067，属预期（证明接口可达+签名正确）
TEST(V5Position, PositionMargin)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.PositionMargin("BTC-USDT", "long", "1", "add");
    ASSERT_NE(r, nullptr);
    int code = r->code.value_or(0);
    // 200=成功（需有 isolated 持仓），1067/1042=无持仓/参数。接口可达+签名正确即通过
    EXPECT_NE(code, 0) << "code=" << code << " msg=" << r->message.value_or("");
    // 不强求 200：真实调整保证金需先开 isolated 仓，成本高且改变账户状态，对齐 Java 弱验证
}

// 回归保护：API code=200 但缺少 data 时无法确认仓位，必须 fail closed，不能当成空仓放行交易。
TEST(V5CleanupGuard, MissingPositionDataFailsClosed)
{
    const V5PositionResponseFetcher fetch = [](V5OpenPositionsResponse &response, string &) {
        response.code = 200;
        // 故意不设置 response.data：模拟服务端成功码但缺字段。
        return true;
    };

    double volume = 123.0;
    string error;
    EXPECT_FALSE(ReadSpxLongVolumeWithFetcher(fetch, volume, error));
    EXPECT_FALSE(error.empty());

    // data 存在且为空数组时才是可确认的空仓。
    const V5PositionResponseFetcher empty_fetch =
        [](V5OpenPositionsResponse &response, string &) {
            response.code = 200;
            response.data = std::vector<V5OpenPositionItem>{};
            return true;
        };
    volume = 123.0;
    error.clear();
    EXPECT_TRUE(ReadSpxLongVolumeWithFetcher(empty_fetch, volume, error));
    EXPECT_EQ(volume, 0.0);
    EXPECT_TRUE(error.empty());
}

TEST(V5CleanupGuard, PositionRowsFailClosedOnMissingOrInvalidFields)
{
    auto make_row = []() {
        V5OpenPositionItem row;
        row.contract_code = V5_CONTRACT;
        row.position_side = "long";
        row.volume = "1";
        return row;
    };
    auto expect_invalid = [](V5OpenPositionItem row, const char *label) {
        const V5PositionResponseFetcher fetch =
            [row](V5OpenPositionsResponse &response, string &) {
                response.code = 200;
                response.data = std::vector<V5OpenPositionItem>{row};
                return true;
            };
        double volume = 123.0;
        string error;
        EXPECT_FALSE(ReadSpxLongVolumeWithFetcher(fetch, volume, error)) << label;
        EXPECT_FALSE(error.empty()) << label;
    };

    V5OpenPositionItem row;
    row = make_row(); row.contract_code.reset(); expect_invalid(row, "missing contract_code");
    row = make_row(); row.contract_code = ""; expect_invalid(row, "empty contract_code");
    row = make_row(); row.contract_code = " SPX500-USDT"; expect_invalid(row, "whitespace contract_code");
    row = make_row(); row.position_side.reset(); expect_invalid(row, "missing position_side");
    row = make_row(); row.position_side = ""; expect_invalid(row, "empty position_side");
    row = make_row(); row.position_side = "both"; expect_invalid(row, "invalid position_side");
    row = make_row(); row.volume.reset(); expect_invalid(row, "missing volume");
    row = make_row(); row.volume = ""; expect_invalid(row, "empty volume");
    row = make_row(); row.volume = "1abc"; expect_invalid(row, "numeric prefix volume");
    row = make_row(); row.volume = "1,2"; expect_invalid(row, "comma volume");
    row = make_row(); row.volume = "nan"; expect_invalid(row, "nan volume");
    row = make_row(); row.volume = "inf"; expect_invalid(row, "inf volume");
    row = make_row(); row.volume = "-inf"; expect_invalid(row, "negative inf volume");
    row = make_row(); row.volume = "-1"; expect_invalid(row, "negative volume");
    row = make_row(); row.volume = "-0"; expect_invalid(row, "negative zero volume");
    row = make_row(); row.volume = "1e309"; expect_invalid(row, "overflow volume");
    row = make_row(); row.volume = "1e-9999"; expect_invalid(row, "underflow volume");
    row = make_row(); row.volume = " 1"; expect_invalid(row, "leading whitespace volume");
    row = make_row(); row.volume = "1 "; expect_invalid(row, "trailing whitespace volume");
}

TEST(V5CleanupGuard, PositionRowsAcceptConfirmedAmounts)
{
    auto expect_valid = [](V5OpenPositionsResponse response, double expected, const char *label) {
        const V5PositionResponseFetcher fetch =
            [response](V5OpenPositionsResponse &out, string &) {
                out = response;
                return true;
            };
        double volume = 123.0;
        string error;
        EXPECT_TRUE(ReadSpxLongVolumeWithFetcher(fetch, volume, error)) << label;
        EXPECT_DOUBLE_EQ(volume, expected) << label;
        EXPECT_TRUE(error.empty()) << label;
    };

    V5OpenPositionsResponse empty;
    empty.code = 200;
    empty.data = std::vector<V5OpenPositionItem>{};
    expect_valid(empty, 0.0, "present empty data");

    V5OpenPositionItem long_one;
    long_one.contract_code = V5_CONTRACT;
    long_one.position_side = "long";
    long_one.volume = "1";
    V5OpenPositionItem long_half;
    long_half.contract_code = V5_CONTRACT;
    long_half.position_side = "long";
    long_half.volume = "0.5";
    V5OpenPositionItem short_two;
    short_two.contract_code = V5_CONTRACT;
    short_two.position_side = "short";
    short_two.volume = "2";
    V5OpenPositionItem other_contract;
    other_contract.contract_code = "BTC-USDT";

    V5OpenPositionsResponse valid;
    valid.code = 200;
    valid.data = std::vector<V5OpenPositionItem>{long_one, long_half, short_two, other_contract};
    expect_valid(valid, 1.5, "valid long sum, short ignored, other contract skipped");
}

TEST(V5MarketFillGuard, ConfirmsOnlyOwnedTerminalFill)
{
    const string expected_client_order_id = "9090909000000000001";
    const string expected_order_id = "12345";

    auto make_order = []() {
        GetTradeOrderResponse response;
        response.code = 200;
        GetTradeOrderResponse::Data order;
        order.client_order_id = "9090909000000000001";
        order.order_id = "12345";
        order.contract_code = V5_CONTRACT;
        order.side = "buy";
        order.position_side = "long";
        order.state = "filled";
        order.volume = "1";
        order.trade_volume = "1";
        response.data = order;
        return response;
    };
    auto expect_unconfirmed = [&](GetTradeOrderResponse response, const char *label) {
        const V5RestMarketFillAssessment assessment =
            EvaluateRestMarketFill(response, expected_client_order_id, expected_order_id);
        EXPECT_FALSE(assessment.confirmed) << label;
        EXPECT_FALSE(assessment.error.empty()) << label;
    };

    const V5RestMarketFillAssessment confirmed =
        EvaluateRestMarketFill(make_order(), expected_client_order_id, expected_order_id);
    EXPECT_TRUE(confirmed.confirmed);
    EXPECT_DOUBLE_EQ(confirmed.volume, 1.0);
    EXPECT_TRUE(confirmed.error.empty());

    auto response = make_order();
    response.data.reset();
    expect_unconfirmed(response, "missing order data");

    response = make_order();
    response.data->client_order_id = "9090909000000000002";
    expect_unconfirmed(response, "client_order_id mismatch");

    response = make_order();
    response.data->client_order_id.reset();
    expect_unconfirmed(response, "missing client_order_id");

    response = make_order();
    response.data->order_id = "99999";
    expect_unconfirmed(response, "order_id mismatch");

    response = make_order();
    response.data->contract_code = "BTC-USDT";
    expect_unconfirmed(response, "contract mismatch");

    response = make_order();
    response.data->side = "sell";
    expect_unconfirmed(response, "side mismatch");

    response = make_order();
    response.data->position_side = "short";
    expect_unconfirmed(response, "position_side mismatch");

    response = make_order();
    response.data->state = "new";
    expect_unconfirmed(response, "new state");

    response = make_order();
    response.data->state = "partial_filled";
    expect_unconfirmed(response, "partial_filled state");

    response = make_order();
    response.data->state = "unknown";
    expect_unconfirmed(response, "unknown state");

    response = make_order();
    response.data->volume.reset();
    expect_unconfirmed(response, "missing order volume");

    response = make_order();
    response.data->volume = "2";
    expect_unconfirmed(response, "order volume over cap");

    response = make_order();
    response.data->trade_volume.reset();
    expect_unconfirmed(response, "missing trade_volume");

    for (const char *bad : {"nan", "inf", "1abc", "-1", "1e309", "1.5", " 1"})
    {
        response = make_order();
        response.data->trade_volume = bad;
        expect_unconfirmed(response, bad);
    }

    response = make_order();
    response.data->state = "filled";
    response.data->trade_volume = "0";
    expect_unconfirmed(response, "filled with zero fill");

    response = make_order();
    response.data->state = "canceled";
    response.data->trade_volume = "0";
    const V5RestMarketFillAssessment canceled =
        EvaluateRestMarketFill(response, expected_client_order_id, expected_order_id);
    EXPECT_TRUE(canceled.confirmed);
    EXPECT_DOUBLE_EQ(canceled.volume, 0.0);
    EXPECT_TRUE(canceled.error.empty());
}

TEST(V5MarketFillGuard, PartialFillAndCleanupScope)
{
    const string expected_client_order_id = "9090909000000000001";
    const string expected_order_id = "12345";

    GetTradeOrderResponse response;
    response.code = 200;
    GetTradeOrderResponse::Data order;
    order.client_order_id = expected_client_order_id;
    order.order_id = expected_order_id;
    order.contract_code = V5_CONTRACT;
    order.side = "buy";
    order.position_side = "long";
    order.state = "filled";
    order.volume = "1";
    order.trade_volume = "0.5";
    response.data = order;

    const V5RestMarketFillAssessment partial =
        EvaluateRestMarketFill(response, expected_client_order_id, expected_order_id);
    EXPECT_TRUE(partial.confirmed);
    EXPECT_DOUBLE_EQ(partial.volume, 0.5);
    EXPECT_TRUE(partial.error.empty());
    EXPECT_EQ(FormatRestVolume(partial.volume), "0.5");
    EXPECT_TRUE(IsSafeRestFillVolume(partial.volume));

    EXPECT_TRUE(IsSafeRestFillVolume(1.0));
    EXPECT_FALSE(IsSafeRestFillVolume(0.0));
    EXPECT_FALSE(IsSafeRestFillVolume(-1.0));
    EXPECT_FALSE(IsSafeRestFillVolume(1.0000001));
    EXPECT_FALSE(IsSafeRestFillVolume(2.0));
    EXPECT_FALSE(IsSafeRestFillVolume(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(IsSafeRestFillVolume(std::numeric_limits<double>::quiet_NaN()));
    EXPECT_EQ(FormatRestVolume(1.0), "1");
    EXPECT_EQ(FormatRestVolume(0.0), "0");
}
