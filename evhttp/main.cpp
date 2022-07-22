//
// Created by Xhy_m on 2022/7/21.
//
#include "common.h"

//#include <event2/http-internal.h>
//#include <event2/http_struct.h>

unsigned long long i = 0;

struct args
{
    struct event* ev;
    struct evhttp_request* req;
    struct bufferevent* bev;
    int file_fd;
    size_t offset;
    size_t file_size;

    size_t last_bev_size;
};

void cb_func(int fd, short event, void* arg)
{

    //cout << "cb_func" << endl;
    auto param = (args*)arg;
    if(param->req->response_code != 200 || param->offset >= param->file_size){
        event_del(param->ev);
        event_free(param->ev);
        evhttp_send_reply_end(param->req);
        close(param->file_fd);
        free(param);
        param = nullptr;
        cout << "****i = " << i << endl;
        return;
    }

    size_t len = 1024*512;
    size_t buffer_size = evbuffer_get_length(bufferevent_get_output(param->bev));
    if(param->last_bev_size > buffer_size){
        len = 2*(param->last_bev_size - buffer_size);
    }
    param->last_bev_size = buffer_size;


    if(buffer_size > 5*len){
        return;
    }

    if(i%100){
        cout << "len" << len << endl;
    }
    i++;

    len = min(param->file_size - param->offset, len);
    auto file_segment = evbuffer_file_segment_new(param->file_fd, (int64_t)param->offset, len, 0);
    auto tmp = evbuffer_new();
    evbuffer_add_file_segment(tmp, file_segment, 0, len);
    evhttp_send_reply_chunk(param->req, tmp);
    param->last_bev_size += len;
    param->offset += len;
    evbuffer_free(tmp);
    evbuffer_file_segment_free(file_segment);
}

void http_request_done(evhttp_request* req, void *arg)
{

    int fd = open("/root/src_file.tar.gz", O_RDONLY);
    struct stat st{};
    fstat(fd, &st);


    auto base = (event_base*)arg;
    cout << "req done" << endl;
    evbuffer *evb = evbuffer_new();
    evbuffer_add(evb, "xiaxia", 7);
    evhttp_send_reply_start(req, 200, "ok");
    evbuffer_free(evb);
    struct evhttp_connection *connection = evhttp_request_get_connection(req);
    auto bev = evhttp_connection_get_bufferevent(connection);
    int bev_fd =  bufferevent_getfd(bev);

    auto cb_arg = (args*) malloc(sizeof (args));
    auto  ev = event_new(base, bev_fd, EV_WRITE | EV_PERSIST, cb_func, cb_arg);
    cb_arg->req = req;
    cb_arg->offset = 0;
    cb_arg->bev = bev;
    cb_arg->file_fd = fd;
    cb_arg->file_size = st.st_size;
    cb_arg->ev = ev;
    event_add(ev, nullptr);
}

int main()
{
    event_base *base = event_base_new();
    evhttp *http = evhttp_new(base);
    evhttp_set_cb(http,"/test", http_request_done, base);
    evhttp_bind_socket(http, "0.0.0.0", 8080);
    event_base_dispatch(base);
    evhttp_free(http);
    event_base_free(base);
    return 0;
}