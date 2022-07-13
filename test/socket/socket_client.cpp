//
// Created by Xhy_m on 2022/6/15.
//

#include "socket_client.h"

socket_client::socket_client(){
    bzero(&m_server_addr, sizeof(sockaddr_in));
    m_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
}

socket_client::~socket_client(){
    close(m_socket_fd);
}

void socket_client::set_addr(const char *ip, short port)
{
    m_server_addr.sin_family = AF_INET;
    inet_aton(ip, &m_server_addr.sin_addr);
    m_server_addr.sin_port = htons(port);


}

bool socket_client::connect_server()const
{
    socklen_t addr_len = sizeof(sockaddr_in);
    if(0 != connect(m_socket_fd, (sockaddr*)&m_server_addr, addr_len)){
        cout << "error msg = " << strerror(errno) << endl;
        return false;
    }

    char* buf = (char*) malloc(1024);
    if(!buf){
        cout << "malloc error" << endl;
        return false;
    }
    memset(buf, 0, 1024);
    ssize_t read_len = read(m_socket_fd, buf, 1024);
    cout << "read buf = " << buf << endl;
    free(buf);
    return true;
}
