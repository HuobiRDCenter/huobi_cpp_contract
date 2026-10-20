#pragma once
#include <gtest/gtest.h>
#include <glog/logging.h>

#include "config.hpp"
#include <thread>
#include <chrono>
#include <atomic>
#include <cerrno>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <limits>
#include <condition_variable>
#include <map>
#include <mutex>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "huobi_futures/linear_swap/ws/WSSwapNotificationClient.hpp"
typedef huobi_futures::linear_swap::ws::WSSwapNotificationClient WSSwapNotificationClient;

#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
typedef huobi_futures::linear_swap::restful::OrderClient OrderClient;
#include "huobi_futures/linear_swap/restful/AlgoClient.hpp"
typedef huobi_futures::linear_swap::restful::AlgoClient AlgoClient;
#include "huobi_futures/url_base/PrivateUrlBuilder.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"
#include "huobi_futures/utils/const_val.hpp"
#include "huobi_futures/json_struct/json_struct.h"

#include "huobi_futures/nlohmann_json/json.hpp"

// V5 推送测试（私有，需 key 鉴权）。
// 订阅 topic → 等 sub ack → REST 触发数据 → latch 等推送 → 断言必填字段。
// orders/algo_orders 用远价限价单/策略单（0 成交）；trade/positions/account/match_orders 用市价成交（成本极低）。

static const string V5_WS_CONTRACT = "SPX500-USDT";
static const string V5_WS_FAR_PRICE = "7300"; // 远低于市价的限价买单，不成交

// HTX V5 的 client_order_id 只接受数字；统一使用 7 位测试前缀 + 秒级时间戳 + 2 位序列。
// 19 位数字保持在 int64 范围内，且前缀可明确识别为测试创建。
static const string V5_WS_TEST_CLIENT_ID_PREFIX = "9090909";

namespace {
    // SDK 的 SwapTradePositionOpensResponse 把 lever_rate 声明成 string，但真实响应是数字，
    // 有持仓时会导致解析失败。测试内用最小结构只取清理所需的字符串字段。
    struct V5WSActivePositionItem
    {
        std::optional<std::string> contract_code;
        std::optional<std::string> position_side;
        std::optional<std::string> margin_mode;
        std::optional<std::string> volume;
        std::optional<std::string> available;

        JS_OBJ(contract_code, position_side, margin_mode, volume, available);
    };

    struct V5WSActivePositionsResponse
    {
        std::optional<int32_t> code;
        std::optional<std::string> message;
        std::optional<std::vector<V5WSActivePositionItem>> data;
        std::optional<int64_t> ts;

        JS_OBJ(code, message, data, ts);
    };

    std::string makeTestClientOrderId()
    {
        static std::atomic<uint64_t> sequence{0};
        const auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        const std::string seq = std::to_string(100 + (sequence.fetch_add(1) % 100)).substr(1);
        return V5_WS_TEST_CLIENT_ID_PREFIX + std::to_string(now_seconds) + seq;
    }

    bool isTestClientOrderId(const std::string &client_order_id)
    {
        return client_order_id.size() == 19 &&
               client_order_id.rfind(V5_WS_TEST_CLIENT_ID_PREFIX, 0) == 0;
    }

    using V5WSPositionResponseFetcher =
        std::function<bool(V5WSActivePositionsResponse &, std::string &)>;

    // 严格解析非负金额：必须整串都是合法数字，拒绝空白、非有限值、负数和溢出。
    bool parseStrictNonNegativeAmount(const std::string &text, double &value,
                                      std::string &error)
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
            if (!(std::isdigit(byte) || ch == '.' || ch == 'e' || ch == 'E' ||
                  ch == '+' || ch == '-'))
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
    bool evaluateSpxLongVolume(const V5WSActivePositionsResponse &response,
                               double &long_volume, std::string &error)
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
            if (position.contract_code.value() != V5_WS_CONTRACT) continue;

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
            std::string parse_error;
            if (!parseStrictNonNegativeAmount(position.volume.value(), volume, parse_error))
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

    bool readSpxLongVolumeWithFetcher(const V5WSPositionResponseFetcher &fetch,
                                      double &long_volume, std::string &error)
    {
        V5WSActivePositionsResponse response;
        if (!fetch(response, error)) return false;
        return evaluateSpxLongVolume(response, long_volume, error);
    }

    bool readSpxLongVolume(double &long_volume, std::string &error)
    {
        init_config();
        const V5WSPositionResponseFetcher fetch =
            [](V5WSActivePositionsResponse &response, std::string &error) {
                huobi_futures::url_base::PrivateUrlBuilder builder(
                    config["AccessKey"], config["SecretKey"], config["Host"]);
                map<string, string> params;
                const std::string url = builder.Build(
                    "GET", huobi_futures::utils::V5_TRADE_POSITION_OPENS, params);
                auto r = huobi_futures::url_base::HttpRequest::Instance()
                             .Get<V5WSActivePositionsResponse>(url);
                if (!r)
                {
                    error = "position query returned no response";
                    return false;
                }
                response = *r;
                return true;
            };
        return readSpxLongVolumeWithFetcher(fetch, long_volume, error);
    }

    bool waitForSpxLongVolume(double expected, double &observed, std::string &error,
                              int attempts = 20)
    {
        for (int attempt = 0; attempt < attempts; ++attempt)
        {
            if (!readSpxLongVolume(observed, error)) return false;
            if (std::fabs(observed - expected) < 1e-9) return true;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        error = "timed out waiting for SPX500-USDT long volume " + std::to_string(expected) +
                ", observed " + std::to_string(observed);
        return false;
    }

    bool spxLongBaselineFlat(std::string &reason)
    {
        double volume = 0;
        if (!readSpxLongVolume(volume, reason))
        {
            reason = "cannot read SPX500-USDT position state: " + reason;
            return false;
        }
        if (volume > 0)
        {
            reason = "pre-existing SPX500-USDT long position; refusing to trade because "
                     "cleanup cannot be scoped safely";
            return false;
        }
        return true;
    }

    struct WSMarketFillAssessment
    {
        bool confirmed = false;
        double volume = 0;
        std::string error;
    };

    // 只按本测试的 client_order_id/order_id 和终态成交信息确认归属与成交量。
    WSMarketFillAssessment evaluateMarketFill(const GetTradeOrderResponse &response,
                                              const std::string &expected_client_order_id,
                                              const std::string &expected_order_id)
    {
        WSMarketFillAssessment result;
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
        if (!order.contract_code.has_value() ||
            order.contract_code.value() != V5_WS_CONTRACT)
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

        const std::string state = order.state.value();
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
        std::string parse_error;
        if (!parseStrictNonNegativeAmount(order.volume.value(), order_volume, parse_error))
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
        if (!parseStrictNonNegativeAmount(order.trade_volume.value(), fill_volume, parse_error))
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

    std::string formatVolume(double volume)
    {
        std::ostringstream out;
        out << std::fixed << std::setprecision(16) << volume;
        std::string text = out.str();
        while (!text.empty() && text.back() == '0') text.pop_back();
        if (!text.empty() && text.back() == '.') text.pop_back();
        if (text.empty()) text = "0";
        return text;
    }

    bool isSafeConfirmedFillVolume(double volume)
    {
        return std::isfinite(volume) && volume > 0 && volume <= 1.0;
    }

    bool confirmMarketFill(OrderClient &client, const std::string &client_order_id,
                           const std::string &order_id, double &fill_volume,
                           std::string &error)
    {
        std::string last_error;
        for (int attempt = 0; attempt < 10; ++attempt)
        {
            auto order = client.GetTradeOrder(V5_WS_CONTRACT, "cross", order_id,
                                              client_order_id);
            if (!order)
            {
                last_error = "order query returned no response";
            }
            else
            {
                const WSMarketFillAssessment assessment =
                    evaluateMarketFill(*order, client_order_id, order_id);
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
    bool closeConfirmedSpxLongExposure(OrderClient &client, double volume,
                                       std::string &error)
    {
        if (volume <= 0) return true;
        if (!isSafeConfirmedFillVolume(volume))
        {
            error = "refusing to close a non-finite or over-1-contract confirmed fill";
            return false;
        }

        const std::string client_order_id = makeTestClientOrderId();
        const std::string volume_text = formatVolume(volume);
        auto close = client.TradeOrder(V5_WS_CONTRACT, "cross", "long", "sell", "market", "",
                                       client_order_id, "", volume_text, "1", "", "", "", "", "",
                                       "", "", "", "", "", "");
        const int close_code = close ? close->code.value_or(0) : -1;

        double observed = 0;
        std::string verify_error;
        if (!waitForSpxLongVolume(0.0, observed, verify_error, 20))
        {
            error = "reduce-only close submitted (code=" + std::to_string(close_code) +
                    ") but position verification failed: " + verify_error;
            return false;
        }
        return true;
    }

    // 识别订阅 ack（op:sub && err-code:0）
    bool isSubAck(const std::string &response) {
        try {
            auto msg = nlohmann::json::parse(response);
            if (msg.contains("op") && msg["op"].get<std::string>() == "sub" &&
                msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                return true;
            }
        } catch (...) {}
        return false;
    }

    // 校验推送数据必填字段。返回 true=有效数据帧（可 countDown），false=空快照应跳过。
    // err 非空表示字段缺失等错误（仍返回 true 让外层断言 errorMsg）。
    bool checkNotifyData(const std::string &topic, const std::string &response,
                         std::string &error) {
        try {
            auto msg = nlohmann::json::parse(response);
            if (!msg.contains("topic") || msg["topic"].get<std::string>() != topic) {
                error = topic + " topic mismatch: " + (msg.contains("topic") ? msg["topic"].get<std::string>() : "missing");
                return true;
            }
            if (!msg.contains("data") || msg["data"].is_null()) {
                return false; // 无 data 帧跳过
            }
            nlohmann::json d;
            if (msg["data"].is_array()) {
                auto arr = msg["data"];
                if (arr.empty()) return false; // 空快照跳过
                d = arr[0];
            } else {
                d = msg["data"];
            }
            if (d.is_null() || !d.is_object()) return false;

            std::string state = d.contains("state") ? d["state"].get<std::string>() : "";
            bool filled = (state == "filled");

            std::vector<std::string> required;
            if (topic == "orders") {
                required = {"order_id", "contract_code", "side", "type", "volume", "state",
                           "margin_mode", "position_side", "lever_rate", "created_time", "updated_time"};
                if (filled) required.insert(required.end(), {"trade_avg_price", "trade_volume", "trade_turnover"});
            } else if (topic == "trade") {
                required = {"trade_id", "order_id", "contract_code", "direction", "trade_price",
                           "trade_volume", "trade_turnover", "role", "position_side", "created_time"};
            } else if (topic == "trade_detail") {
                required = {"trade_id", "order_id", "contract_code", "direction", "trade_price",
                           "trade_volume", "trade_turnover", "trade_fee", "fee_currency", "position_side", "created_time"};
            } else if (topic == "positions") {
                required = {"contract_code", "position_side", "direction", "margin_mode", "volume",
                           "lever_rate", "open_avg_price", "margin", "state", "created_time"};
            } else if (topic == "account") {
                required = {"equity", "state", "details", "initial_margin", "maintenance_margin", "available_margin"};
            } else if (topic == "match_orders") {
                required = {"order_id", "contract_code", "side", "type", "volume", "state", "match_time", "position_side"};
                if (filled) required.insert(required.end(), {"trade_id", "trade_price", "trade_volume", "role"});
            } else if (topic == "algo_orders") {
                required = {"algo_id", "contract_code", "type", "side", "volume", "state",
                           "margin_mode", "position_side", "trigger_price", "created_time"};
            }
            for (const auto &f : required) {
                if (!d.contains(f) || d[f].is_null()) {
                    error = topic + " missing field: " + f + " (state=" + state + ")";
                    return true;
                }
            }
            return true;
        } catch (const std::exception &e) {
            error = topic + " parse error: " + std::string(e.what());
            return true;
        }
    }

    // REST 触发器：挂远价限价单（触发 orders 推送），返回 order_id 供清理
    string triggerLimitOrder(OrderClient &client) {
        auto r = client.TradeOrder(V5_WS_CONTRACT, "cross", "long", "buy", "limit", "",
                                   "", V5_WS_FAR_PRICE, "1", "", "", "", "", "", "", "", "",
                                   "", "", "", "");
        if (!r || r->code.value_or(0) != 200 || !r->data.has_value()) return "";
        return r->data->order_id;
    }

    // REST 触发器：市价买 1 张成交（触发 trade/positions/account/match_orders 推送），
    // 只按本测试订单确认成交量后平掉该数量，不根据账户仓位推断归属。
    void triggerMarketFillAndClose(OrderClient &client) {
        double before = 0;
        std::string error;
        if (!readSpxLongVolume(before, error))
        {
            ADD_FAILURE() << "cannot read SPX500-USDT position before market trigger: " << error;
            return;
        }
        if (before > 0)
        {
            ADD_FAILURE() << "pre-existing SPX500-USDT long position; refusing to trade";
            return;
        }

        const std::string client_order_id = makeTestClientOrderId();
        auto place = client.TradeOrder(V5_WS_CONTRACT, "cross", "long", "buy", "market", "",
                                       client_order_id, "", "1", "", "", "", "", "", "", "", "",
                                       "", "", "", "");
        const int place_code = place ? place->code.value_or(0) : -1;
        const std::string order_id =
            (place && place->data.has_value()) ? place->data->order_id : "";

        double fill_volume = 0;
        std::string confirm_error;
        if (!confirmMarketFill(client, client_order_id, order_id, fill_volume, confirm_error))
        {
            ADD_FAILURE() << "market order response code=" << place_code
                          << "; fill could not be established for this test order; "
                             "residual risk, not widening cleanup target: " << confirm_error;
            return;
        }
        if (fill_volume <= 0)
        {
            ADD_FAILURE() << "market order response code=" << place_code
                          << " confirmed zero fill; nothing safely closeable";
            return;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(800));

        std::string close_error;
        if (!closeConfirmedSpxLongExposure(client, fill_volume, close_error))
        {
            ADD_FAILURE() << "confirmed fill " << fill_volume
                          << " could not be cleaned safely; residual risk: " << close_error;
            return;
        }
    }
}

class WSNotifyTest : public ::testing::Test {
protected:
    void SetUp() override {
        extern map<string, string> config;
        init_config();
    }
};

// 只有 data 明确存在时才能确认“没有待清理的测试策略单”；缺 data 视为未确认。
static bool inspectOpenAlgoOrders(const AlgoQueryOpenOrdersResponse &response,
                                  const string *exact_client_order_id,
                                  std::vector<string> &algo_ids_to_cancel,
                                  string &error) {
    algo_ids_to_cancel.clear();
    if (response.code.value_or(0) != 200) {
        error = "open algo order query code=" + std::to_string(response.code.value_or(0)) +
                " message=" + response.message.value_or("");
        return false;
    }
    if (!response.data.has_value()) {
        error = "open algo order query is missing data; cannot confirm cleanup";
        return false;
    }

    for (const auto &order : response.data.value()) {
        const string client_order_id = order.algo_client_order_id.value_or("");
        const bool matches = exact_client_order_id != nullptr
                                 ? (client_order_id == *exact_client_order_id)
                                 : isTestClientOrderId(client_order_id);
        if (!matches) continue;

        const string algo_id = order.algo_id.value_or("");
        if (algo_id.empty()) {
            error = "test-owned algo order is missing algo_id";
            return false;
        }
        algo_ids_to_cancel.push_back(algo_id);
    }
    return true;
}

// 只清理带测试前缀的遗留策略单；不按合约/价格/数量匹配账户里的其它订单。
static bool cleanupStaleTestAlgoOrders(AlgoClient &client) {
    for (int attempt = 0; attempt < 8; ++attempt) {
        auto open_orders = client.AlgoQueryOpenOrders("trigger", V5_WS_CONTRACT);
        if (!open_orders) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }

        std::vector<string> algo_ids;
        string inspect_error;
        if (!inspectOpenAlgoOrders(*open_orders, nullptr, algo_ids, inspect_error)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }
        if (algo_ids.empty()) return true;

        for (const auto &algo_id : algo_ids) {
            client.AlgoCancelOrders(algo_id, "", V5_WS_CONTRACT);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return false;
}

// 按精确 algo_client_order_id 清理本用例创建的订单，并轮询确认服务端状态已更新。
static bool cleanupTestAlgoOrder(AlgoClient &client, const string &client_order_id,
                                 const string &known_algo_id = "") {
    if (!isTestClientOrderId(client_order_id)) return false;

    if (!known_algo_id.empty()) {
        client.AlgoCancelOrders(known_algo_id, "", V5_WS_CONTRACT);
    }

    for (int attempt = 0; attempt < 10; ++attempt) {
        auto open_orders = client.AlgoQueryOpenOrders(
            "trigger", V5_WS_CONTRACT, "", client_order_id);
        if (!open_orders) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }

        std::vector<string> algo_ids;
        string inspect_error;
        if (!inspectOpenAlgoOrders(*open_orders, &client_order_id, algo_ids, inspect_error)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }
        if (algo_ids.empty()) return true;

        for (const auto &algo_id : algo_ids) {
            client.AlgoCancelOrders(algo_id, "", V5_WS_CONTRACT);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return false;
}

// 通用推送测试骨架：订阅 → 等 ack → 触发 → 等数据 → 断言
static void runNotifyTest(const string &topic, const std::function<void(OrderClient &)> &trigger) {
    extern map<string, string> config;
    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;
    std::mutex errorMtx;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    ASSERT_TRUE(ws.Connect()) << "WS connect failed";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    ws.Sub({topic}, V5_WS_CONTRACT, [&](const std::string &response) {
        LOG(INFO) << topic << " received: " << response;
        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }
        // 只校验 notify 数据帧，auth/sub ack 等帧跳过
        try {
            auto msg = nlohmann::json::parse(response);
            if (!msg.contains("op") || msg["op"].get<std::string>() != "notify") return;
        } catch (...) { return; }
        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                std::lock_guard<std::mutex> lock(errorMtx);
                if (errorMsg.empty()) errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    LOG(INFO) << topic << " sub ack: " << (subAckRecv ? "yes" : "no");
    ASSERT_TRUE(subAckRecv) << topic << " sub ack not received";

    OrderClient client(config["AccessKey"], config["SecretKey"]);
    trigger(client);

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ws.Disconnect();
    EXPECT_TRUE(dataRecv) << topic << " data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubOrders) {
    runNotifyTest("orders", [](OrderClient &c) {
        string oid = triggerLimitOrder(c);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (!oid.empty()) c.CancelTradeOrder(V5_WS_CONTRACT, oid, "");
    });
}

TEST_F(WSNotifyTest, SubTrade) {
    string reason;
    if (!spxLongBaselineFlat(reason)) GTEST_SKIP() << reason;
    runNotifyTest("trade", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubTradeDetail) {
    string reason;
    if (!spxLongBaselineFlat(reason)) GTEST_SKIP() << reason;
    runNotifyTest("trade_detail", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubPositions) {
    string reason;
    if (!spxLongBaselineFlat(reason)) GTEST_SKIP() << reason;
    runNotifyTest("positions", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubAccount) {
    string reason;
    if (!spxLongBaselineFlat(reason)) GTEST_SKIP() << reason;
    runNotifyTest("account", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubMatchOrders) {
    string reason;
    if (!spxLongBaselineFlat(reason)) GTEST_SKIP() << reason;
    runNotifyTest("match_orders", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubAlgoOrders) {
    extern map<string, string> config;
    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;
    std::mutex errorMtx;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    ASSERT_TRUE(ws.Connect()) << "WS connect failed";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    ws.Sub({"algo_orders"}, V5_WS_CONTRACT, [&](const std::string &response) {
        LOG(INFO) << "algo_orders received: " << response;
        if (!subAckRecv && isSubAck(response)) { subAckRecv = true; return; }
        try {
            auto msg = nlohmann::json::parse(response);
            if (!msg.contains("op") || msg["op"].get<std::string>() != "notify") return;
        } catch (...) { return; }
        std::string err;
        if (checkNotifyData("algo_orders", response, err)) {
            if (!err.empty()) { std::lock_guard<std::mutex> lock(errorMtx); if (errorMsg.empty()) errorMsg = err; }
            else dataRecv = true;
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ASSERT_TRUE(subAckRecv) << "algo_orders sub ack not received";

    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    ASSERT_TRUE(cleanupStaleTestAlgoOrders(client))
        << "could not clear stale test-owned WS algo orders";

    const string client_order_id = makeTestClientOrderId();
    auto r = client.AlgoOrder(V5_WS_CONTRACT, "trigger", "long", "buy", "cross",
                              client_order_id, "1", "", "", "", "", "", "", "", "",
                              V5_WS_FAR_PRICE, "", V5_WS_FAR_PRICE, "last", "", "optimal_20", "");
    EXPECT_NE(r, nullptr) << "AlgoOrder returned no response";
    if (r) EXPECT_EQ(r->code.value_or(0), 200) << "AlgoOrder request failed";
    string algo_id;
    if (r && r->data.has_value() && !r->data->empty()) {
        algo_id = r->data->at(0).algo_id.value_or("");
    }
    for (int i = 0; i < 200 && !dataRecv; ++i) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ws.Disconnect();
    bool cancelSucceeded = false;
    if (!algo_id.empty()) {
        auto cancel = client.AlgoCancelOrders(algo_id, "", V5_WS_CONTRACT);
        cancelSucceeded = cancel && cancel->code.value_or(0) == 200;
    }
    bool testOrdersCleared = cleanupTestAlgoOrder(client, client_order_id, algo_id);
    EXPECT_TRUE(cancelSucceeded) << "algo order response missing ID or cancellation failed";
    EXPECT_TRUE(testOrdersCleared) << "test-owned algo order could not be cleared";
    EXPECT_TRUE(dataRecv) << "algo_orders data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;

    // 最终残留确认同样要求 data 明确存在；缺 data 会重试后失败，而不是当作已清理。
    ASSERT_TRUE(cleanupTestAlgoOrder(client, client_order_id))
        << "final residue check could not confirm test-owned algo order is gone";
}

// 回归保护：API code=200 但缺少 data 时无法确认仓位，必须 fail closed，不能当成空仓放行交易。
TEST(V5WSCleanupGuard, MissingPositionDataFailsClosed)
{
    const V5WSPositionResponseFetcher fetch =
        [](V5WSActivePositionsResponse &response, std::string &) {
            response.code = 200;
            // 故意不设置 response.data：模拟服务端成功码但缺字段。
            return true;
        };

    double volume = 123.0;
    std::string error;
    EXPECT_FALSE(readSpxLongVolumeWithFetcher(fetch, volume, error));
    EXPECT_FALSE(error.empty());

    // data 存在且为空数组时才是可确认的空仓。
    const V5WSPositionResponseFetcher empty_fetch =
        [](V5WSActivePositionsResponse &response, std::string &) {
            response.code = 200;
            response.data = std::vector<V5WSActivePositionItem>{};
            return true;
        };
    volume = 123.0;
    error.clear();
    EXPECT_TRUE(readSpxLongVolumeWithFetcher(empty_fetch, volume, error));
    EXPECT_EQ(volume, 0.0);
    EXPECT_TRUE(error.empty());
}

TEST(V5WSCleanupGuard, PositionRowsFailClosedOnMissingOrInvalidFields)
{
    auto make_row = []() {
        V5WSActivePositionItem row;
        row.contract_code = V5_WS_CONTRACT;
        row.position_side = "long";
        row.volume = "1";
        return row;
    };
    auto expect_invalid = [](V5WSActivePositionItem row, const char *label) {
        const V5WSPositionResponseFetcher fetch =
            [row](V5WSActivePositionsResponse &response, std::string &) {
                response.code = 200;
                response.data = std::vector<V5WSActivePositionItem>{row};
                return true;
            };
        double volume = 123.0;
        std::string error;
        EXPECT_FALSE(readSpxLongVolumeWithFetcher(fetch, volume, error)) << label;
        EXPECT_FALSE(error.empty()) << label;
    };

    V5WSActivePositionItem row;
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

TEST(V5WSCleanupGuard, PositionRowsAcceptConfirmedAmounts)
{
    auto expect_valid = [](V5WSActivePositionsResponse response, double expected,
                           const char *label) {
        const V5WSPositionResponseFetcher fetch =
            [response](V5WSActivePositionsResponse &out, std::string &) {
                out = response;
                return true;
            };
        double volume = 123.0;
        std::string error;
        EXPECT_TRUE(readSpxLongVolumeWithFetcher(fetch, volume, error)) << label;
        EXPECT_DOUBLE_EQ(volume, expected) << label;
        EXPECT_TRUE(error.empty()) << label;
    };

    V5WSActivePositionsResponse empty;
    empty.code = 200;
    empty.data = std::vector<V5WSActivePositionItem>{};
    expect_valid(empty, 0.0, "present empty data");

    V5WSActivePositionItem long_one;
    long_one.contract_code = V5_WS_CONTRACT;
    long_one.position_side = "long";
    long_one.volume = "1";
    V5WSActivePositionItem long_half;
    long_half.contract_code = V5_WS_CONTRACT;
    long_half.position_side = "long";
    long_half.volume = "0.5";
    V5WSActivePositionItem short_two;
    short_two.contract_code = V5_WS_CONTRACT;
    short_two.position_side = "short";
    short_two.volume = "2";
    V5WSActivePositionItem other_contract;
    other_contract.contract_code = "BTC-USDT";

    V5WSActivePositionsResponse valid;
    valid.code = 200;
    valid.data = std::vector<V5WSActivePositionItem>{long_one, long_half, short_two, other_contract};
    expect_valid(valid, 1.5, "valid long sum, short ignored, other contract skipped");
}

TEST(V5WSAlgoCleanupGuard, MissingOpenOrderDataIsUnconfirmed)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200; // data 故意缺失

    std::vector<string> algo_ids;
    string error;
    EXPECT_FALSE(inspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_FALSE(error.empty());

    const string client_order_id = "9090909000000000001";
    error.clear();
    EXPECT_FALSE(inspectOpenAlgoOrders(response, &client_order_id, algo_ids, error));
    EXPECT_FALSE(error.empty());
}

TEST(V5WSAlgoCleanupGuard, PresentEmptyOpenOrderDataConfirmsEmpty)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200;
    response.data = std::vector<AlgoQueryOpenOrdersResponse::Data>{};

    std::vector<string> algo_ids;
    string error;
    EXPECT_TRUE(inspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_TRUE(algo_ids.empty());
    EXPECT_TRUE(error.empty());

    const string client_order_id = "9090909000000000001";
    EXPECT_TRUE(inspectOpenAlgoOrders(response, &client_order_id, algo_ids, error));
    EXPECT_TRUE(algo_ids.empty());
    EXPECT_TRUE(error.empty());
}

TEST(V5WSAlgoCleanupGuard, MalformedTestOrderFailsClosed)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200;
    AlgoQueryOpenOrdersResponse::Data order;
    order.algo_client_order_id = "9090909000000000001";
    response.data = std::vector<AlgoQueryOpenOrdersResponse::Data>{order};

    std::vector<string> algo_ids;
    string error;
    EXPECT_FALSE(inspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_FALSE(error.empty());
}

TEST(V5WSMarketFillGuard, ConfirmsOnlyOwnedTerminalFill)
{
    const string expected_client_order_id = "9090909000000000001";
    const string expected_order_id = "12345";

    auto make_order = []() {
        GetTradeOrderResponse response;
        response.code = 200;
        GetTradeOrderResponse::Data order;
        order.client_order_id = "9090909000000000001";
        order.order_id = "12345";
        order.contract_code = V5_WS_CONTRACT;
        order.side = "buy";
        order.position_side = "long";
        order.state = "filled";
        order.volume = "1";
        order.trade_volume = "1";
        response.data = order;
        return response;
    };
    auto expect_unconfirmed = [&](GetTradeOrderResponse response, const char *label) {
        const WSMarketFillAssessment assessment =
            evaluateMarketFill(response, expected_client_order_id, expected_order_id);
        EXPECT_FALSE(assessment.confirmed) << label;
        EXPECT_FALSE(assessment.error.empty()) << label;
    };

    const WSMarketFillAssessment confirmed =
        evaluateMarketFill(make_order(), expected_client_order_id, expected_order_id);
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
    response.data->state = "partial_filled";
    expect_unconfirmed(response, "non-terminal state");

    response = make_order();
    response.data->state = "filled";
    response.data->trade_volume.reset();
    expect_unconfirmed(response, "missing trade_volume");

    for (const char *bad : {"nan", "inf", "1abc", "-1", "1e309", "1.5", " 1"})
    {
        response = make_order();
        response.data->trade_volume = bad;
        expect_unconfirmed(response, bad);
    }

    response = make_order();
    response.data->volume = "2";
    expect_unconfirmed(response, "order volume over cap");

    response = make_order();
    response.data->state = "filled";
    response.data->trade_volume = "0";
    expect_unconfirmed(response, "filled with zero fill");

    response = make_order();
    response.data->state = "canceled";
    response.data->trade_volume = "0";
    const WSMarketFillAssessment canceled =
        evaluateMarketFill(response, expected_client_order_id, expected_order_id);
    EXPECT_TRUE(canceled.confirmed);
    EXPECT_DOUBLE_EQ(canceled.volume, 0.0);
    EXPECT_TRUE(canceled.error.empty());
}

TEST(V5WSMarketFillGuard, CleanupScopeCapsAtOneContract)
{
    EXPECT_TRUE(isSafeConfirmedFillVolume(1.0));
    EXPECT_TRUE(isSafeConfirmedFillVolume(0.5));
    EXPECT_FALSE(isSafeConfirmedFillVolume(0.0));
    EXPECT_FALSE(isSafeConfirmedFillVolume(-1.0));
    EXPECT_FALSE(isSafeConfirmedFillVolume(1.0000001));
    EXPECT_FALSE(isSafeConfirmedFillVolume(2.0));
    EXPECT_FALSE(isSafeConfirmedFillVolume(std::numeric_limits<double>::infinity()));
    EXPECT_FALSE(isSafeConfirmedFillVolume(std::numeric_limits<double>::quiet_NaN()));

    EXPECT_EQ(formatVolume(1.0), "1");
    EXPECT_EQ(formatVolume(0.5), "0.5");
    EXPECT_EQ(formatVolume(0.0), "0");
}
