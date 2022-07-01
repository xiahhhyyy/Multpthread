//
// Created by Xhy_m on 2022/6/24.
//

#ifndef XIAHHHYYY_EPOLL_CLIENT_H
#define XIAHHHYYY_EPOLL_CLIENT_H
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <fcntl.h>
#include <arpa/inet.h>

using namespace std;
class epoll_client
{
public:
    epoll_client();

    ~epoll_client();

    bool start();

private:
    int sock_fd;

    char *server_ip;

    int port;

};


#endif //XIAHHHYYY_EPOLL_CLIENT_H
