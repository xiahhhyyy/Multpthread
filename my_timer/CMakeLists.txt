cmake_minimum_required(VERSION 3.0)
project(timer)

set(CMAKE_CXX_STANDARD 11)
include_directories(../io_manager)

add_executable(timer main.cpp tt_timer.cpp ../io_manager/thread_pool.cpp)
target_link_libraries(timer event pthread)