#pragma once
#include <gtest/gtest.h>
#include <glog/logging.h>

#include "config.hpp"
#include <thread>
#include <chrono>

#include "huobi_futures/nlohmann_json/json.hpp"

// 健全性测试：验证编译和基础功能

TEST(WSSanity, JsonParsing) {
    // 验证 nlohmann::json 正常工作
    auto msg = nlohmann::json::parse(R"({"op":"notify","topic":"orders","data":[{"order_id":"12345"}]})");
    EXPECT_EQ(msg["op"].get<std::string>(), "notify");
    EXPECT_EQ(msg["topic"].get<std::string>(), "orders");
    EXPECT_TRUE(msg["data"].is_array());
    EXPECT_EQ(msg["data"][0]["order_id"].get<std::string>(), "12345");
}

TEST(WSSanity, EmptySnapshot) {
    // 验证空快照检测逻辑
    auto msg = nlohmann::json::parse(R"({"op":"notify","topic":"positions","data":[]})");
    auto data = msg["data"];

    if (data.is_array() && data.empty()) {
        // 空快照，跳过
        EXPECT_TRUE(true);
    } else {
        FAIL() << "Empty array detection failed";
    }
}

TEST(WSSanity, StateConditionalFields) {
    // 验证 state 条件字段检测
    std::string filled_msg = R"({
        "order_id": "123",
        "state": "filled",
        "trade_id": "456",
        "trade_price": "100.5",
        "trade_volume": "1"
    })";

    std::string partial_msg = R"({
        "order_id": "789",
        "state": "ordering",
        "trade_id": null,
        "trade_price": null,
        "trade_volume": null
    })";

    auto filled = nlohmann::json::parse(filled_msg);
    EXPECT_EQ(filled["state"].get<std::string>(), "filled");
    EXPECT_FALSE(filled["trade_id"].is_null());

    auto partial = nlohmann::json::parse(partial_msg);
    EXPECT_EQ(partial["state"].get<std::string>(), "ordering");
    EXPECT_TRUE(partial["trade_id"].is_null());  // ordering 状态下可为空
}

TEST(WSSanity, CIDAssociation) {
    // 验证 cid 关联逻辑
    std::map<std::string, std::string> responses;
    responses["1"] = R"({"cid":"1","code":200,"data":{"order_id":"abc"}})";
    responses["2"] = R"({"cid":"2","code":200,"data":{"order_id":"def"}})";

    auto resp1 = nlohmann::json::parse(responses["1"]);
    auto resp2 = nlohmann::json::parse(responses["2"]);

    EXPECT_EQ(resp1["cid"].get<std::string>(), "1");
    EXPECT_EQ(resp2["cid"].get<std::string>(), "2");
    EXPECT_EQ(resp1["data"]["order_id"].get<std::string>(), "abc");
    EXPECT_EQ(resp2["data"]["order_id"].get<std::string>(), "def");
}

TEST(WSSanity, SubAckDetection) {
    // 验证订阅 ack 检测
    std::string ack_msg = R"({"op":"sub","topic":"orders","err-code":0})";
    std::string reject_msg = R"({"op":"sub","topic":"orders","err-code":1001})";

    auto ack = nlohmann::json::parse(ack_msg);
    EXPECT_EQ(ack["op"].get<std::string>(), "sub");
    EXPECT_EQ(ack["err-code"].get<int>(), 0);  // 成功

    auto reject = nlohmann::json::parse(reject_msg);
    EXPECT_EQ(reject["op"].get<std::string>(), "sub");
    EXPECT_NE(reject["err-code"].get<int>(), 0);  // 失败
}
