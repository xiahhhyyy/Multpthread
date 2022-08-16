//
// Created by Xhy_m on 2022/8/12.
//

#include "util_timer.h"
util_timer::util_timer():
    pre(nullptr),
    next(nullptr),
    expire_time(INT64_MAX)
{
    data = new timer_data;
    data->str = "默认";
}


util_timer::~util_timer()
{
    delete data;
}

timer_manager::timer_manager():
    head(nullptr),
    tail(nullptr)
{}

timer_manager::~timer_manager()
{
    util_timer* tmp = head;
    while(tmp){
        head = tmp->next;
        delete tmp;
        tmp = head;
    }
}

void timer_manager::add_timer(util_timer *timer)
{
    if(!timer){
        return;
    }

    if(!head){
        head = tail = timer;
        return;
    }

    if(timer->expire_time < head->expire_time){
        timer->next = head;
        head->pre = timer;
        head = timer;
        return;
    }
    add_timer(timer, head);
}

void timer_manager::delete_timer(util_timer *timer)
{
    if(!timer){
        return;
    }

    if(timer==head && timer==tail){
        delete timer;
        head = tail = nullptr;
        return;
    }

    if(timer == head && timer != tail){
        head=head->next;
        head->pre = nullptr;
        delete timer;
        return;
    }

    if(timer != head && timer == tail){
        tail = tail->pre;
        tail->next = nullptr;
        delete timer;
        return;
    }

    timer->pre->next = timer->next;
    timer->next->pre = timer->pre;
}

void timer_manager::tick()
{
    auto cur_time = time(nullptr);
    while(head &&  head->expire_time <= cur_time){
        cout << 123 << endl;
        head->cb_func(head->data);
        delete_timer(head);
    }
}

void timer_manager::adjust_timer(util_timer *timer)
{
    if(!timer){
        return;
    }

    util_timer *tmp = timer->next;

    if(!tmp || timer->expire_time <= tmp->expire_time){
        return;
    }

    if(timer == head){
        head = head->next;
        head->pre = nullptr;
        timer->next = nullptr;
        add_timer(timer, head);
    }else{
        util_timer* pre = timer->pre;
        util_timer* next = timer->next;

        pre->next = next;
        next->pre = pre;
        add_timer(timer, timer->next);
    }

}

void timer_manager::add_timer(util_timer *timer, util_timer *lst_timer)
{
    while(lst_timer && timer->expire_time > lst_timer->expire_time){
        lst_timer = lst_timer->next;
    }

    if(!lst_timer){
        tail->next = timer;
        timer->pre = tail;
        tail = timer;
    }else{
        lst_timer->pre->next = timer;
        timer->pre = lst_timer->pre;
        timer->next = lst_timer;
        lst_timer->pre = timer;
    }
}


