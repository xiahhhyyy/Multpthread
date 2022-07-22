//
// Created by Xhy_m on 2022/7/20.
//

#include "event2/event.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "sys/socket.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;
int fd;

void read_cb(bufferevent *bev, void* arg){
    //cout << "read_cb" << endl;
    char buf[1024] = {0};
    size_t bev_ret = bufferevent_read(bev, buf, sizeof(buf)-1);
    size_t ret = 0;
    while(ret < bev_ret){
        auto tmp = write(fd, buf+ret, sizeof(buf)-1);
        if(tmp == -1){
            cout << "write error:" << strerror(errno) << endl;
            break;
        }
        ret += tmp;
    }
    sleep(1000000);
}

void write_cb(bufferevent *bev, void* arg){
    cout << "write_cb" << endl;
    sleep(1);
}

void event_cb(bufferevent *bev, short event, void *arg){
    cout << "event_cb" << endl;

    if(event & BEV_EVENT_ERROR){
        cout << "some error" << endl;
    }

    if(event & BEV_EVENT_EOF){
        cout << "connect closed" << endl;
    }

    if(event & BEV_EVENT_CONNECTED){
        cout << "connect finish" << endl;
        return;
    }

    bufferevent_free(bev);
    close(fd);
}

int main(){

    fd = open("/root/res.tar.gz", O_WRONLY | O_APPEND | O_CREAT);
    if(fd == -1){
        cout << "error msg:" << strerror(errno) << endl;
        return -1;
    }
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    event_base *ev_base = event_base_new();
    bufferevent *bev = bufferevent_socket_new(ev_base, -1, BEV_OPT_CLOSE_ON_FREE);

    struct sockaddr_in serv_address{};
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(12345);
    inet_aton("192.168.175.233", &serv_address.sin_addr);
    bufferevent_setcb(bev, read_cb, write_cb, event_cb, NULL);
    bufferevent_socket_connect(bev, (sockaddr*)&serv_address, sizeof(sockaddr_in));
    bufferevent_enable(bev, EV_READ | EV_WRITE);
    bufferevent_setwatermark(bev, EV_READ, 0, 1024);

    event_base_dispatch(ev_base);
    event_base_free(ev_base);

    return 0;
}

