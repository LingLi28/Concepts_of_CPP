cmake_minimum_required(VERSION 3.14)
project(hw02)
set(CMAKE_CXX_STANDARD 20)


add_library(hw02 STATIC combinatorics.cpp)

target_include_directories(hw02 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_NAME runhw02)
add_executable(${EXECUTABLE_NAME} run.cpp)


target_link_libraries(${EXECUTABLE_NAME} hw02)