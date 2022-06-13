//
// Created by Xhy_m on 2022/5/26.
//

#ifndef XIAHHHYYY_CTHREAD_H
#define XIAHHHYYY_CTHREAD_H
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/eventfd.h>
using namespace std;

enum PTHREAD_STATUS
{
    PTHREAD_NOT_CREATE = 0,     //未创建
    PTHREAD_RUNNING,            //正在运行
    PTHREAD_END,                //运行完成
};

class CThread
{
public:
    CThread();

    ~CThread();

    void ThreadSleep(unsigned long long iTime);

    void CreateThread(void*(*)(void*), void *param);

    bool isExit();

    bool DestroyThread();

    void SetThreadStatus(unsigned short iThreadStatus);
private:
    pthread_t pthread_id;   //线程id

    unsigned short pthread_status;  //线程状态

    pthread_cond_t pthread_cond;

    pthread_mutex_t pthread_mutex;

    bool bIsExit;

    int m_iEfd;
};


#endif //XIAHHHYYY_CTHREAD_H
