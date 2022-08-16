//
// Created by Xhy_m on 2022/8/12.
//

#ifndef XIAHHHYYY_UTIL_TIMER_H
#define XIAHHHYYY_UTIL_TIMER_H
#include <ctime>
#include "string"
#include "iostream"

using namespace std;

//触发回调函数后, 传给回调函数的数据
struct tt_data
{
    //
    string str;
};


class util_timer
{
public:
    util_timer();
    //util_timer(const util_timer &obj);
    ~util_timer();

    void (*cb_func)(timer_data* arg);
    util_timer *pre;
    util_timer *next;
    timer_data *data;
    time_t expire_time;

};

class timer_manager
{
public:
    timer_manager();
    ~timer_manager();

    void add_timer(util_timer* timer);

    void delete_timer(util_timer* timer);

    void tick();

    util_timer* head;

    util_timer* tail;
private:
    void adjust_timer(util_timer* timer);

    void add_timer(util_timer* timer, util_timer* lst_timer);
};


#endif //XIAHHHYYY_UTIL_TIMER_H
