//
// Created by Xhy_m on 2022/7/7.
//

#include "single_class.h"
single_class single_class::obj;

single_class *single_class::get_obj(){

    return &obj;
}

void single_class::print_test()
{
    cout << print_str << endl;
}

void single_class::set_str(string str)
{
    print_str = std::move(str);
}

single_class::~single_class()
{
    free_obj();     //非静态成员函数调用静态成员函数了，不是很规范
    cout << "~single_class" << endl;
}

void single_class::free_obj()
{
    obj.set_str("free_obj");
    cout << "free_obj" << endl;
}
