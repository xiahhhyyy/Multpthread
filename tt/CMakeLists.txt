cmake_minimum_required(VERSION 3.0)
project(tt)
set(CMAKE_CXX_STANDARD 11)

include_directories( ../common /root/client/include)

set(src main.cpp
        ../common/common.cpp
        ../common/my_shared_ptr.cpp
        ../common/CMicInteger.cpp)
add_executable(tt ${src})
link_libraries(/root/client/lib/x86_64/libjsoncpp.so)
target_link_libraries(tt pthread)