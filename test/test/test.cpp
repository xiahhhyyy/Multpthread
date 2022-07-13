//
// Created by Xhy_m on 2022/7/12.
//

#include "pthread.h"
#include "string"
#include "iostream"
#include "unistd.h"

using namespace std;

pthread_cond_t p_cond;
pthread_mutex_t p_mutex;

void* call_func(void*){
    for(int i=0; i<10; ++i){
        cout << "bb" << endl;
        pthread_mutex_lock(&p_mutex);
        cout << "aa" << endl;
        pthread_cond_wait(&p_cond, &p_mutex);
        //p_cond = PTHREAD_COND_INITIALIZER;
        cout << 11 << endl;
        pthread_mutex_unlock(&p_mutex);
    }
    return nullptr;
}


int main(){
    pthread_t fd1, fd2;
    p_cond = PTHREAD_COND_INITIALIZER;
    p_mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_create(&fd1, nullptr, call_func, nullptr);

    sleep(1);
    pthread_cond_signal(&p_cond);
    sleep(100);
    //pthread_cond_signal(&p_cond);
    pthread_join(fd1, nullptr);
    pthread_join(fd2, nullptr);
    sleep(10);
}