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

#include "huobi_futures/nlohmann_json/json.hpp"
#include "huobi_futures/url_base/HttpRequest.hpp"

// 辅助函数：提取 REST key
extern "C"
{
    // 声明 REST 交易函数（链接时外部定义）
}

namespace {
    // 辅助：等待订阅 ack (op:sub && err-code:0) 再触发数据
    // 避免 "订阅未就绪就下单" 导致推送丢失
    bool isSubAck(const std::string &response) {
        try {
            auto msg = nlohmann::json::parse(response);
            if (msg.contains("op") && msg["op"].get<std::string>() == "sub" &&
                msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                return true;
            }
        } catch (...) {
        }
        return false;
    }

    // 校验推送数据的必填字段
    // data 结构因 topic 而异：orders/account 为单对象，其余为对象数组
    // 返回 true 表示有效数据帧（可 countDown），false 表示空快照应跳过
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
                if (arr.empty()) {
                    return false; // 空快照跳过
                }
                d = arr[0];
            } else {
                d = msg["data"];
            }

            if (d.is_null() || !d.is_object()) {
                return false;
            }

            // 按 topic 检查必填字段
            std::string state = d.contains("state") ? d["state"].get<std::string>() : "";
            bool filled = (state == "filled");

            std::vector<std::string> required;
            if (topic == "orders") {
                required = {"order_id", "contract_code", "side", "type", "volume", "state",
                           "margin_mode", "position_side", "lever_rate", "created_time", "updated_time"};
                if (filled) {
                    required.insert(required.end(), {"trade_avg_price", "trade_volume", "trade_turnover"});
                }
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
                if (filled) {
                    required.insert(required.end(), {"trade_id", "trade_price", "trade_volume", "role"});
                }
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
            return true; // 有效数据帧
        } catch (const std::exception &e) {
            error = topic + " parse error: " + std::string(e.what());
            return true;
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

// 推送测试模板：订阅 topic → 等 ack → REST 触发数据 → latch 等推送 → 断言
#define V5_WS_NOTIFY_TEST(topic_name, rest_trigger) \
    TEST_F(WSNotifyTest, Sub##topic_name) { \
        extern map<string, string> config; \
        std::string topic = "SPX500-USDT." + std::string(#topic_name); \
        \
        std::atomic<bool> subAckRecv(false); \
        std::atomic<bool> dataRecv(false); \
        std::string errorMsg; \
        std::mutex errorMtx; \
        \
        WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]); \
        if (!ws.Connect()) { \
            FAIL() << "WS connect failed"; \
            return; \
        } \
        \
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); \
        \
        ws.Sub({topic}, [&](const std::string &response) { \
            LOG(INFO) << #topic_name << " received: " << response; \
            \
            if (!subAckRecv && isSubAck(response)) { \
                subAckRecv = true; \
                return; \
            } \
            \
            std::string err; \
            if (checkNotifyData(topic, response, err)) { \
                if (!err.empty()) { \
                    std::lock_guard<std::mutex> lock(errorMtx); \
                    if (errorMsg.empty()) errorMsg = err; \
                } else { \
                    dataRecv = true; \
                } \
            } \
        }); \
        \
        /* wait for sub ack */ \
        for (int i = 0; i < 100 && !subAckRecv; ++i) { \
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); \
        } \
        LOG(INFO) << "Sub ack received: " << (subAckRecv ? "yes" : "no"); \
        \
        /* trigger data */ \
        rest_trigger; \
        \
        /* wait for data */ \
        for (int i = 0; i < 200 && !dataRecv; ++i) { \
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); \
        } \
        \
        ws.Disconnect(); \
        \
        EXPECT_TRUE(dataRecv) << "data not received within 20s"; \
        EXPECT_TRUE(errorMsg.empty()) << errorMsg; \
    }

// Topic tests - using placeholder triggers for now
// In real test, these would call REST API to trigger data

TEST_F(WSNotifyTest, SubOrders) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.orders";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;
    std::mutex errorMtx;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "orders received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

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

    // wait for sub ack
    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    LOG(INFO) << "Sub ack received: " << (subAckRecv ? "yes" : "no");

    // TODO: trigger via REST - place limit order
    // For now just wait to see if mock data arrives

    // wait for data
    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "orders data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubTrade) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.trade";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "trade received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    LOG(INFO) << "Sub ack received: " << (subAckRecv ? "yes" : "no");

    // TODO: trigger market order fill

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "trade data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubTradeDetail) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.trade_detail";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "trade_detail received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "trade_detail data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubPositions) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.positions";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "positions received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "positions data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubAccount) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.account";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "account received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "account data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubMatchOrders) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.match_orders";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "match_orders received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "match_orders data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}

TEST_F(WSNotifyTest, SubAlgoOrders) {
    extern map<string, string> config;
    std::string topic = "SPX500-USDT.algo_orders";

    std::atomic<bool> subAckRecv(false);
    std::atomic<bool> dataRecv(false);
    std::string errorMsg;

    WSSwapNotificationClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect()) {
        FAIL() << "WS connect failed";
        return;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    ws.Sub({topic}, [&](const std::string &response) {
        LOG(INFO) << "algo_orders received: " << response;

        if (!subAckRecv && isSubAck(response)) {
            subAckRecv = true;
            return;
        }

        std::string err;
        if (checkNotifyData(topic, response, err)) {
            if (!err.empty()) {
                errorMsg = err;
            } else {
                dataRecv = true;
            }
        }
    });

    for (int i = 0; i < 100 && !subAckRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (int i = 0; i < 200 && !dataRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(dataRecv) << "algo_orders data not received within 20s";
    EXPECT_TRUE(errorMsg.empty()) << errorMsg;
}
