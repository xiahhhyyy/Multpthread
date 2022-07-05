//
// Created by Xhy_m on 2022/7/4.
//

#include "io_timer.h"

io_timer::io_timer():
    event_fd(-1),
    head(nullptr),
    tail(nullptr)
{
    event_fd = eventfd(0, 0);

}

io_timer::~io_timer()
{
    while(head){
        auto tmp = head;
        head = head->next;
        delete tmp;
        tmp = nullptr;
    }
    tail = nullptr;
    close(event_fd);
}

void io_timer::add_timer(struct my_timer *timer)
{
    if(!timer) return;
    auto* target = new my_timer;
    memcpy(target, timer, sizeof(my_timer));

    //防止传入的定时器指针瞎指向其它地址
    target->next = nullptr;

    if(!head){
        head = target;
        tail = head;
        return;
    }

    if(head->expire_time >= target->expire_time){
        target->next = head;
        head = target;
        return;
    }

    if(tail->expire_time <= target->expire_time){
        tail->next = target;
        tail = target;
        return;
    }

    auto tmp = head;
    while(tmp && target->expire_time > tmp->expire_time){
        tmp = tmp->next;
    }

    if(tmp){    //正常情况tmp不可能为null
        target->next = tmp->next;
        tmp->next = target;
    }
}

void io_timer::del_timer(struct my_timer *timer)
{
    if(!timer) return;

    if(!head) return;

    time_t expire_time = timer->expire_time;
    while(head && head->expire_time <= expire_time){
        auto tmp = head;
        head = head->next;
        if(tmp == timer) timer = nullptr;
        delete tmp ;
    }

    if(!head) tail = nullptr;
}

void io_timer::wake_up()
{
    fd_set tmp, reads;
    FD_ZERO(&tmp);
    FD_ZERO(&reads);
    FD_SET(event_fd, &tmp);
    timeval time_out{};
    time_out.tv_usec = 0;
    time_out.tv_sec = 10;
    time_t start_time, end_time;
    start_time = time(nullptr);
    unsigned long count = 0;
    while(true){
        reads = tmp;
        end_time = time(nullptr);
        time_out.tv_sec = end_time - start_time - count*10 + 10;
        select(event_fd+1, &reads, nullptr, nullptr, &time_out);
        cur_time = time(nullptr);
        if(cur_time - 10 < end_time){
            sleep(cur_time - end_time - 10);
        }

        deal_mission();

        ++count;
    }
}

void io_timer::deal_mission()
{

}
