
set(SRCS
    CThread.cpp
    main.cpp)
add_executable(xx ${SRCS} )
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_link_libraries(xx PUBLIC libpthread.so)
endif()