cmake_minimum_required(VERSION 3.0)
project(timer_test)
set(CMAKE_CXX_STANDARD 11)

add_executable(timer_test timer_main.cpp my_signal.cpp io_timer.cpp)

