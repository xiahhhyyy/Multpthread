//
// Created by Xhy_m on 2022/6/13.
//

#include "epoll_client.h"
#include "epoll_server.h"
#include "sys/types.h"
#include "unistd.h"


int main(){

    int ret = fork();

    if (ret == -1){
        cout << "fork is error" << endl;
    }
    else if(ret == 0){   //子进程
        sleep(2);   //等待服务器初始化完成
        //epoll_client client;
        //client.start();

    }
    else{  //父进程
        epoll_server server;
        server.start();
    }

    return 0;
}