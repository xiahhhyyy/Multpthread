cmake_minimum_required(VERSION 3.0)
project(socket_client)

add_executable(client main.cpp)

target_link_libraries(client event)