//
// Created by Xhy_m on 2022/7/12.
//

#ifndef XIAHHHYYY_REACTOR_H
#define XIAHHHYYY_REACTOR_H
#include "event_handler.h"
#include "io_multiplex.h"
#include "thread_pool.h"

class reactor:public thread_pool
{
public:
    reactor();

    ~reactor();

    void start_server();

    void stop_server();

protected:
    void work_thread() override;

private:
    void sock_server();

    int sock_fd;

    std::list<client_data> list_fd;

    event_handler* m_event_handler;

    io_multiplex* m_io_multiplex;

    bool exit;

};


#endif //XIAHHHYYY_REACTOR_H
