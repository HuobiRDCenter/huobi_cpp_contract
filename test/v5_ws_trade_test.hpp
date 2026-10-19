#pragma once
#include <gtest/gtest.h>
#include <glog/logging.h>

#include "config.hpp"
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <map>

#include "huobi_futures/linear_swap/ws/WSSwapTradeClient.hpp"
typedef huobi_futures::linear_swap::ws::WSSwapTradeClient WSSwapTradeClient;
// 用例结束用 REST 撤单清理挂单，避免单独跑某个用例时在账户里留下挂单
#include "huobi_futures/linear_swap/restful/OrderClient.hpp"

#include "huobi_futures/nlohmann_json/json.hpp"

class WSTradeTest : public ::testing::Test {
protected:
    void SetUp() override {
        extern map<string, string> config;
        init_config();
    }
};

TEST_F(WSTradeTest, PlaceOrder) {
    extern map<string, string> config;

    std::atomic<bool> authRecv(false);
    std::atomic<bool> respRecv(false);
    std::string respData;
    std::string errorMsg;
    std::mutex mtx;

    WSSwapTradeClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect([&](const std::string &response) {
        LOG(INFO) << "place_order response: " << response;

        auto msg = nlohmann::json::parse(response);

        if (msg.contains("op") && msg["op"].get<std::string>() == "auth") {
            if (msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                authRecv = true;
            }
            return;
        }

        if (msg.contains("cid") && msg["cid"].get<std::string>() == "1" &&
            msg.contains("code") && msg["code"].get<int>() == 200) {

            std::lock_guard<std::mutex> lock(mtx);
            if (msg.contains("data")) {
                respData = msg["data"].dump();
            }
            respRecv = true;
        }
    })) {
        FAIL() << "WS connect failed";
        return;
    }

    // wait auth
    for (int i = 0; i < 100 && !authRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    LOG(INFO) << "Auth received: " << (authRecv ? "yes" : "no");

    // place limit order (7300 SPX500, won't fill)
    nlohmann::json orderData;
    orderData["contract_code"] = "SPX500-USDT";
    orderData["margin_mode"] = "cross";
    orderData["position_side"] = "long";
    orderData["side"] = "buy";
    orderData["type"] = "limit";
    orderData["price"] = "7300";
    orderData["volume"] = "1";

    std::string cid = ws.PlaceOrder(orderData.dump());
    LOG(INFO) << "Sent place_order with cid: " << cid;

    // wait response
    for (int i = 0; i < 100 && !respRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(authRecv) << "auth not received";
    EXPECT_TRUE(respRecv) << "place_order response not received within 10s";
    EXPECT_FALSE(respData.empty()) << "place_order data empty";

    // parse response and check order_id，随后撤单清理（避免单独跑本用例时账户里留挂单）
    try {
        auto data = nlohmann::json::parse(respData);
        EXPECT_TRUE(data.contains("order_id")) << "order_id missing in response";
        if (data.contains("order_id")) {
            huobi_futures::linear_swap::restful::OrderClient rest(config["AccessKey"], config["SecretKey"]);
            auto cancel = rest.CancelTradeOrder("SPX500-USDT", data["order_id"].get<std::string>(), "");
            if (cancel) EXPECT_EQ(cancel->code.value_or(0), 200) << "cleanup cancel_order failed";
        }
    } catch (const std::exception &e) {
        FAIL() << "Failed to parse response data: " << e.what();
    }
}

TEST_F(WSTradeTest, PlaceBatchOrders) {
    extern map<string, string> config;

    std::atomic<bool> authRecv(false);
    std::atomic<bool> respRecv(false);
    std::string respData;

    WSSwapTradeClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect([&](const std::string &response) {
        LOG(INFO) << "place_batch_orders response: " << response;

        auto msg = nlohmann::json::parse(response);

        if (msg.contains("op") && msg["op"].get<std::string>() == "auth") {
            if (msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                authRecv = true;
            }
            return;
        }

        if (msg.contains("cid") && msg["cid"].get<std::string>() == "1" &&
            msg.contains("code") && msg["code"].get<int>() == 200) {

            if (msg.contains("data")) {
                respData = msg["data"].dump();
            }
            respRecv = true;
        }
    })) {
        FAIL() << "WS connect failed";
        return;
    }

    for (int i = 0; i < 100 && !authRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // batch: single order in array
    nlohmann::json orderData = nlohmann::json::array();
    nlohmann::json order;
    order["contract_code"] = "SPX500-USDT";
    order["margin_mode"] = "cross";
    order["position_side"] = "long";
    order["side"] = "buy";
    order["type"] = "limit";
    order["price"] = "7300";
    order["volume"] = "1";
    orderData.push_back(order);

    std::string cid = ws.PlaceBatchOrders(orderData.dump());
    LOG(INFO) << "Sent place_batch_orders with cid: " << cid;

    for (int i = 0; i < 100 && !respRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(authRecv) << "auth not received";
    EXPECT_TRUE(respRecv) << "place_batch_orders response not received within 10s";
    EXPECT_FALSE(respData.empty()) << "place_batch_orders data empty";

    // check order_id，随后撤单清理（避免单独跑本用例时账户里留挂单）
    try {
        auto dataArr = nlohmann::json::parse(respData);
        EXPECT_TRUE(dataArr.is_array()) << "response data should be array";
        EXPECT_FALSE(dataArr.empty()) << "response data array empty";
        huobi_futures::linear_swap::restful::OrderClient rest(config["AccessKey"], config["SecretKey"]);
        for (auto &item : dataArr) {
            if (item.contains("order_id")) {
                auto cancel = rest.CancelTradeOrder("SPX500-USDT", item["order_id"].get<std::string>(), "");
                if (cancel) EXPECT_EQ(cancel->code.value_or(0), 200) << "cleanup cancel_order failed";
            }
        }
    } catch (const std::exception &e) {
        FAIL() << "Failed to parse response data: " << e.what();
    }
}

TEST_F(WSTradeTest, CancelOrder) {
    extern map<string, string> config;

    std::atomic<bool> authRecv(false);
    std::atomic<bool> placeRecv(false);
    std::atomic<bool> cancelRecv(false);
    std::string placedOrderId;
    std::string cancelData;

    WSSwapTradeClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect([&](const std::string &response) {
        LOG(INFO) << "trade response: " << response;

        auto msg = nlohmann::json::parse(response);

        if (msg.contains("op") && msg["op"].get<std::string>() == "auth") {
            if (msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                authRecv = true;
            }
            return;
        }

        if (!msg.contains("code") || msg["code"].get<int>() != 200) {
            return;
        }

        std::string cid = msg.contains("cid") ? msg["cid"].get<std::string>() : "";
        if (cid == "1" && !placeRecv) {
            // place_order response
            if (msg.contains("data")) {
                auto data = msg["data"];
                if (data.contains("order_id")) {
                    placedOrderId = data["order_id"].get<std::string>();
                }
            }
            placeRecv = true;
        } else if (cid == "2" && placeRecv) {
            // cancel_order response
            if (msg.contains("data")) {
                cancelData = msg["data"].dump();
            }
            cancelRecv = true;
        }
    })) {
        FAIL() << "WS connect failed";
        return;
    }

    for (int i = 0; i < 100 && !authRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // place order
    nlohmann::json orderData;
    orderData["contract_code"] = "SPX500-USDT";
    orderData["margin_mode"] = "cross";
    orderData["position_side"] = "long";
    orderData["side"] = "buy";
    orderData["type"] = "limit";
    orderData["price"] = "7300";
    orderData["volume"] = "1";

    ws.PlaceOrder(orderData.dump());

    for (int i = 0; i < 100 && !placeRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ASSERT_FALSE(placedOrderId.empty()) << "Failed to place order";

    // cancel order
    nlohmann::json cancelReq;
    cancelReq["contract_code"] = "SPX500-USDT";
    cancelReq["order_id"] = placedOrderId;

    ws.CancelOrder(cancelReq.dump());

    for (int i = 0; i < 100 && !cancelRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(cancelRecv) << "cancel_order response not received within 10s";
    EXPECT_FALSE(cancelData.empty()) << "cancel_order data empty";

    try {
        auto data = nlohmann::json::parse(cancelData);
        EXPECT_TRUE(data.contains("order_id")) << "order_id missing in cancel response";
    } catch (const std::exception &e) {
        FAIL() << "Failed to parse cancel response data: " << e.what();
    }
}

TEST_F(WSTradeTest, CancelBatchOrders) {
    extern map<string, string> config;

    std::atomic<bool> authRecv(false);
    std::atomic<bool> placeRecv(false);
    std::atomic<bool> cancelRecv(false);
    std::string placedOrderId;
    std::string cancelData;

    WSSwapTradeClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect([&](const std::string &response) {
        LOG(INFO) << "trade response: " << response;

        auto msg = nlohmann::json::parse(response);

        if (msg.contains("op") && msg["op"].get<std::string>() == "auth") {
            if (msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                authRecv = true;
            }
            return;
        }

        if (!msg.contains("code") || msg["code"].get<int>() != 200) {
            return;
        }

        std::string cid = msg.contains("cid") ? msg["cid"].get<std::string>() : "";
        if (cid == "1" && !placeRecv) {
            if (msg.contains("data")) {
                auto data = msg["data"];
                if (data.contains("order_id")) {
                    placedOrderId = data["order_id"].get<std::string>();
                }
            }
            placeRecv = true;
        } else if (cid == "2" && placeRecv) {
            if (msg.contains("data")) {
                cancelData = msg["data"].dump();
            }
            cancelRecv = true;
        }
    })) {
        FAIL() << "WS connect failed";
        return;
    }

    for (int i = 0; i < 100 && !authRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // place order
    nlohmann::json orderData;
    orderData["contract_code"] = "SPX500-USDT";
    orderData["margin_mode"] = "cross";
    orderData["position_side"] = "long";
    orderData["side"] = "buy";
    orderData["type"] = "limit";
    orderData["price"] = "7300";
    orderData["volume"] = "1";

    ws.PlaceOrder(orderData.dump());

    for (int i = 0; i < 100 && !placeRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    ASSERT_FALSE(placedOrderId.empty()) << "Failed to place order";

    // cancel batch
    nlohmann::json cancelReq;
    cancelReq["contract_code"] = "SPX500-USDT";
    cancelReq["order_id"] = nlohmann::json::array({placedOrderId});

    ws.CancelBatchOrders(cancelReq.dump());

    for (int i = 0; i < 100 && !cancelRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(cancelRecv) << "cancel_batch_orders response not received within 10s";
    EXPECT_FALSE(cancelData.empty()) << "cancel_batch_orders data empty";

    try {
        auto dataArr = nlohmann::json::parse(cancelData);
        EXPECT_TRUE(dataArr.is_array()) << "response data should be array";
        EXPECT_FALSE(dataArr.empty()) << "response data array empty";
    } catch (const std::exception &e) {
        FAIL() << "Failed to parse cancel response data: " << e.what();
    }
}

TEST_F(WSTradeTest, CancelAllOrders) {
    extern map<string, string> config;

    std::atomic<bool> authRecv(false);
    std::atomic<bool> placeRecv(false);
    std::atomic<bool> cancelRecv(false);
    std::string cancelData;

    WSSwapTradeClient ws(config["AccessKey"], config["SecretKey"], config["Host"]);
    if (!ws.Connect([&](const std::string &response) {
        LOG(INFO) << "trade response: " << response;

        auto msg = nlohmann::json::parse(response);

        if (msg.contains("op") && msg["op"].get<std::string>() == "auth") {
            if (msg.contains("err-code") && msg["err-code"].get<int>() == 0) {
                authRecv = true;
            }
            return;
        }

        if (!msg.contains("code") || msg["code"].get<int>() != 200) {
            return;
        }

        std::string cid = msg.contains("cid") ? msg["cid"].get<std::string>() : "";
        if (cid == "1" && !placeRecv) {
            placeRecv = true;
        } else if (cid == "2" && placeRecv) {
            if (msg.contains("data")) {
                cancelData = msg["data"].dump();
            }
            cancelRecv = true;
        }
    })) {
        FAIL() << "WS connect failed";
        return;
    }

    for (int i = 0; i < 100 && !authRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // place order
    nlohmann::json orderData;
    orderData["contract_code"] = "SPX500-USDT";
    orderData["margin_mode"] = "cross";
    orderData["position_side"] = "long";
    orderData["side"] = "buy";
    orderData["type"] = "limit";
    orderData["price"] = "7300";
    orderData["volume"] = "1";

    ws.PlaceOrder(orderData.dump());

    for (int i = 0; i < 100 && !placeRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // cancel all
    nlohmann::json cancelReq;
    cancelReq["contract_code"] = "SPX500-USDT";
    cancelReq["margin_mode"] = "cross";

    ws.CancelAllOrders(cancelReq.dump());

    for (int i = 0; i < 100 && !cancelRecv; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.Disconnect();

    EXPECT_TRUE(cancelRecv) << "cancel_all_orders response not received within 10s";
    EXPECT_FALSE(cancelData.empty()) << "cancel_all_orders data empty";

    try {
        auto dataArr = nlohmann::json::parse(cancelData);
        EXPECT_TRUE(dataArr.is_array()) << "response data should be array";
    } catch (const std::exception &e) {
        FAIL() << "Failed to parse cancel_all response data: " << e.what();
    }
}
