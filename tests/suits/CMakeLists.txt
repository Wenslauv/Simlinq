cmake_minimum_required(VERSION 3.10)

project(suits)


set(SOURCES
    optional.cpp
    generating.cpp
    check.cpp
)

add_library(suits STATIC
    ${SOURCES}
)

target_include_directories(suits PRIVATE 
    ../../include
    ../../third-party/unittest-cpp
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
