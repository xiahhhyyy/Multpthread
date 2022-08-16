//
// Created by Xhy_m on 2022/7/12.
//

#include "reactor.h"

void reactor::work_thread()
{
    while(!exit){
        pthread_mutex_lock(&m_thread_mutex);
        if(list_fd.empty()){
            pthread_cond_wait(&m_thread_cond, &m_thread_mutex);
        }
        client_data data = list_fd.front();
        list_fd.pop_front();
        pthread_mutex_unlock(&m_thread_mutex);

        m_event_handler->process_func(&data);
    }
}

reactor::reactor():
    sock_fd(-1),
    m_event_handler(nullptr),
    m_io_multiplex(nullptr),
    exit(false)
{
    m_event_handler = new event_handler;
    m_io_multiplex = new io_multiplex;
    list_fd.clear();
}

reactor::~reactor()
{
    delete m_io_multiplex;
    delete m_event_handler;
}

void reactor::start_server()
{
    //创建线程池
    start_thread_pool();

    sock_server();
    m_io_multiplex->register_event(sock_fd, EPOLLIN);
    epoll_event events[1000];
    while(!exit){
        int ret = m_io_multiplex->my_epoll(events);
        for(int i=0; i<ret; ++i){
            auto tmp_event = events + i;
            if( (tmp_event->data.fd == sock_fd) && (tmp_event->events & EPOLLIN) ){
                sockaddr_in client_address{};
                socklen_t socklen = sizeof(sockaddr_in);
                int connect_fd = accept(sock_fd, (sockaddr*)&client_address, &socklen);
                m_io_multiplex->register_event(connect_fd, EPOLLIN|EPOLLET);
                std::cout << "new connect" << std::endl;
            } else if(tmp_event->data.fd != sock_fd){
                client_data data{};
                data.fd = tmp_event->data.fd;
                data.epoll_event = tmp_event->events;
                data.io_obj = m_io_multiplex;

                pthread_mutex_lock(&m_thread_mutex);
                list_fd.push_back(data);
                if(list_fd.size() == 1){
                    pthread_cond_signal(&m_thread_cond);
                }
                pthread_mutex_unlock(&m_thread_mutex);

            }
        }
    }
    close(sock_fd);
}

void reactor::sock_server()
{
    sock_fd = socket(PF_INET, SOCK_STREAM, 0);   //创建socket
    std::cout << "server socket = " << sock_fd << std::endl;

    sockaddr_in address{};
    address.sin_family = AF_INET;
    inet_aton("192.168.175.233", &address.sin_addr);
    address.sin_port = htons(12345);
    socklen_t socklen = sizeof(sockaddr_in);

    int ret = bind(sock_fd, (sockaddr*) &address, socklen);
    if(ret != 0){
        std::cout << "bind error" << std::endl;
    }

    ret = listen(sock_fd, SOMAXCONN);
    if(ret != 0){
        std::cout << "listen error" << std::endl;
    }
}

void reactor::stop_server()
{
    exit = true;
}
