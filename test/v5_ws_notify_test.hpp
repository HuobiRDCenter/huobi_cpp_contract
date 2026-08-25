#pragma once
#include <gtest/gtest.h>
#include <glog/logging.h>

#include "config.hpp"
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>

#include "huobi_futures/linear_swap/ws/WSSwapNotificationClient.hpp"
typedef huobi_futures::linear_swap::ws::WSSwapNotificationClient WSSwapNotificationClient;

#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
typedef huobi_futures::linear_swap::restful::OrderClient OrderClient;
#include "huobi_futures/linear_swap/restful/AlgoClient.hpp"
typedef huobi_futures::linear_swap::restful::AlgoClient AlgoClient;

#include "huobi_futures/nlohmann_json/json.hpp"

// V5 推送测试（私有，需 key 鉴权）。
// 订阅 topic → 等 sub ack → REST 触发数据 → latch 等推送 → 断言必填字段。
// orders/algo_orders 用远价限价单/策略单（0 成交）；trade/positions/account/match_orders 用市价成交（成本极低）。

static const string V5_WS_CONTRACT = "SPX500-USDT";
static const string V5_WS_FAR_PRICE = "1000"; // 远价限价单，不成交

namespace {
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

    // REST 触发器：市价买 1 张成交（触发 trade/positions/account/match_orders 推送），随后全平清理
    void triggerMarketFillAndClose(OrderClient &client) {
        // 前置清账户残留挂单/持仓，避免连续跑时账户状态污染
        client.CancelAllOrders(V5_WS_CONTRACT, "buy", "long");
        client.TradePositionAll();
        auto place = client.TradeOrder(V5_WS_CONTRACT, "cross", "long", "buy", "market", "",
                                      "", "", "1", "", "", "", "", "", "", "", "",
                                      "", "", "", "");
        if (!place || place->code.value_or(0) != 200) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        client.TradePosition(V5_WS_CONTRACT, "cross", "long", "");
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        client.TradePositionAll(); // 兜底全平持仓
        client.CancelAllOrders(V5_WS_CONTRACT, "buy", "long"); // 兜底撤残留挂单
    }
}

class WSNotifyTest : public ::testing::Test {
protected:
    void SetUp() override {
        extern map<string, string> config;
        init_config();
    }
};

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
    runNotifyTest("trade", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubTradeDetail) {
    runNotifyTest("trade_detail", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubPositions) {
    runNotifyTest("positions", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubAccount) {
    runNotifyTest("account", [](OrderClient &c) { triggerMarketFillAndClose(c); });
}

TEST_F(WSNotifyTest, SubMatchOrders) {
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
    auto r = client.AlgoOrder(V5_WS_CONTRACT, "trigger", "long", "buy", "cross",
                              "", "1", "", "", "", "", "", "", "", "",
                              "100", "", "100", "last", "", "optimal_20", "");
    string algo_id;
    if (r && r->data.has_value() && !r->data->empty()) {
        algo_id = r->data->at(0).algo_id.value_or("");
    }
    for (int i = 0; i < 200 && !dataRecv; ++i) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    ws.Disconnect();
    if (!algo_id.empty()) client.AlgoCancelOrders(algo_id, "", V5_WS_CONTRACT);
    EXPECT_TRUE(dataRecv) << "algo_orders data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}
