//
// Created by Xhy_m on 2022/7/12.
//

#include "event_handler.h"

void event_handler::process_func(client_data* data)
{
    //模拟业务处理
    //sleep(3);

    char* buffer = (char*) malloc(32);
    if(data->epoll_event & EPOLLIN){
        std::cout << "read event" << std::endl;
        memset(buffer, 0, 32);
        auto ret = read(data->fd, buffer, 32);
        if(ret == 0){
            data->io_obj->remove_event(data->fd);
            close(data->fd);
            std::cout << "close fd" << std::endl;
        } else{
            std::cout << "get data from client:" << buffer << std::endl;
            data->io_obj->modify_event(data->fd,  EPOLLOUT | EPOLLONESHOT);
        }
    }

    if(data->epoll_event & EPOLLOUT){
        std::cout << "write event" << std::endl;
        memset(buffer, 0, 32);
        memcpy(buffer, "xia", 4);
        auto ret = write(data->fd, buffer, 3);
        if(ret == 0){
            data->io_obj->remove_event(data->fd);
            close(data->fd);
        } else{
            std::cout << "send data to client:" << buffer << std::endl;
            data->io_obj->modify_event(data->fd, EPOLLIN | EPOLLONESHOT);
        }
    }
    free(buffer);

}


