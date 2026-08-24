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
        auto r = client.SetPositionMode("dual_side");
        if (r && r->code.value_or(0) != 200)
        {
            LOG(WARNING) << "SetPositionMode dual_side failed, code=" << r->code.value_or(0);
        }
    }
};

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new PositionModeEnv);
    return RUN_ALL_TESTS();
}
