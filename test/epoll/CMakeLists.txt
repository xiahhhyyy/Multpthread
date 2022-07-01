cmake_minimum_required(VERSION 3.0)
project(epoll_test)
set(CMAKE_CXX_STANDARD 11)
set(SRC main.cpp
        epoll_client.cpp
        epoll_server.cpp)
add_executable(epoll_test ${SRC})
target_link_libraries(epoll_test libpthread.so)