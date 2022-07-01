//
// Created by Xhy_m on 2022/6/24.
//

#ifndef XIAHHHYYY_EPOLL_SERVER_H
#define XIAHHHYYY_EPOLL_SERVER_H
#include "epoll_client.h"

struct client_param{
    int socket_fd;
    sockaddr_in client_address;
};

class epoll_server
{
public:
    epoll_server();

    ~epoll_server();

    bool start();

    bool end();

private:
    static void* work_pthread(void* param);

    bool my_epoll_ctl(int option, int fd, epoll_event *event) const;

    int socket_fd;

    int epoll_fd;

    int thread_num;

    bool isExit;

    pthread_t* thread_id;

    int thread_index;
};


#endif //XIAHHHYYY_EPOLL_SERVER_H
