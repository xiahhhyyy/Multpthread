//
// Created by Xhy_m on 2022/7/6.
//

#ifndef XIAHHHYYY_UPDATE_MANAGER_H
#define XIAHHHYYY_UPDATE_MANAGER_H
#include "update.h"
#include "manual_update.h"
#include "auto_update.h"

class update_manager
{
public:
    update_manager();

    ~update_manager()=default;

    void creat_update_obj(int type);

    void start_run();

private:
    update* p_update;




};


#endif //XIAHHHYYY_UPDATE_MANAGER_H
