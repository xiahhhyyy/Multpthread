//
// Created by Xhy_m on 2022/7/6.
//

#ifndef XIAHHHYYY_AUTO_UPDATE_H
#define XIAHHHYYY_AUTO_UPDATE_H
#include "update.h"


class auto_update:public update
{
public:
    ~auto_update() override =default;

    auto_update()=default;

private:
    void get_update_url() override;
};


#endif //XIAHHHYYY_AUTO_UPDATE_H
