cmake_minimum_required(VERSION 3.10)

project(SimlinqTests VERSION 0.1)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(../third-party/unittest-cpp unittest++)

add_executable(SimlinqTests sources/runner.cpp)

target_link_libraries(SimlinqTests -force_load unittest++)