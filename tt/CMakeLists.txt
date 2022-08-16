cmake_minimum_required(VERSION 3.0)
project(tt)
set(CMAKE_CXX_STANDARD 11)

include_directories( ../common)
set(src main.cpp
        ../common/common.cpp
        ../common/my_shared_ptr.cpp)
add_executable(tt ${src})