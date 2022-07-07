//
// Created by Xhy_m on 2022/7/7.
//

#include "single_class.h"
//懒汉单例，第一次需要用的时候才创建对象
//饿汉单例，一开始就创建对象了


int main(int argc, char** argv){
    auto obj = single_class::get_obj();

    obj->set_str("123");
    obj->print_test();
    cout << obj << endl;
    return  0;
}

