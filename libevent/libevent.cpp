//
// Created by Xhy_m on 2022/7/14.
//

#include "libevent.h"

libevent::libevent()
{
    ev_base = event_base_new();
}

libevent::~libevent()
{
    event_base_free(ev_base);
    close(m_socket_fd);
}

bool libevent::init_socket()
{
    m_socket_fd = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(12345);
    inet_pton(AF_INET, "192.168.175.233", &address.sin_addr);
    socklen_t address_len = sizeof(sockaddr_in);


    int ret = bind(m_socket_fd, (sockaddr*)&address, address_len);
    if(ret != 0){
            cout << strerror(errno) << __LINE__ <<  endl;
        return false;
    }

    ret = listen(m_socket_fd, 10);
    if(ret != 0){
        cout << strerror(errno) << __LINE__ <<  endl;
        return false;
    }
    return true;
}

bool libevent::get_src_file(){
    string filepath = "/root/src_file.tar.gz";
    int fd = open(filepath.c_str(), O_RDONLY);
    struct stat st{};
    if( 0 != fstat(fd, &st)){
        cout << "fstat is error:" << strerror(errno) << endl;
        return false;
    }

    m_file_msg.file_path = filepath;
    m_file_msg.fd = fd;
    m_file_msg.offset = 0;
    m_file_msg.file_size = st.st_size;
    return true;
}

void libevent::start()
{
    if(!init_socket()){
        return;
    }

    if(!get_src_file()){
        return;
    }


    my_argc data{};
    data.ev_base = ev_base;
    data.m_socket_fd = m_socket_fd;
    data.src_file = m_file_msg;
    struct event *ev = event_new(ev_base, m_socket_fd, EV_READ | EV_PERSIST, libevent::callback_func, &data);
    cout << "m_socket_fd = " << m_socket_fd <<endl;

    event_add(ev, nullptr);
    event_base_dispatch(ev_base);

    event_free(ev);
}

void libevent::callback_func(int fd, short event, void *arg)
{
    cout << "callback_func fd=" << fd << endl;
    cout << "eee=" << event << endl;
    auto data = (struct my_argc*) arg;
    cout << "socket_fd" << data->m_socket_fd << endl;
/*    if(fd == obj->m_socket_fd && (event & EV_READ)){
        sockaddr_in client_address{};
        socklen_t len;
        int connect_fd = accept(obj->m_socket_fd, (sockaddr*)&client_address, &len);

        struct event *ev = event_new(obj->ev_base, connect_fd, EV_WRITE, libevent::callback_func, obj);
        obj->ev = ev;
        event_add(ev, nullptr);
        return;
    }

    short type = 0;
    bool is_end = false;
    char buffer_tmp[1024] = {0};
    if(event & EV_READ){
        size_t ret = read(fd, &buffer_tmp, 1024);
        if(ret <= 0){
            close(fd);
            is_end = true;
        }else{
            cout << "get client data = " << buffer_tmp << endl;
        }
        type = EV_WRITE;
    }

    if(event & EV_WRITE){
        strcpy(buffer_tmp, "xia");
        size_t ret = write(fd, buffer_tmp, 1024);
        if(ret <= 0){
            close(fd);
            is_end = true;
        }else{
            cout << "write data" << endl;
        }
        type = EV_READ;
    }

    event_free(obj->ev);
    if(is_end) return;
    struct event *ev = event_new(obj->ev_base, fd, type, libevent::callback_func, obj);
    obj->ev = ev;
    event_add(obj->ev, nullptr);*/
    if(data->m_socket_fd == fd && (event & EV_READ)){
        cout << 111 << endl;
        sockaddr_in client_address{};
        socklen_t len = sizeof(sockaddr_in);
        int connect_fd = accept(fd, (sockaddr*)&client_address, &len);
        cout << "connect_fd = " << connect_fd << endl;
        if(connect_fd == -1){
            cout << "accept error:" << strerror(errno) << endl;
            return;
        }

        struct bufferevent *bev = bufferevent_socket_new(data->ev_base, connect_fd, BEV_OPT_CLOSE_ON_FREE);
        //bufferevent_setwatermark(bev, EV_WRITE, 1024*1024*5, 0);


        bufferevent_setcb(bev, read_cb, write_cb, event_cb, &data->src_file);
        bufferevent_enable(bev, EV_READ | EV_WRITE);
        struct timeval time_out{};
        time_out.tv_sec = 3;
        bufferevent_set_timeouts(bev, nullptr, &time_out);
    }
}

void libevent::write_cb(struct bufferevent *bev, void *arg)
{
    auto src_file = (file_msg*)arg;
    if(src_file->offset >= src_file->file_size){
        cout << "offset > filesize" << endl;
        bufferevent_free(bev);
        return;
    }
    cout << "offset = " << src_file->offset << endl;
    size_t length = 10*1024*1024;
    length = min(length, src_file->file_size - src_file->offset);

    struct evbuffer *evb = evbuffer_new();
    struct evbuffer_file_segment *evb_seg = evbuffer_file_segment_new(src_file->fd, src_file->offset, length, 0);
    evbuffer_add_file_segment(evb, evb_seg, 0, length);
    bufferevent_write_buffer(bev, evb);

    src_file->offset += length;
    evbuffer_free(evb);
    evbuffer_file_segment_free(evb_seg);
}

void libevent::read_cb(struct bufferevent *bev, void *arg)
{
    cout << "read event" << endl;
    char buffer_tmp[128] = {0};
    bufferevent_read(bev, buffer_tmp, 127);
    cout << "get client data: " << buffer_tmp << endl;
    //sleep(1);
}

void libevent::event_cb(struct bufferevent *bev, short events, void *arg)
{
    cout << 1111 << endl;
    //查错的
    if(events & BEV_EVENT_EOF)
    {
        printf("connection closed\n");
    }else if(events & BEV_EVENT_ERROR)
    {
        printf("some error\n");
    }
    //出错了就把事件给释放掉
    bufferevent_free(bev);
    printf("bufferevent 资源被释放\n");
}

