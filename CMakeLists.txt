cmake_minimum_required(VERSION 3.12)
project(TheRoadToAdvancement)

set(CMAKE_CXX_STANDARD 11)

# 添加编译选项
# add_definitions(-g -fpermissive -std=c++0x)

# 添加头文件目录
include_directories(./include)
include_directories(./include/DataStructure)

# 添加src文件夹内所有cpp文件
# CMAKE_CURRENT_SOURCE_DIR: 路径指向当前正在处理的源目录
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_MAIN)
add_executable(TheRoadToAdvancement ${SRC_MAIN})

# 添加需要链接的库文件目录
# LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/lib)
