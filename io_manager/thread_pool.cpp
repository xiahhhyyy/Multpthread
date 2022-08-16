//
// Created by Xhy_m on 2022/7/12.
//

#include "thread_pool.h"

thread_pool::thread_pool(int thread_count):
    m_thread_count(thread_count)
{
    m_thread_id = new pthread_t[m_thread_count];
    m_thread_mutex = PTHREAD_MUTEX_INITIALIZER;
    m_thread_cond = PTHREAD_COND_INITIALIZER;
}

thread_pool::~thread_pool()
{
    delete []m_thread_id;
}

void thread_pool::start_thread_pool()
{
    //创建线程
    for(int i=0; i<m_thread_count; ++i){
        if(0!=pthread_create(m_thread_id+i, nullptr, call_func, this)){
            //异常处理
        }
        pthread_detach(*(m_thread_id+i));
    }
}

void *thread_pool::call_func(void *param)
{
    auto obj = (thread_pool*)param;
    obj->work_thread();
    return obj;
}











