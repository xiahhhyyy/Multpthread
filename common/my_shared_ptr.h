//
// Created by Xhy_m on 2022/8/9.
//

#ifndef XIAHHHYYY_MY_SHARED_PTR_H
#define XIAHHHYYY_MY_SHARED_PTR_H
#include "iostream"
#include "mutex"
using namespace std;

struct tt{
    int a;
    int b;
    int c;
};

template <typename T>
class my_shared_ptr
{
public:
    explicit my_shared_ptr<T>(T *ptr = nullptr);
    ~my_shared_ptr();
    my_shared_ptr<T>& operator=(const my_shared_ptr &obj);
    T* operator->();
    T operator*();

    my_shared_ptr(const my_shared_ptr &obj);
    size_t use_count();
private:
    mutex *mp_mutex{};
    T *m_ptr;
    int *mp_count;
};





template<typename T>
my_shared_ptr<T>::my_shared_ptr(T *ptr)
{
    cout << "构造" << endl;
    m_ptr = ptr;
    if(m_ptr){
        mp_count = new int(1);
    }else{
        mp_count = new int(0);
    }
    mp_mutex = new mutex;
}

template<typename T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr<T> &obj)
{
    cout << "拷贝构造" << endl;
    m_ptr = obj.m_ptr;
    mp_count = obj.mp_count;
    mp_mutex = obj.mp_mutex;
    ++(*mp_count);
}

template<typename T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(const my_shared_ptr<T> &obj)
{
    cout << "operator = " << endl;
    if(this == &obj) return *this;
    if(m_ptr != obj.m_ptr){
        if(--(*mp_count) == 0){
            cout << "delete count=0" << endl;
            delete m_ptr;
            delete mp_count;
            delete mp_mutex;
        }
        mp_count = obj.mp_count;
        mp_mutex = obj.mp_mutex;
        m_ptr = obj.m_ptr;
        ++(*mp_count);
    }
    return *this;
}

template<typename T>
T* my_shared_ptr<T>::operator->()
{
    cout << "operator ->" << endl;
    return m_ptr;
}

template<typename T>
T my_shared_ptr<T>::operator*()
{
    cout << "operator *" << endl;
    return *m_ptr;
}

template<typename T>
size_t my_shared_ptr<T>::use_count()
{
    return *mp_count;
}

template<typename T>
my_shared_ptr<T>::~my_shared_ptr()
{
    cout << "析构函数" << endl;
    cout << m_ptr->str << endl;
    if(--(*mp_count)==0){
        cout << "delete" << endl;
        delete mp_count;
        delete mp_mutex;
        delete m_ptr;
    }
}



#endif //XIAHHHYYY_MY_SHARED_PTR_H
