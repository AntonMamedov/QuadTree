cmake_minimum_required(VERSION 3.16)
project(QuadTree CXX)
set(CMAKE_CXX_STANDARD 20)


file(GLOB src "src/*.cpp")
include_directories(include)
add_subdirectory(unit_tests)