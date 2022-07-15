//
// Created by Xhy_m on 2022/7/14.
//

#ifndef XIAHHHYYY_LIBEVENT_H
#define XIAHHHYYY_LIBEVENT_H
#include "event2/event.h"
#include "event2/bufferevent.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "cstring"
#include "string"
#include "iostream"

using namespace std;

class libevent
{
public:
    libevent();

    ~libevent();

    void start();

private:
    bool init_socket();

    struct my_argc{
        int m_socket_fd;

        event_base *ev_base;

        struct event* ev;
    };

    static void callback_func(int fd, short event, void *arg);

private:

    int m_socket_fd;

    event_base *ev_base;

    int m_src_file_fd;
};


#endif //XIAHHHYYY_LIBEVENT_H
