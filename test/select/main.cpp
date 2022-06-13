#include <pthread.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#include <sys/select.h>
#include <sys/stat.h>

using namespace std;

int efd;
int efd2;
int efd3;
bool isExit;
void* func1 (void* param){
    fd_set reads, writes, tmp1, tmp2;
    FD_ZERO(&reads);
    FD_ZERO(&writes);

    FD_SET(efd, &reads);
    FD_SET(efd2, &reads);
    FD_SET(efd3, &reads);

    timeval ttime;

    while(!isExit){
        static long long i=0;
        tmp1 = reads;
        tmp2 = writes;
        ttime.tv_usec = 0;
        ttime.tv_sec = 10;
        int a = efd>efd2?efd:efd2;a = a>efd3?a:efd3;
        select(a+1, &tmp1, NULL, NULL, &ttime);
        int res = 0;
        if(FD_ISSET(efd, &tmp1)){
            cout << read(efd, &res, sizeof(eventfd_t)) << endl;
            cout << "efd = " << res << endl;
        }else if(FD_ISSET(efd2, &tmp1)){
            read(efd2, &res, sizeof(eventfd_t));
            cout << "efd2 = " << res << endl;
        }else if(FD_ISSET(efd3, &tmp1)){
            read(efd3, &res, sizeof(eventfd_t));
            cout << "efd3 = " << res << endl;
        }
        sleep(1);
    }

    return nullptr;
}
int main(){
    isExit = false;
    efd = eventfd(0, 0);
    efd2 = eventfd(0, 0);
    efd3 = eventfd(0, 0);
    pthread_t thread_id;
    int ret =  pthread_create(&thread_id, nullptr, func1, nullptr);
    if(ret != 0){
        cout << "thread create is error" << endl;
        return 0;
    }

    cout << "start pthread_join" << endl;
    sleep(1);
    cout << "efd" << endl;
    eventfd_write(efd,10);
    sleep(1);
    cout << "efd2" << endl;
    eventfd_write(efd2, 2);
    sleep(1);
    cout << "efd3" << endl;
    eventfd_write(efd2, 3);
    isExit = true;
    pthread_join(thread_id, nullptr);
    close(efd);
    close(efd2);
    close(efd3);
    return 0;


}

