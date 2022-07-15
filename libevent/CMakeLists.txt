project(my_libevent)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

include_directories(../common)
set(src libevent.cpp
        main.cpp)

add_executable(my_libevent ${src})
target_link_libraries(my_libevent libpthread.so event)