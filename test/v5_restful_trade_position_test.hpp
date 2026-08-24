#include <gtest/gtest.h>

#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
typedef huobi_futures::linear_swap::restful::OrderClient OrderClient;
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 trade + position 接口（私有，需 key）。
// 写操作用 SPX500-USDT 远价限价单（7300，市价≈7600）挂单后立即撤单，0 成交 0 损失。
// dual_side 模式下单必带 position_side。空数据接口用前置数据复测。

static const string V5_CONTRACT = "SPX500-USDT";
static const string V5_FAR_PRICE = "7300"; // 远低于市价的限价买单，不会成交

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