cmake_minimum_required(VERSION 3.10)
project(da)

set(CMAKE_CXX_STANDARD 17)

add_executable(da arr_test.cpp da.cpp)

enable_testing()

find_package(GTest CONFIG REQUIRED)
target_link_libraries(da PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

add_test(AllTestsInMain da)

