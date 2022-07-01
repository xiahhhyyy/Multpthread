//
// Created by Xhy_m on 2022/6/24.
//

#include "epoll_server.h"

epoll_server::epoll_server():
    socket_fd(-1),
    epoll_fd(-1),
    thread_num(5),
    isExit(false),
    thread_id(nullptr)
{
    thread_id = (pthread_t *) malloc(sizeof(pthread_t)*thread_num);
    if(!thread_id){
        cout << "malloc is error, msg:" << strerror(errno) << endl;
    }
}

epoll_server::~epoll_server()
{
    if(thread_id){
        free(thread_id);
    }
}

bool epoll_server::start()
{
    socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    int old_option = fcntl(socket_fd, F_GETFL);
    fcntl(socket_fd, old_option | O_NONBLOCK);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    const char* ip = "192.168.175.233";
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(12345);

    socklen_t address_len = sizeof(sockaddr_in);
    if(0 != bind(socket_fd, (sockaddr*)&address, address_len)){
        cout << "bind error, msg:" << strerror(errno) << endl;
        return false;
    }

    if(0 != listen(socket_fd, SOMAXCONN)){
        cout << "listen error, msg:" << strerror(errno) << endl;
        return false;
    }

    sockaddr_in client_address{};
    socklen_t client_address_len = sizeof(sockaddr_in);


    epoll_fd = epoll_create(100);
    epoll_event event{};
    event.data.fd = socket_fd;
    event.events = EPOLLIN;
    my_epoll_ctl(EPOLL_CTL_ADD, socket_fd, &event);

    //服务器退出事件

    while(!isExit){
        epoll_event events[20] = {0};
        int ret_num = epoll_wait(epoll_fd, events, 100, -1);
        if(isExit){
            break;
        }

        for(int i=0; i<ret_num; ++i)
        {
            if (events->data.fd == socket_fd && event.events&EPOLLIN)       //新建连接
            {
                //将新的连接创建一个线程，并进行处理
                int connect_fd = accept(socket_fd, (sockaddr*)&client_address, &client_address_len);
                pthread_t pthread_id;
                if (0 != pthread_create(&pthread_id, nullptr, epoll_server::work_pthread, (void *) &connect_fd))
                {
                    cout << "创建线程错误" << endl;
                    continue;
                }
                pthread_detach(pthread_id);     //暂时不做异常处理
            }else{
                cout << "unknown error" << endl;
            }
        }
    }

    close(epoll_fd);
    close(socket_fd);

    return true;
}

bool epoll_server::end()
{
    isExit = true;

    return false;
}

void *epoll_server::work_pthread(void *param)
{
    int connect_fd = *(int*)param;
    auto buffer = (char*) malloc(1024);
    while(true){
        string data = "this is server";
        write(connect_fd, data.c_str(), data.size());

        memset(buffer, 0, 1024);
        size_t ret = read(connect_fd, buffer, 1023);
        if(ret == -1){
            cout << "ret = -1" << endl;
            close(connect_fd);
            break;
        }
        if(ret == 0){
            cout << "ret = 0" << endl;
            close(connect_fd);
            break;
        }
        cout << "server receive data:" << buffer << endl;
        char* end = "end";
        if(strncmp(buffer, end, 3) == 0){
            close(connect_fd);
            break;
        }
    }
    cout << "work_pthread is end" << endl;
    return nullptr;
}

bool epoll_server::my_epoll_ctl(int option, int fd, epoll_event *event) const
{
    if(0 != epoll_ctl(epoll_fd, option, fd, event)){
        cout << "epoll_ctl error, msg:" << strerror(errno) << endl;
        return false;
    }
    return true;
}
