//
// Created by Xhy_m on 2022/6/15.
//

#ifndef XIAHHHYYY_COMMON_SOCKET_SERVER_H
#define XIAHHHYYY_SOCKET_SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include "sys/un.h"
using namespace std;

class socket_server
{
public:
    socket_server();

    ~socket_server();

    void set_listen_addr(const char* addr, uint16_t port);

    bool start_listen();

    void handle_request() const;

private:
    int m_sock_id;

    int m_accept_id;

    struct sockaddr_un m_server_sockaddr;

};


#endif //XIAHHHYYY_COMMON_SOCKET_SERVER_H
