cmake_minimum_required(VERSION 3.17)
project(TheRoadToAdvancement)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(include/DataStructure)

add_executable(TheRoadToAdvancement src/main.cpp src/DailyCoding.cpp)