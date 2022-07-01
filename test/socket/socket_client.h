//
// Created by Xhy_m on 2022/6/15.
//
#ifndef XIAHHHYYY_SOCKET_CLIENT_H
#define XIAHHHYYY_SOCKET_CLIENT_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
using namespace std;




class socket_client
{
public:
    socket_client();

    ~socket_client();

    void set_addr(const char* ip, short port);

    bool connect_server()const;
private:
    sockaddr_in m_server_addr;
    int m_socket_fd;

    int pthread_arr[5];

};


#endif //XIAHHHYYY_SOCKET_CLIENT_H
