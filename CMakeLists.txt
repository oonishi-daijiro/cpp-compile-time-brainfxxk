cmake_minimum_required(VERSION 3.26)
project(cpp-meta-brainfxxk)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CXX_STANDARD C++20)
add_compile_options(-std=c++20 -ftemplate-depth=1000000)

add_executable(bf main.cpp)
