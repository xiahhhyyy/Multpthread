//
// Created by Xhy_m on 2022/6/13.
//

#include <pthread.h>
#include <iostream>
#include <sys/eventfd.h>
#include <unistd.h>
#include <sys/epoll.h>
using namespace std;
int efd1, efd2, efd3;
int epoll_fd;
bool isExit;

struct my_epoll{
    int max_events;
    int time_out;
    int ready_counts;
    epoll_event *ev;
};

class epoll_demo{
public:
    epoll_demo();

    ~epoll_demo();

    bool add_to_epoll(int fd, epoll_event* event) const;

    bool del_from_epoll(int fd, epoll_event* event) const;

    bool mod_from_epoll(int fd, epoll_event* event) const;

    void start_run(struct my_epoll &param) const;
private:
    int epoll_fd;
};

epoll_demo::epoll_demo()
    :epoll_fd(0){
    epoll_fd = epoll_create(1);
}

epoll_demo::~epoll_demo(){
    close(epoll_fd);
}

bool epoll_demo::add_to_epoll(int fd, epoll_event *event) const {
    return epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, event) == 0;
}

bool epoll_demo::del_from_epoll(int fd, epoll_event* event) const{
    return epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, event) == 0;
}

bool epoll_demo::mod_from_epoll(int fd, epoll_event* event) const{
    return epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, event) == 0;
}

void epoll_demo::start_run(struct my_epoll &param) const{
    param.ready_counts = epoll_wait(epoll_fd, param.ev, param.max_events, param.time_out);
}

void* func1(void*){
    auto *obj = new epoll_demo;

    epoll_event ev{};
    ev.data.fd = efd1;
    ev.events = EPOLLIN;
    obj->add_to_epoll(efd1, &ev);
    ev.data.fd = efd2;
    obj->add_to_epoll(efd2, &ev);
    ev.data.fd = efd3;
    obj->add_to_epoll(efd3, &ev);

    my_epoll myEpoll{};
    myEpoll.max_events = 3;
    myEpoll.ev = (epoll_event*)malloc(myEpoll.max_events*sizeof(epoll_event));
    myEpoll.time_out = -1;


    while(!isExit){
        obj->start_run(myEpoll);
        int ready_counts = myEpoll.ready_counts;
        cout << "ready events counts = " << ready_counts << endl;
        for(int i=0; i<ready_counts; ++i){
            auto event = myEpoll.ev+i;
            if(event->events & EPOLLIN){
                eventfd_t res=0;
                eventfd_read(event->data.fd, &res);
                cout << "res = " << res << endl;
            }
        }
    }
    free(myEpoll.ev);
    delete obj;
    return nullptr;
}



int main(){
    isExit = false;
    efd1 = eventfd(0, 0);
    efd2 = eventfd(0, 0);
    efd3 = eventfd(0, 0);
    pthread_t pthread_id;
    pthread_create(&pthread_id, nullptr, func1, nullptr);
    sleep(1);
    eventfd_write(efd1, 1);
    eventfd_write(efd2, 2);
    eventfd_write(efd3, 3);
    isExit = true;
    pthread_join(pthread_id, nullptr);
    close(efd1);
    close(efd2);
    close(efd3);
    return 0;
}