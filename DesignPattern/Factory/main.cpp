//
// Created by Xhy_m on 2022/7/6.
//

#include "update_manager.h"

int main(){
    auto* obj = new update_manager;
    obj->creat_update_obj(0);
    obj->start_run();
    obj->creat_update_obj(1);
    obj->start_run();
    return 0;
}