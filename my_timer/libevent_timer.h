//
// Created by Xhy_m on 2022/8/12.
//

#ifndef XIAHHHYYY_LIBEVENT_TIMER_H
#define XIAHHHYYY_LIBEVENT_TIMER_H
#include "event2/event.h"
#include "sys/eventfd.h"
#include "unordered_map"
#include "mutex"
#include "iostream"

using namespace std;

class timer{
public:
    time_t start_time;          //第一次开始时间
    void(*cb_func)(void*arg);   //回调函数
    time_t cycle_time;          //周期,单位为秒,为0则只执行一次
    event *ev;
};

class libevent_timer
{
public:
    static libevent_timer* get_obj();
private:
    static libevent_timer *m_obj;

    static void first(int fd, short event, void* arg);

public:
    timer* create_timer(void(*cb_func)(int fd, short event,void* arg), time_t start_time, time_t cycle_time);

    void cancel_timer(timer* tt);

    void start();

    void stop();
private:
    libevent_timer();

    ~libevent_timer();

    struct my_arg{
        time_t cycle_time;
        event_base *base;
        void(*cb_func)(int fd, short event, void* arg);
        void* arg;
        timer* tt;
        mutex* mut;
        unordered_map<timer*, event*> *my_map;
    };
    event_base* base;

    unordered_map<timer*, event*> my_map;
    
    mutex* my_mutex;
};

#endif //XIAHHHYYY_LIBEVENT_TIMER_H
