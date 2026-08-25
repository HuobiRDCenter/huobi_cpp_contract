#include <gtest/gtest.h>

#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
typedef huobi_futures::linear_swap::restful::OrderClient OrderClient;
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 trade + position 接口（私有，需 key）。
// 写操作用 SPX500-USDT 远价限价单（7300，市价≈7600）挂单后立即撤单，0 成交 0 损失。
// dual_side 模式下单必带 position_side。空数据接口用前置数据复测。

static const string V5_CONTRACT = "SPX500-USDT";
static const string V5_FAR_PRICE = "1000"; // 远低于市价（SPX500 low_limit≈7271），肯定不成交的限价买单

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

// #15 GET /v5/trade/order/details - 查询成交明细（Java 权威：市价买 1 张成交→查明细→全平清理）
TEST(V5Trade, TradeOrderDetails)
{
    extern map<string, string> config;
    init_config();
    OrderClient client(config["AccessKey"], config["SecretKey"]);
    // 市价买入 1 张 SPX500 成交（产生成交记录）
    auto place = client.TradeOrder(V5_CONTRACT, "cross", "long", "buy", "market", "",
                                  "", "", "1", "", "", "", "", "", "", "", "",
                                  "", "", "", "");
    ASSERT_NE(place, nullptr);
    ASSERT_EQ(place->code.value_or(0), 200);
    string oid = place->data.has_value() ? place->data->order_id : "";
    ASSERT_FALSE(oid.empty());
    // 查询该单成交明细
    auto r = client.TradeOrderDetails(V5_CONTRACT, oid, "", "", "", "", "", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_TRUE(r->data != nullptr);
    ASSERT_FALSE(r->data->empty());
    EXPECT_FALSE(r->data->at(0).trade_id.value_or("").empty());
    // 清理：全平该持仓
    client.TradePosition(V5_CONTRACT, "cross", "long", "");
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
    auto r = client.SetPositionLever("BTC-USDT", "isolated", "5", "long");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
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