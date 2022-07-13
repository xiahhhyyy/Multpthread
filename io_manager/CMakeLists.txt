project(io_manager)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.0)
add_definitions("-Wall -g")

add_executable(io_manager
        thread_pool.cpp
        event_handler.cpp
        io_multiplex.cpp
        reactor.cpp
        main.cpp)

target_link_libraries(io_manager libpthread.so)
