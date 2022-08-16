//
// Created by Xhy_m on 2022/6/15.
//

#include "socket_client.h"

socket_client::socket_client(){
    bzero(&m_server_addr, sizeof(sockaddr_in));
    m_socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);
}

socket_client::~socket_client(){
    close(m_socket_fd);
}

void socket_client::set_addr(const char *ip, short port)
{
/*    m_server_addr.sin_family = AF_INET;
    inet_aton(ip, &m_server_addr.sin_addr);
    m_server_addr.sin_port = htons(port);*/

    m_server_addr.sun_family = AF_LOCAL;
    strcpy(m_server_addr.sun_path, "test_socket");
}

bool socket_client::connect_server()const
{
    socklen_t addr_len = sizeof(sockaddr_un);
    if(0 != connect(m_socket_fd, (sockaddr*)&m_server_addr, addr_len)){
        cout << "error msg = " << strerror(errno) << " "<< __LINE__ << endl;
        return false;
    }

    char* buf = (char*) malloc(1024);
    if(!buf){
        cout << "malloc error" << endl;
        return false;
    }
    cout << "123123" << endl;
    write(m_socket_fd, "123", 4);
    cout << "send" << endl;
    memset(buf, 0, 1024);
    ssize_t read_len = recv(m_socket_fd, buf, 1024,0);
    cout << "read buf = " << buf << endl;

    free(buf);
    return true;
}
