//
// Created by Xhy_m on 2022/7/6.
//

#include "update_manager.h"

enum UPDATE_TYPE{
    T1,
    T2,
    T3,
    T4,
};
void update_manager::creat_update_obj(const int type)
{
    if(p_update){
        delete p_update;
        p_update = nullptr;
    }

    switch (type){
        case T1:{
            cout << "t1" << endl;
            p_update = new manual_update;
        }break;
        case T2:{
            cout << "t2" << endl;
            p_update = new auto_update;
        }break;
        default:{
            cout << "default" << endl;
        }break;
    }
}

void update_manager::start_run()
{
    p_update->start_update();
}

update_manager::update_manager():p_update(nullptr)
{}
