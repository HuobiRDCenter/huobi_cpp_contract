enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test main.cpp)
target_link_libraries(test Threads::Threads websockets OpenSSL::SSL OpenSSL::Crypto ${GTEST_BOTH_LIBRARIES} curl z glog::glog huobi_futures)

# V5 测试单独 target：避开 v3 存量废墟（老 DTO/测试的 JS_OBJ 笔误与歧义），
# 只编译 V5 接口 + 其依赖的 V5 DTO
add_executable(v5_test v5_main.cpp)
target_link_libraries(v5_test Threads::Threads websockets OpenSSL::SSL OpenSSL::Crypto ${GTEST_BOTH_LIBRARIES} curl z glog::glog huobi_futures)
add_test(V5Test v5_test)