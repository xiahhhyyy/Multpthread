//
// Created by Xhy_m on 2022/8/9.
//

#include "my_shared_ptr.h"

/*template<typename T>
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
    if(--(*mp_count)==0){
        cout << "delete" << endl;
        delete mp_count;
        delete mp_mutex;
        delete m_ptr;
    }
}

template class my_shared_ptr<tt>;*/


