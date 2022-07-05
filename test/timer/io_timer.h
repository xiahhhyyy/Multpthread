//
// Created by Xhy_m on 2022/7/4.
//

#ifndef XIAHHHYYY_MY_TIMER_H
#define XIAHHHYYY_MY_TIMER_H
#include <sys/eventfd.h>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

struct my_timer{
    my_timer* next;

    void (*callback)(void*);
    time_t expire_time;
    bool is_continue;
};


//定时器最大精度为10秒
class io_timer
{
public:
    io_timer();

    ~io_timer();

    void add_timer(struct my_timer* timer);

private:

    void del_timer(struct my_timer* timer);

    void wake_up();

    void deal_mission();

    my_timer* head;

    my_timer* tail;

    int event_fd;

    time_t cur_time;

};


#endif //XIAHHHYYY_MY_TIMER_H
