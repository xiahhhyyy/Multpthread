#include "CThread.h"

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
    std::cout << "Hello, World!" << std::endl;
    auto* pThread = new CThread();
    pThread->CreateThread(func1, pThread);
    sleep(10);
    pThread->DestroyThread();
    return 0;
}
