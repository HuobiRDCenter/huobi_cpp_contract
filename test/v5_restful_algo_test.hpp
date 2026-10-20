#include <gtest/gtest.h>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>

#include "huobi_futures/linear_swap/restful/AlgoClient.hpp"
typedef huobi_futures::linear_swap::restful::AlgoClient AlgoClient;
#include "huobi_futures/utils/convert.hpp"

#include "config.hpp"

// V5 algo 接口（私有，需 key）。
// 策略单用远价限价单（78000，市价≈82700）挂单后立即撤单，0 成交 0 损失。
// dual_side 模式下单必带 position_side。

extern const string V5_CONTRACT;
extern const string V5_FAR_PRICE;

// algo 用 BTC-USDT（对齐 Java SrategyAPITest），trigger_price 远低于市价不触发，0 风险
static const string ALGO_CONTRACT = "BTC-USDT";
static const string ALGO_TRIGGER_PRICE = "78000";

// HTX V5 的 client_order_id 只接受数字；统一使用 7 位测试前缀 + 秒级时间戳 + 2 位序列。
// 19 位数字保持在 int64 范围内，且前缀可明确识别为测试创建。
static const string V5_TEST_CLIENT_ID_PREFIX = "9090909";

static string MakeTestClientOrderId()
{
    static std::atomic<uint64_t> sequence{0};
    const auto now_seconds = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    const string seq = std::to_string(100 + (sequence.fetch_add(1) % 100)).substr(1);
    return V5_TEST_CLIENT_ID_PREFIX + std::to_string(now_seconds) + seq;
}

static bool IsTestClientOrderId(const string &client_order_id)
{
    return client_order_id.size() == 19 &&
           client_order_id.rfind(V5_TEST_CLIENT_ID_PREFIX, 0) == 0;
}

// 辅助：创建一个远价限价的策略单，返回 algo_id（供后续撤单/查询）
static string PlaceFarAlgoOrder(AlgoClient &client, const string &client_order_id,
                                const string &position_side = "long")
{
    if (!IsTestClientOrderId(client_order_id))
    {
        ADD_FAILURE() << "refusing to place algo order without a test-owned client_order_id";
        return "";
    }
    auto r = client.AlgoOrder(ALGO_CONTRACT, "trigger", position_side, "buy", "cross",
                              client_order_id, "1", "", "", "", "", "", "", "", "",
                              ALGO_TRIGGER_PRICE, "", ALGO_TRIGGER_PRICE, "last", "", "optimal_20", "");
    if (r == nullptr)
    {
        ADD_FAILURE() << "AlgoOrder returned no response";
        return "";
    }
    if (r->code.value_or(0) != 200)
    {
        ADD_FAILURE() << "AlgoOrder failed with code=" << r->code.value_or(0)
                      << " message=" << r->message.value_or("");
        return "";
    }
    // algo_id 在 data vector 的第一个元素里
    if (r->data.has_value() && !r->data->empty())
    {
        string algo_id = r->data->at(0).algo_id.value_or("");
        if (!algo_id.empty()) return algo_id;
    }
    ADD_FAILURE() << "AlgoOrder response did not include algo_id";
    return "";
}

// 只有 data 明确存在时才能确认“没有待清理的测试策略单”；缺 data 视为未确认。
static bool InspectOpenAlgoOrders(const AlgoQueryOpenOrdersResponse &response,
                                  const string *exact_client_order_id,
                                  std::vector<string> &algo_ids_to_cancel,
                                  string &error)
{
    algo_ids_to_cancel.clear();
    if (response.code.value_or(0) != 200)
    {
        error = "open algo order query code=" + std::to_string(response.code.value_or(0)) +
                " message=" + response.message.value_or("");
        return false;
    }
    if (!response.data.has_value())
    {
        error = "open algo order query is missing data; cannot confirm cleanup";
        return false;
    }

    for (const auto &order : response.data.value())
    {
        const string client_order_id = order.algo_client_order_id.value_or("");
        const bool matches = exact_client_order_id != nullptr
                                 ? (client_order_id == *exact_client_order_id)
                                 : IsTestClientOrderId(client_order_id);
        if (!matches) continue;

        const string algo_id = order.algo_id.value_or("");
        if (algo_id.empty())
        {
            error = "test-owned algo order is missing algo_id";
            return false;
        }
        algo_ids_to_cancel.push_back(algo_id);
    }
    return true;
}

// 只清理带测试前缀的遗留策略单；不按合约/价格/数量匹配账户里的其它订单。
static bool CleanupStaleTestAlgoOrders(AlgoClient &client, const string &contract_code)
{
    for (int attempt = 0; attempt < 8; ++attempt)
    {
        auto open_orders = client.AlgoQueryOpenOrders("trigger", contract_code);
        if (!open_orders)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }

        std::vector<string> algo_ids;
        string inspect_error;
        if (!InspectOpenAlgoOrders(*open_orders, nullptr, algo_ids, inspect_error))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }
        if (algo_ids.empty()) return true;

        for (const auto &algo_id : algo_ids)
        {
            client.AlgoCancelOrders(algo_id, "", contract_code);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return false;
}

// 按精确 algo_client_order_id 清理本用例创建的订单，并轮询确认服务端状态已更新。
static bool CleanupTestAlgoOrder(AlgoClient &client, const string &contract_code,
                                 const string &client_order_id,
                                 const string &known_algo_id = "")
{
    if (!IsTestClientOrderId(client_order_id)) return false;

    if (!known_algo_id.empty())
    {
        client.AlgoCancelOrders(known_algo_id, "", contract_code);
    }

    for (int attempt = 0; attempt < 10; ++attempt)
    {
        auto open_orders = client.AlgoQueryOpenOrders("trigger", contract_code, "", client_order_id);
        if (!open_orders)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }

        std::vector<string> algo_ids;
        string inspect_error;
        if (!InspectOpenAlgoOrders(*open_orders, &client_order_id, algo_ids, inspect_error))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
            continue;
        }
        if (algo_ids.empty()) return true;

        for (const auto &algo_id : algo_ids)
        {
            client.AlgoCancelOrders(algo_id, "", contract_code);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return false;
}

TEST(V5Algo, AlgoOrder)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    ASSERT_TRUE(CleanupStaleTestAlgoOrders(client, ALGO_CONTRACT))
        << "stale test-owned algo orders remained before AlgoOrder";

    const string client_order_id = MakeTestClientOrderId();
    auto r = client.AlgoOrder(ALGO_CONTRACT, "trigger", "long", "buy", "cross",
                              client_order_id, "1", "", "", "", "", "", "", "", "",
                              ALGO_TRIGGER_PRICE, "", ALGO_TRIGGER_PRICE, "last", "", "optimal_20", "");
    string algo_id = (r && r->data.has_value() && !r->data->empty()) ? r->data->at(0).algo_id.value_or("") : "";
    std::shared_ptr<AlgoCancelOrdersResponse> cancel;
    if (!algo_id.empty()) cancel = client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
    const bool clean = CleanupTestAlgoOrder(client, ALGO_CONTRACT, client_order_id, algo_id);
    EXPECT_TRUE(clean) << "test-owned algo order remained after cleanup";
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
    ASSERT_FALSE(algo_id.empty()) << "AlgoOrder response did not include algo_id";
    ASSERT_NE(cancel, nullptr);
    EXPECT_EQ(cancel->code.value_or(0), 200);
}

TEST(V5Algo, AlgoCancelOrders)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    ASSERT_TRUE(CleanupStaleTestAlgoOrders(client, ALGO_CONTRACT))
        << "stale test-owned algo orders remained before AlgoCancelOrders";
    // 先创建一个策略单，然后撤销
    const string client_order_id = MakeTestClientOrderId();
    string algo_id = PlaceFarAlgoOrder(client, client_order_id);
    std::shared_ptr<AlgoCancelOrdersResponse> r;
    if (!algo_id.empty()) r = client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
    const bool clean = CleanupTestAlgoOrder(client, ALGO_CONTRACT, client_order_id, algo_id);
    EXPECT_TRUE(clean) << "test-owned algo order remained after cleanup";
    ASSERT_FALSE(algo_id.empty());
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
}

TEST(V5Algo, AlgoQueryOrders)
{
    extern map<string, string> config;
    init_config();
    AlgoClient client(config["AccessKey"], config["SecretKey"]);
    ASSERT_TRUE(CleanupStaleTestAlgoOrders(client, ALGO_CONTRACT))
        << "stale test-owned algo orders remained before AlgoQueryOrders";
    // 前置创建一个策略单再查询
    const string client_order_id = MakeTestClientOrderId();
    string algo_id = PlaceFarAlgoOrder(client, client_order_id);
    // HTX 要求按 algo_id 或 algo_client_order_id 查询；仅传 type 会返回 1067。
    std::shared_ptr<AlgoQueryOrdersResponse> r;
    if (!algo_id.empty())
    {
        for (int attempt = 0; attempt < 8; ++attempt)
        {
            r = client.AlgoQueryOrders("trigger", algo_id, "", ALGO_CONTRACT);
            if (r && r->code.value_or(0) == 200) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }
    std::shared_ptr<AlgoCancelOrdersResponse> cancel;
    if (!algo_id.empty()) cancel = client.AlgoCancelOrders(algo_id, "", ALGO_CONTRACT);
    const bool clean = CleanupTestAlgoOrder(client, ALGO_CONTRACT, client_order_id, algo_id);
    EXPECT_TRUE(clean) << "test-owned algo order remained after cleanup";
    ASSERT_FALSE(algo_id.empty());
    ASSERT_NE(cancel, nullptr);
    EXPECT_EQ(cancel->code.value_or(0), 200);
    ASSERT_NE(r, nullptr);
    EXPECT_EQ(r->code.value_or(0), 200);
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

TEST(V5AlgoCleanupGuard, MissingOpenOrderDataIsUnconfirmed)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200; // data 故意缺失

    std::vector<string> algo_ids;
    string error;
    EXPECT_FALSE(InspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_FALSE(error.empty());

    const string client_order_id = "9090909000000000001";
    error.clear();
    EXPECT_FALSE(InspectOpenAlgoOrders(response, &client_order_id, algo_ids, error));
    EXPECT_FALSE(error.empty());
}

TEST(V5AlgoCleanupGuard, PresentEmptyOpenOrderDataConfirmsEmpty)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200;
    response.data = std::vector<AlgoQueryOpenOrdersResponse::Data>{};

    std::vector<string> algo_ids;
    string error;
    EXPECT_TRUE(InspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_TRUE(algo_ids.empty());
    EXPECT_TRUE(error.empty());

    const string client_order_id = "9090909000000000001";
    EXPECT_TRUE(InspectOpenAlgoOrders(response, &client_order_id, algo_ids, error));
    EXPECT_TRUE(algo_ids.empty());
    EXPECT_TRUE(error.empty());
}

TEST(V5AlgoCleanupGuard, MalformedTestOrderFailsClosed)
{
    AlgoQueryOpenOrdersResponse response;
    response.code = 200;
    AlgoQueryOpenOrdersResponse::Data order;
    order.algo_client_order_id = "9090909000000000001";
    // algo_id 缺失：不能当作已确认清理。
    response.data = std::vector<AlgoQueryOpenOrdersResponse::Data>{order};

    std::vector<string> algo_ids;
    string error;
    EXPECT_FALSE(InspectOpenAlgoOrders(response, nullptr, algo_ids, error));
    EXPECT_FALSE(error.empty());
}
