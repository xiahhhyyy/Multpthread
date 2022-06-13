//
// Created by Xhy_m on 2022/6/13.
//

#include <pthread.h>
#include <sys/poll.h>
#include <iostream>
#include <sys/eventfd.h>
#include <unistd.h>
using namespace std;
int efd1, efd2, efd3;
bool isExit;

void* func1(void* param){
    const int num = 3;
    struct pollfd fds[num] = {0};
    fds[0].fd = efd1;
    fds[0].events= POLLIN;
    fds[1].fd = efd2;
    fds[1].events= POLLIN;
    fds[2].fd = efd3;
    fds[2].events= POLLIN;
    while(!isExit){
        poll(fds, num, -1);
        eventfd_t res;
        if(fds[0].revents & POLLIN){
            eventfd_read(fds[0].fd, &res);
            cout << "fd = " << fds[0].fd << endl;
            cout << "res = " << res << endl;
        }else if(fds[1].revents & POLLIN){
            eventfd_read(fds[1].fd, &res);
            cout << "fd = " << fds[1].fd << endl;
            cout << "res = " << res << endl;
        }else if(fds[2].revents & POLLIN){
            eventfd_read(fds[2].fd, &res);
            cout << "fd = " << fds[2].fd << endl;
            cout << "res = " << res << endl;
        }
    }
    return nullptr;
}

int main(){
    efd1 = eventfd(0, 0);
    efd2 = eventfd(0, 0);
    efd3 = eventfd(0, 0);
    isExit = false;
    pthread_t thread_id;
    pthread_create(&thread_id, nullptr, func1, nullptr);
    usleep(100);
    eventfd_write(efd1, 1);
    usleep(100);
    eventfd_write(efd2, 2);
    usleep(100);
    eventfd_write(efd3, 3);
    isExit = true;
    pthread_join(thread_id, nullptr);
    close(efd1);
    close(efd2);
    close(efd3);
    return 0;
}