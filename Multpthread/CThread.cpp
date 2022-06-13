//
// Created by Xhy_m on 2022/5/26.
//

#include "CThread.h"
#include "time.h"

CThread::CThread(){
    pthread_status = PTHREAD_NOT_CREATE;
    bIsExit = false;
    pthread_id = 0;
    pthread_mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond = PTHREAD_COND_INITIALIZER;
}

CThread::~CThread(){

}

void CThread::ThreadSleep(unsigned long long iTime){
    timespec timeWait;
    timeWait.tv_sec = time(NULL) + 3;
    timeWait.tv_nsec = 0;



    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_timedwait(&pthread_cond, &pthread_mutex, &timeWait);
    pthread_mutex_unlock(&pthread_mutex);
}

void CThread::CreateThread(void*(func)(void*) , void *param){
    if(pthread_status != PTHREAD_NOT_CREATE){
        cout << "pthread has been created" << endl;
        return;
    }

    if(pthread_create(&pthread_id, NULL, func, param)){
        cout << "pthread create is error" << endl;
    }
    pthread_status = PTHREAD_RUNNING;
}

bool CThread::isExit(){
    return bIsExit;
}

bool CThread::DestroyThread(){
    bIsExit = true;




    pthread_mutex_lock(&pthread_mutex);
    pthread_cond_signal(&pthread_cond);
    pthread_mutex_unlock(&pthread_mutex);

    cout << pthread_id << endl;
    pthread_join(pthread_id, NULL);
    pthread_status = PTHREAD_NOT_CREATE;
    return true;
}

void CThread::SetThreadStatus(unsigned short iThreadStatus){
    pthread_status = iThreadStatus;
}

