//
// Created by Xhy_m on 2022/7/12.
//

#include "io_multiplex.h"

io_multiplex::io_multiplex():
    epoll_fd(-1),
    max_event(1000)
{
    epoll_fd = epoll_create(max_event);
    cout << "epoll_fd = " << epoll_fd << endl;
}

io_multiplex::io_multiplex(int max_count):
    epoll_fd(-1),
    max_event(max_count)
{
    epoll_fd = epoll_create(max_event);
}

io_multiplex::~io_multiplex()
{
    close(epoll_fd);
}

void io_multiplex::register_event(int fd, int epoll_events) const
{
    epoll_event event{};
    event.events = epoll_events | EPOLLET;
    event.data.fd = fd;
    if(0 != epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event)){
        std::cout << "epoll add error msg=" << strerror(errno) << std::endl;
    }
}

void io_multiplex::modify_event(int fd, int epoll_events) const
{
    epoll_event event{};
    event.events = epoll_events | EPOLLET;
    event.data.fd = fd;
    if(0 != epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event)){
        std::cout << "epoll mod error msg=" << strerror(errno) << std::endl;
    }
}

void io_multiplex::remove_event(int fd) const
{
    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr);
}

int io_multiplex::my_epoll(epoll_event event[]) const
{
    int ret = epoll_wait(epoll_fd, event, max_event,-1);
    cout << "ret = " << ret << endl;
    if(ret == -1){
        if(errno != EINTR){
            cout << "epoll wait error msg:" << strerror(errno) << endl;
            sleep(1);
            return -1;
        }
        return 0;
    }
    return ret;
}




