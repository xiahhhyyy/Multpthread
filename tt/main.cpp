//
// Created by Xhy_m on 2022/8/9.
//
#include "common.h"
#include "my_shared_ptr.h"
#include "memory"
#include "CMicInteger.h"
#include "pthread.h"
#include "json/json.h"


int main(){

    CMicInteger<int> xhy;
    xhy = 100;

    int aa =xhy.GetValue();


    return 0;
}

