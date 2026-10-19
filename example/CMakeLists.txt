add_executable(example main.cpp)
target_link_libraries(example curl glog::glog huobi_futures)

# V5 最小示例：公开行情 +（有 key 时）账户/交易查询
add_executable(v5_example v5_example.cpp)
target_link_libraries(v5_example curl z OpenSSL::SSL OpenSSL::Crypto glog::glog huobi_futures)
