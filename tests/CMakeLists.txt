cmake_minimum_required(VERSION 3.10)

project(sltests)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(../third-party/unittest-cpp unittest++) 
add_subdirectory(suits)
add_subdirectory(runner)
