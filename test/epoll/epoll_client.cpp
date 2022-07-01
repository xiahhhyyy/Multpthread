//
// Created by Xhy_m on 2022/6/24.
//

#include "epoll_client.h"

epoll_client::epoll_client():
    sock_fd(-1),
    port(12345),
    server_ip(nullptr)
{
    server_ip = "192.168.175.233";
}

epoll_client::~epoll_client(){
}


bool epoll_client::start(){

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;

    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);
    socklen_t  sock_len = sizeof(server_addr);
    int connect_fd = connect(sock_fd, (sockaddr*)&server_addr, sock_len);

    //客户端先简单粗暴一点
    int buffer_len = 512;
    char* buffer = (char*) malloc(buffer_len);

    memset(buffer, 0, buffer_len);
    read(connect_fd, buffer, buffer_len);
    cout << "client buffer:" << buffer << endl;

    string replay_data = "client receive data";
    write(connect_fd, replay_data.c_str(), replay_data.size());

    cout << "client is over" << endl;
    close(sock_fd);
    free(buffer);
    sleep(3);

    return true;
}


