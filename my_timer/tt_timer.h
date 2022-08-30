//
// Created by Xhy_m on 2022/8/15.
//

#ifndef XIAHHHYYY_TT_TIMER_H
#define XIAHHHYYY_TT_TIMER_H
#include "sys/epoll.h"
#include "map"
#include "iostream"
#include "unistd.h"
#include "mutex"
#include "sys/select.h"
#include "sys/eventfd.h"
#include "string"
#include "cstring"
#include <cerrno>
#include "thread_pool.h"
#include "unordered_set"
#include "unordered_map"
#include "set"

using namespace std;
class tt_timer;
struct timer_data
{
    void (*cb_func)(tt_timer *obj, void* arg);
    void *arg;
    time_t trig_time;
    time_t timeT;
    timer_data():arg(nullptr),cb_func(nullptr),trig_time(0),timeT(0){}
    bool operator<(const timer_data &obj) const{
        return this->trig_time < obj.trig_time;
    }
};

class tt_timer:public thread_pool
{
public:

    tt_timer();

    ~tt_timer() override;

    int create_timer(const timer_data &data);


private:
    void tick();

    inline void handler(const timer_data &data){
        data.cb_func(this, data.arg);
    };

    void work_thread() override;

private:
    static void *run(void* arg);

private:
    int epoll_fd;

    bool exit;

    int exit_fd;

    list<timer_data> m_list;

    multiset<timer_data> m_set;

    map<int, multiset<timer_data>::iterator> m_map;
};


#endif //XIAHHHYYY_TT_TIMER_H
