//
// Created by Xhy_m on 2022/8/9.
//
#include "common.h"
#include "my_shared_ptr.h"
#include "memory"

class cl2;
class cl1
{
public:
    cl1()= default;;
    ~cl1() = default;
     shared_ptr<cl2> cl2_ptr;
    string str;
};

class cl2
{
public:
    cl2() = default;
    ~cl2() = default;
    weak_ptr<cl1> cl1_ptr;
    string str;
};




int main(){

    shared_ptr<cl2> bb(new cl2);
    bb->str = "bb";
    {
        shared_ptr<cl1> aa(new cl1);
        aa->str = "bb";
        aa->cl2_ptr = bb;
        bb->cl1_ptr = aa;
        shared_ptr<cl1> cc = bb->cl1_ptr.lock();
    }

    cout << (bb->cl1_ptr)->str << endl;








    return 0;
}

