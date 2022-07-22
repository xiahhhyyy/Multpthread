cmake_minimum_required(VERSION 3.0)
project(my_http)

add_executable(my_http main.cpp)
target_include_directories(my_http PRIVATE ../common/)
target_link_libraries(my_http event)