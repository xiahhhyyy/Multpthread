//
// Created by Xhy_m on 2022/8/12.
//
//#include "util_timer.h"
//#include "libevent_timer.h"
#include "tt_timer.h"
#include "unistd.h"

void func(tt_timer*obj,  void* arg)
{
    cout << *(int*)arg <<endl;
    sleep(3);
}

void func2(tt_timer*obj, void* arg)
{
    cout << *(int*)arg << " func 2" << endl;
    //sleep(6);
    timer_data data{};
    data.cb_func = func2;
    data.trig_time = time(nullptr) + 8;
    data.arg = new int(*(int*)arg + 10);
    obj->create_timer(data);
    delete (int*)arg;
}

void* test(void* arg){
    cout << 123 << endl;
    sleep(1);
    cout << *(int*)arg << endl;
    delete (int*)arg;
    return nullptr;
}



int main(){
    tt_timer obj;
/*        auto *t = new timer_data[5];
        t->cb_func = func;
        t->trig_time = time(nullptr) + 1;
        t->arg = &obj;
        obj.create_timer(t);

        (t+1)->cb_func = func;
        (t+1)->trig_time = time(nullptr) + 1;
        (t+1)->arg = t+1;
        obj.create_timer(t+1);

        (t+2)->cb_func = func;
        (t+2)->trig_time = time(nullptr) + 1;
        (t+2)->arg = t+2;
        obj.create_timer(t+2);

        (t+3)->cb_func = func;
        (t+3)->trig_time = time(nullptr) + 1;
        (t+3)->arg = t+3;
        obj.create_timer(t+3);

        (t+4)->cb_func = func;
        (t+4)->trig_time = time(nullptr) + 1;
        (t+4)->arg = t+4;
        obj.create_timer(t+4);*/
        auto *aa = new timer_data;
        aa->cb_func = func2;
        aa->trig_time = time(nullptr) ;
        aa->arg = new int(10);
        obj.create_timer(*aa);
        delete aa;
    sleep(100);
}
