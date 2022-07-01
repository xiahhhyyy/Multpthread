#include "CThread.h"
#include <cerrno>
#include <cstdio>
#include <cstring>

void* func1(void* param){
    auto* pThread = (CThread*) param;
    while(!pThread->isExit()){
        static int i = 0;
        pThread->ThreadSleep(3000);
        cout << "func1" << ++i << endl;
    }
    cout << "thread is end" << endl;
    return nullptr;
}

int main()
{
    FILE *fd = fopen("/root/file_test.txt", "rb");
    if(nullptr == fd){
        cout << "错误号 = " << errno << endl;
        cout << "错误信息 = " << strerror(errno) << endl;
    }
    std::cout << "Hello, World!" << std::endl;
    auto* pThread = new CThread();
    pThread->CreateThread(func1, pThread);
    sleep(10);
    pThread->DestroyThread();
    return 0;
}
