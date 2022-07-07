//
// Created by Xhy_m on 2022/7/6.
//

#ifndef XIAHHHYYY_MANUAL_UPDATE_H
#define XIAHHHYYY_MANUAL_UPDATE_H
#include "update.h"


class manual_update: public update
{
public:
    manual_update()=default;

    ~manual_update() override =default;

    void get_update_url() override;
};


#endif //XIAHHHYYY_MANUAL_UPDATE_H
