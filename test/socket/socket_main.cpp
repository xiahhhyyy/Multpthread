//
// Created by Xhy_m on 2022/6/14.
//
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "socket_client.h"
#include "socket_server.h"

using namespace std;


int main(int argc, char** argv){

    const char*ip="192.168.175.233";
    int port=12345;
    pid_t parent_pid = getpid();
    fork();

    if(getpid() != parent_pid){
        cout << "child pid = " << getpid() << endl;
        return 0;
    }else{
        cout << "ip = " << ip << endl;
        cout << "port = " << port << endl;
        socket_server xhy_server;
        xhy_server.set_listen_addr(ip, port);
        xhy_server.start_listen();
        xhy_server.handle_request();
    }

    return 0;

}
