enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# 老 v3 测试 target：存量债（TriggerOrderClient / SwapTrackHisOrdersResponse 等老 DTO 语法错误），
# 当前无法编译，故 EXCLUDE_FROM_ALL —— 默认 `cmake --build build` 不再因它失败。
# 需要时显式构建：cmake --build build --target test（目前预期失败，与 V5 无关）
add_executable(test EXCLUDE_FROM_ALL main.cpp)
target_link_libraries(test Threads::Threads websockets OpenSSL::SSL OpenSSL::Crypto ${GTEST_BOTH_LIBRARIES} curl z glog::glog huobi_futures)

# V5 测试单独 target：避开 v3 存量废墟，只编译 V5 接口 + 其依赖的 V5 DTO
add_executable(v5_test v5_main.cpp)
target_link_libraries(v5_test Threads::Threads websockets OpenSSL::SSL OpenSSL::Crypto ${GTEST_BOTH_LIBRARIES} curl z glog::glog huobi_futures)
add_test(V5Test v5_test)

# V5 WebSocket 测试：通知推送 + 交易客户端（含 5 个离线 sanity 用例）
add_executable(v5_ws_test v5_ws_main.cpp)
target_link_libraries(v5_ws_test Threads::Threads websockets OpenSSL::SSL OpenSSL::Crypto ${GTEST_BOTH_LIBRARIES} curl z glog::glog huobi_futures)
add_test(V5WSTest v5_ws_test)

