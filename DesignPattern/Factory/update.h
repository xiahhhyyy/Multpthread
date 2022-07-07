//
// Created by Xhy_m on 2022/7/6.
//

#ifndef XIAHHHYYY_UPDATE_H
#define XIAHHHYYY_UPDATE_H
#include "string"
#include "iostream"
using namespace std;

class update
{
public:
    update() = default;

    virtual ~update() = default;

    bool start_update();

protected:
    virtual void get_update_url()=0;

    string update_url;
private:

};


#endif //XIAHHHYYY_UPDATE_H
