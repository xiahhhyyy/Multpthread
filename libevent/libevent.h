//
// Created by Xhy_m on 2022/7/14.
//

#ifndef XIAHHHYYY_LIBEVENT_H
#define XIAHHHYYY_LIBEVENT_H
#include "event2/event.h"
#include "event2/bufferevent.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "cstring"
#include "string"
#include "iostream"
#include "event2/buffer.h"
#include <algorithm>

#include <sys/stat.h>
#include <fcntl.h>
#include <event2/http.h>


using namespace std;

struct file_msg{
    int fd;
    size_t offset;
    size_t file_size;
    string file_path;
};

struct my_argc{
    int m_socket_fd{};

    event_base *ev_base{};

    struct event* ev{};

    struct file_msg src_file;
};

class libevent
{
public:
    libevent();

    ~libevent();

    void start();

private:
    bool init_socket();

    bool get_src_file();

    static void callback_func(int fd, short event, void *arg);

    static void write_cb(struct bufferevent *bev, void *arg);

    static void read_cb(struct bufferevent *bev, void *arg);

    static void event_cb(struct bufferevent *bev, short events,void *arg);


private:


    int m_socket_fd;

    event_base *ev_base;

    file_msg m_file_msg;
};


#endif //XIAHHHYYY_LIBEVENT_H
