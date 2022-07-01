cmake_minimum_required(VERSION 3.0)
project(socket_test)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG})
set(SRCS
    socket_server.cpp
    socket_client.cpp
    socket_main.cpp)
add_executable(socket_test ${SRCS})

