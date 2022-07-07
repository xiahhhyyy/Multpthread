//
// Created by Xhy_m on 2022/7/7.
//

#ifndef XIAHHHYYY_SINGLE_CLASS_H
#define XIAHHHYYY_SINGLE_CLASS_H

#include "iostream"
#include "string"
using namespace std;

class single_class
{
public:
    static single_class* get_obj();

    void print_test();

    void set_str(string str);

private:
    single_class& operator=(const single_class& _obj);

    single_class(const single_class &obj);

    single_class() = default;

    ~single_class();

    string print_str;

    static single_class obj;

    static void free_obj();
};


#endif //XIAHHHYYY_SINGLE_CLASS_H
