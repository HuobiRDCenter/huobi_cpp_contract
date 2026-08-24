#include <gtest/gtest.h>

#include "huobi_futures/linear_swap/restful/AlgoClient.hpp"
typedef huobi_futures::linear_swap::restful::AlgoClient AlgoClient;
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 algo 接口（私有，需 key）。
// 策略单用远价限价单（7300，市价≈7600）挂单后立即撤单，0 成交 0 损失。
// dual_side 模式下单必带 position_side。

extern const string V5_CONTRACT;
extern const string V5_FAR_PRICE;

// algo 用 BTC-USDT（对齐 Java SrategyAPITest），trigger_price 远低于市价不触发，0 风险
static const string ALGO_CONTRACT = "BTC-USDT";
static const string ALGO_TRIGGER_PRICE = "10000";

// 辅助：创建一个远价限价的策略单，返回 algo_id（供后续撤单/查询）
static string PlaceFarAlgoOrder(AlgoClient &client, const string &position_side = "long")
{
    auto r = client.AlgoOrder(ALGO_CONTRACT, "trigger", position_side, "buy", "cross",
                              "", "1", "", "", "", "", "", "", "", "",
                              ALGO_TRIGGER_PRICE, "", ALGO_TRIGGER_PRICE, "last", "", "optimal_20", "");
    EXPECT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    // algo_id 在 data vector 的第一个元素里
    if (r->data.has_value() && !r->data->empty())
    {
        return r->data->at(0).algo_id.value_or("");
    }
    return "";
}

TEST(V5Algo, AlgoOrder)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    auto r = client.AlgoOrder(ALGO_CONTRACT, "trigger", "long", "buy", "cross",
                              "", "1", "", "", "", "", "", "", "", "",
                              ALGO_TRIGGER_PRICE, "", ALGO_TRIGGER_PRICE, "last", "", "optimal_20", "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    // 下单成功后立即撤单
    string algo_id = (r->data.has_value() && !r->data->empty()) ? r->data->at(0).algo_id.value_or("") : "";
    if (!algo_id.empty())
    {
        auto c = client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
        EXPECT_EQ(c->code.value_or(0), 200);
    }
}

TEST(V5Algo, AlgoCancelOrders)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    // 先创建一个策略单，然后撤销
    string algo_id = PlaceFarAlgoOrder(client);
    if (!algo_id.empty())
    {
        auto r = client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
        ASSERT_NE(r, nullptr);
        EXPECT_EQ(r->code.value_or(0), 200);
    }
}

TEST(V5Algo, AlgoQueryOrders)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    // 前置创建一个策略单再查询
    string algo_id = PlaceFarAlgoOrder(client);
    auto r = client.AlgoQueryOrders("trigger", algo_id, "", ALGO_CONTRACT);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    if (!algo_id.empty())
    {
        client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
    }
}

TEST(V5Algo, AlgoQueryOpenOrders)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    // 查询所有未触发策略单
    auto r = client.AlgoQueryOpenOrders("trigger", ALGO_CONTRACT, "", "", 0, 0, "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Algo, AlgoQueryOrderHistory)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    // 查询历史策略单
    auto r = client.AlgoQueryOrderHistory("trigger", ALGO_CONTRACT, "cross", "", "", "", 0, 0, "");
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}
