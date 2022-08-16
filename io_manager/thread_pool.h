//
// Created by Xhy_m on 2022/7/12.
//

#ifndef XIAHHHYYY_THREAD_POOL_H
#define XIAHHHYYY_THREAD_POOL_H
#include "pthread.h"
#include "list"

class thread_pool
{
public:
    explicit thread_pool(int thread_count = 4);

    virtual ~thread_pool();
protected:
    virtual void work_thread() = 0;

    void start_thread_pool();

    int m_thread_count;

    pthread_mutex_t m_thread_mutex{};

    pthread_cond_t m_thread_cond{};
private:
    static void *call_func(void*);

    pthread_t *m_thread_id;
};



#endif //XIAHHHYYY_THREAD_POOL_H
