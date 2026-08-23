PROJECT(huobi_futures_cpp)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS_DEBUG "-g")

find_package(gflags REQUIRED)
find_package(glog REQUIRED)
find_package(zlib REQUIRED)
find_package(curl REQUIRED)
find_package(libwebsockets REQUIRED)
find_package(GTest REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(OpenSSL REQUIRED)

add_subdirectory(huobi_futures)
add_subdirectory(example)
add_subdirectory(test)
