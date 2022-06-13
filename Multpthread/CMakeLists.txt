
set(SRCS
    CThread.cpp
    main.cpp)
add_executable(my ${SRCS} )
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES Windows)
    target_link_libraries(my PUBLIC libpthread.so)
endif()