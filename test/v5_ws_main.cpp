#include <gtest/gtest.h>
#include <glog/logging.h>

// Include sanity tests
#include "v5_ws_sanity_test.hpp"

// Include notification and trade tests
#include "v5_ws_notify_test.hpp"
#include "v5_ws_trade_test.hpp"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
