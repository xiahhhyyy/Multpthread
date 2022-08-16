//
// Created by Xhy_m on 2022/6/15.
//

#include "socket_server.h"
socket_server::socket_server():
    m_accept_id(0),
    m_server_sockaddr{}
{
    m_sock_id = socket(PF_LOCAL, SOCK_STREAM, 0);
}

socket_server::~socket_server()
{
    close(m_sock_id);
}

void socket_server::set_listen_addr(const char *addr, uint16_t port)
{

    m_server_sockaddr.sun_family = AF_LOCAL;
    strcpy(m_server_sockaddr.sun_path, "test_socket");
    //m_server_sockaddr.sin_port = htons(port);
    //inet_pton(AF_INET,addr,&m_server_sockaddr.sin_addr);

    //inet_aton(addr, &m_server_sockaddr.sin_addr);
}

bool socket_server::start_listen()
{
    if(0 != bind(m_sock_id, (struct sockaddr*)&m_server_sockaddr, sizeof(m_server_sockaddr))){
        cout << "bind error, error msg = "<< strerror(errno) << endl;
        return false;
    }
    if(0 != listen(m_sock_id, SOMAXCONN)){
        cout << "listen error, error msg = "<< strerror(errno) << endl;
        return false;
    }
    return true;
}

void socket_server::handle_request() const
{
    char*buf = (char*) malloc(1024);
    int i = 0;
    while(++i<100){

        struct sockaddr_un client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        cout << "connect_fd = 1231231"<< endl;
        int connect_fd = accept(m_sock_id, (sockaddr*)&client_addr, &client_addr_len);
        cout << "connect_fd = " << connect_fd << endl;
        memset(buf, 0, 1024);
        read(connect_fd, buf, 1023);
        //char* client_ip =  inet_ntoa(client_addr.sin_addr);
        //cout << "client_ip = " << client_ip << endl;
        cout << "server buf = " << buf << endl;

        write(connect_fd, "xhy", 4);
        close(connect_fd);
    }
}


