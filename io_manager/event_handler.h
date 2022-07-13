//
// Created by Xhy_m on 2022/7/12.
//

#ifndef XIAHHHYYY_EVENT_HANDLER_H
#define XIAHHHYYY_EVENT_HANDLER_H

#include "io_multiplex.h"
#include "cstring"
//单例类
struct client_data
{
    int fd;
    int epoll_event;
    int offset;
    io_multiplex* io_obj;
};

class event_handler
{
public:

    void process_func(client_data* data);

    event_handler() = default;

    ~event_handler() = default;

private:
};


#endif //XIAHHHYYY_EVENT_HANDLER_H
