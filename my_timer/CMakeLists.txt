cmake_minimum_required(VERSION 3.0)
project(timer)

set(CMAKE_CXX_STANDARD 11)
include_directories(../io_manager)

set(src main.cpp
        tt_timer.cpp
        ../io_manager/thread_pool.cpp
        day_timer.cpp
        period_timer.cpp)
add_executable(timer ${src})
target_link_libraries(timer event pthread)