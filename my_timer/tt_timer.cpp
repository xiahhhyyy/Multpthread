//
// Created by Xhy_m on 2022/8/15.
//

#include "tt_timer.h"

tt_timer::tt_timer()
{
    epoll_fd = epoll_create(1);
    exit_fd = eventfd(0, 0);
    exit = false;
    start_thread_pool();

    pthread_t id;
    pthread_create(&id, nullptr, tt_timer::run, this);
    pthread_detach(id);
}

tt_timer::~tt_timer()
{
    exit = true;
    eventfd_write(exit_fd, 1);
    int i = 5;  //超时时间为5秒
    while(i>0){
        pthread_cond_broadcast(&m_thread_cond);
        if(cur_thread_count == 0) break;
        sleep(1);
        --i;
    }

    if(cur_thread_count){
        //异常处理
    }
    close(epoll_fd);
    close(exit_fd);
}

int tt_timer::create_timer(const timer_data &data)
{
    pthread_mutex_lock(&m_thread_mutex);
    m_set.insert(data);
    pthread_mutex_unlock(&m_thread_mutex);
}

void *tt_timer::run(void *arg)
{
    auto *obj= (tt_timer*)arg;

    //在Epoll上注册线程退出事件
    epoll_event ev{};
    ev.data.fd = obj->exit_fd;
    ev.events = EPOLLIN | EPOLLONESHOT;
    if(0 != epoll_ctl(obj->epoll_fd, EPOLL_CTL_ADD, obj->exit_fd, &ev)){
        cout << "epoll_ctl error, msg:" << strerror(errno) << endl;
    }

    time_t cur_time = time(nullptr);
    time_t last_time = cur_time-4;
    while(!obj->exit)
    {
        cur_time = time(nullptr);
        time_t timeout = (8 - (cur_time - last_time))*1000;
        if(timeout <= 0){
            timeout = 1;
        }
        epoll_event event[1] = {0};

        int ret = epoll_wait(obj->epoll_fd, event, 1, timeout);
        if( ret == 1 && event[0].data.fd == obj->exit_fd && event[0].events & EPOLLIN){
            cout << "exit event" << endl;
            break;
        }

        obj->tick();
        last_time = cur_time;
    }
    return nullptr;
}

void tt_timer::tick()
{
    pthread_mutex_lock(&m_thread_mutex);
    time_t cur_time = time(nullptr);
    cout <<"time = " << time(nullptr) << endl;
    cout << "set.size() = " << m_set.size() << endl;
    if(!m_set.empty() && m_set.begin()->trig_time <= cur_time){
        pthread_cond_broadcast(&m_thread_cond);
    }
    pthread_mutex_unlock(&m_thread_mutex);
}

void tt_timer::work_thread()
{
    while(!exit){
        pthread_mutex_lock(&m_thread_mutex);
        time_t cur_time = time(nullptr);
        while((m_set.empty() || m_set.begin()->trig_time > cur_time)){
            pthread_cond_wait(&m_thread_cond, &m_thread_mutex);
            if(exit){
                pthread_mutex_unlock(&m_thread_mutex);
                return;
            }
            cur_time = time(nullptr);
        }
        timer_data data = *m_set.begin();
        m_set.erase(m_set.begin());
        pthread_mutex_unlock(&m_thread_mutex);
        handler(data);
    }
}


