//
// Created by Xhy_m on 2022/7/14.
//

#include "libevent.h"

libevent::libevent()
{
    ev_base = event_base_new();
}

libevent::~libevent()
{
    event_base_free(ev_base);
    close(m_socket_fd);
}

bool libevent::init_socket()
{
    m_socket_fd = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(12345);
    inet_pton(AF_INET, "192.168.175.233", &address.sin_addr);
    socklen_t address_len = sizeof(sockaddr_in);


    int ret = bind(m_socket_fd, (sockaddr*)&address, address_len);
    if(ret != 0){
            cout << strerror(errno) << __LINE__ <<  endl;
        return false;
    }

    ret = listen(m_socket_fd, SOMAXCONN);
    if(ret != 0){
        cout << strerror(errno) << __LINE__ <<  endl;
        return false;
    }
    return true;
}

void libevent::start()
{
    if(!init_socket()){
        return;
    }

    struct event *ev = event_new(ev_base, m_socket_fd, EV_READ | EV_PERSIST, libevent::callback_func, this);
    event_add(ev, nullptr);
    event_base_dispatch(ev_base);

    event_free(ev);
}

void libevent::callback_func(int fd, short event, void *arg)
{
    auto obj = (my_argc*) arg;
    if(fd == obj->m_socket_fd && (event & EV_READ)){
        sockaddr_in client_address{};
        socklen_t len;
        int connect_fd = accept(obj->m_socket_fd, (sockaddr*)&client_address, &len);

        struct event *ev = event_new(obj->ev_base, connect_fd, EV_WRITE, libevent::callback_func, obj);
        obj->ev = ev;
        event_add(ev, nullptr);
        return;
    }

    short type = 0;
    bool is_end = false;
    char buffer_tmp[1024] = {0};
    if(event & EV_READ){
        size_t ret = read(fd, &buffer_tmp, 1024);
        if(ret <= 0){
            close(fd);
            is_end = true;
        }else{
            cout << "get client data = " << buffer_tmp << endl;
        }
        type = EV_WRITE;
    }

    if(event & EV_WRITE){
        strcpy(buffer_tmp, "xia");
        size_t ret = write(fd, buffer_tmp, 1024);
        if(ret <= 0){
            close(fd);
            is_end = true;
        }else{
            cout << "write data" << endl;
        }
        type = EV_READ;
    }

    event_free(obj->ev);
    if(is_end) return;
    struct event *ev = event_new(obj->ev_base, fd, type, libevent::callback_func, obj);
    obj->ev = ev;
    event_add(obj->ev, nullptr);
}

