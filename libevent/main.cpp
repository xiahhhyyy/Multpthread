//
// Created by Xhy_m on 2022/7/14.
//

#include "libevent.h"
#include "signal.h"

using namespace std;


int main()
{
    signal(SIGPIPE, SIG_IGN);
    libevent obj;
    obj.start();

    return 0;
}