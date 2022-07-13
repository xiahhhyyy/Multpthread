//
// Created by Xhy_m on 2022/7/13.
//

#include "reactor.h"

using namespace std;

int main(){
    reactor obj;
    obj.start_server();
    sleep(10000);
    obj.stop_server();

    return 0;
}
