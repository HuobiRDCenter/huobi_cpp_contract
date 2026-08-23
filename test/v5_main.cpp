#include <gtest/gtest.h>
#include <glog/logging.h>
#include "v5_restful_account_market_test.hpp"
#include "v5_restful_trade_position_test.hpp"
#include "v5_restful_algo_test.hpp"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}