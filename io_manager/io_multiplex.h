//
// Created by Xhy_m on 2022/7/12.
//

#ifndef XIAHHHYYY_IO_MULTIPLEX_H
#define XIAHHHYYY_IO_MULTIPLEX_H
#include "sys/epoll.h"
#include "string"
#include "iostream"
#include <unistd.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "cstring"

using namespace std;
class io_multiplex
{
public:
    io_multiplex();

    explicit io_multiplex(int max_count);

    ~io_multiplex();

    void register_event(int fd, int epoll_events) const;

    void modify_event(int fd, int epoll_events)const;

    void remove_event(int fd) const;

    int my_epoll(epoll_event* event) const;

private:


    int epoll_fd;

    int max_event;
};


#endif //XIAHHHYYY_IO_MULTIPLEX_H
