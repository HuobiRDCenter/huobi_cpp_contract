#include <gtest/gtest.h>
#include <glog/logging.h>
#include "huobi_futures/linear_swap/restful/OrderClient.hpp"
#include "config.hpp"
#include "v5_restful_account_market_test.hpp"
#include "v5_restful_trade_position_test.hpp"
#include "v5_restful_algo_test.hpp"

// trade/position 写测试要求账户 dual_side（下单必带 position_side）。
// 全局 SetUp 把账户切到 dual_side，对齐 Java TradeAPITest 的切换步骤。
struct PositionModeEnv : public ::testing::Environment
{
    void SetUp() override
    {
        init_config();
        if (config["AccessKey"].find("x-x-x") != string::npos) return; // 无 key，跳过
        huobi_futures::linear_swap::restful::OrderClient client(config["AccessKey"], config["SecretKey"]);
        auto current = client.PositionMode();
        if (!current || current->code.value_or(0) != 200 || !current->data.has_value())
        {
            GTEST_FAIL() << "V5 setup: unable to read current position mode; "
                            "refusing to run dual_side-dependent trade/position tests with an unknown mode";
            return;
        }
        if (current->data->position_mode == "dual_side")
        {
            LOG(INFO) << "V5 setup: position mode is dual_side";
            return;
        }

        auto r = client.SetPositionMode("dual_side");
        if (!r || r->code.value_or(0) != 200)
        {
            GTEST_FAIL() << "V5 setup: unable to establish dual_side, code="
                         << (r ? r->code.value_or(0) : -1)
                         << " message=" << (r ? r->message.value_or("") : "no response");
            return;
        }

        auto verified = client.PositionMode();
        if (!verified || verified->code.value_or(0) != 200 || !verified->data.has_value() ||
            verified->data->position_mode != "dual_side")
        {
            GTEST_FAIL() << "V5 setup: position mode is not dual_side after SetPositionMode";
            return;
        }
        LOG(INFO) << "V5 setup: position mode set to dual_side";
    }
};

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new PositionModeEnv);
    return RUN_ALL_TESTS();
}
