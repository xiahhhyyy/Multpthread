//
// Created by Xhy_m on 2022/8/12.
//

#include "libevent_timer.h"
libevent_timer *libevent_timer::get_obj()
{
    if(!m_obj){
        cout << 123 << endl;
        m_obj = new libevent_timer;
    }
    return m_obj;
}

timer* libevent_timer::create_timer(void(*cb_func)(int fd, short event,void* arg), time_t start_time, time_t cycle_time)
{
    time_t cur = time(nullptr);
    auto* arg = new my_arg;

    arg->arg = nullptr;
    arg->base = base;
    arg->cb_func = cb_func;
    arg->cycle_time = cycle_time;
    arg->my_map = &my_map;
    arg->mut = my_mutex;



    auto *ret = new timer;
    ret->ev = event_new(base, -1, EV_ET, libevent_timer::first, arg);
    arg->tt = ret;
    timeval timeout{};
    if(start_time <= cur){
        timeout.tv_sec = 0;
        timeout.tv_usec = 100;
    }else{
        timeout.tv_sec = start_time - cur;
        timeout.tv_usec = 0;
    }
    event_add(ret->ev, &timeout);
    my_mutex->lock();
    my_map.insert(std::make_pair(ret, nullptr));
    my_mutex->unlock();
    return ret;
}

void libevent_timer::cancel_timer(timer* tt){
    my_mutex->lock();
    if(my_map.count(tt) == 0){
        return;
    }
    if(my_map[tt] == nullptr){
        event_free(tt->ev);
    }else{
        event_free(my_map[tt]);
        event_free(tt->ev);
    }
    my_map.erase(tt);
    my_mutex->unlock();
}

void libevent_timer::start()
{
    event_base_dispatch(base);
}

void libevent_timer::stop()
{

}

void libevent_timer::first(int fd, short event, void *arg)
{
    auto *param = (my_arg*)arg;
    cout << param->mut << endl;
    mutex* my_mutex = param->mut;

    unordered_map<timer*, struct event*> *my_map = param->my_map;

    my_mutex->lock();
    do{
        if(my_map->count(param->tt) == 0){
            break;
        }
        param->cb_func(-1, -1, param->arg);
        (*my_map)[param->tt] = event_new(param->base, -1, EV_PERSIST | EV_ET, param->cb_func, param->arg);
        timeval timeout{};
        timeout.tv_sec = param->cycle_time;
        timeout.tv_usec = 0;
        event_add((*my_map)[param->tt], &timeout);
    }while(false);
    my_mutex->unlock();
    delete param;
}

libevent_timer::libevent_timer():
    base(nullptr),
    my_mutex(nullptr)
{
    base = event_base_new();
    my_mutex = new mutex;
}

libevent_timer* libevent_timer::m_obj;


