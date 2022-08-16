//
// Created by Xhy_m on 2022/7/21.
//

#ifndef XIAHHHYYY_COMMON_H
#define XIAHHHYYY_COMMON_H

#include "iostream"
#include "cstring"
#include <cerrno>
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "evhttp.h"
#include "unistd.h"
#include <sys/stat.h>
#include <fcntl.h>
#include "algorithm"
#include "vector"

using namespace std;

class aa{
public:
    aa() = default;
    ~aa() = default;
    void print();
};
void fast_sort(vector<int> &arr);

#endif //XIAHHHYYY_COMMON_H
