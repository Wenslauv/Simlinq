cmake_minimum_required(VERSION 3.10)

project(runner)

set(SOURCES runner.cpp)

add_executable(runner runner.cpp)


target_link_libraries(runner -force_load UnitTest++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

target_include_directories(runner PRIVATE 
    ../../third-party/unittest-cpp
)
