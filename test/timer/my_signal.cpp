//
// Created by Xhy_m on 2022/7/4.
//
#include "my_signal.h"
#include <ctime>

void handle_func(int param){
    cout << "handle_func" << endl;
    //sleep(4);
}

int main(int argc , char ** argv){
    int father_pid = getpid();
    switch (fork())
    {
        case -1:{
            cout << "fork error, errno= "<< strerror(errno) << endl;
            return -1;
        }
        case 0:{
            //子进程, 每隔1秒发一次sigalrm信号
            while(true){
                sleep(1);
                //kill(father_pid, SIGALRM);
                sleep(10);
            }
        }
        default:{
            //父进程,
            cout << "father_pid" <<  father_pid << endl;
            struct sigaction act{};
            act.sa_handler = handle_func;
            act.sa_flags = SA_RESTART;
            //sigaddset(&act.sa_mask, SIGINT);
            sigaction(SIGALRM | SIGINT, &act, nullptr);

            while(true){
                sleep(5);
            }

        }
    }
    
    return 0;
}