//
// Created by Xhy_m on 2022/8/23.
//

#include "CMicInteger.h"

template<typename T>
CMicInteger<T>::CMicInteger():
    m_Var(0),
    m_pLocker(NULL)
{
    m_pLocker = new mutex;
}

template<typename T>
CMicInteger<T>::CMicInteger(T arg):
    m_Var(arg),
    m_pLocker(NULL)
{
    m_pLocker = new mutex;
    m_pLocker = NULL;
}

template<typename T>
CMicInteger<T>::CMicInteger(const CMicInteger<T> &obj):
    m_Var(obj.m_Var),
    m_pLocker(NULL)
{
    m_pLocker = new mutex;
}

template<typename T>
CMicInteger<T>::~CMicInteger()
{
    delete m_pLocker;
    m_pLocker = NULL;
}

template<typename T>
CMicInteger<T> &CMicInteger<T>::operator=(const T &arg)
{
    m_pLocker->lock();
    this->m_Var = arg;
    m_pLocker->unlock();
    return *this;
}

template<typename T>
CMicInteger<T> CMicInteger<T>::operator+(const T &arg)
{
    return CMicInteger<T>(this->GetValue() + arg);
}

template<typename T>
CMicInteger<T> CMicInteger<T>::operator+(const CMicInteger<T> &obj)
{
    return CMicInteger<T>(this->GetValue() + obj.GetValue());
}

template<typename T>
CMicInteger<T> CMicInteger<T>::operator-(const T &arg)
{
    return CMicInteger<T>(this->GetValue() - arg);
}

template<typename T>
CMicInteger<T> CMicInteger<T>::operator-(const CMicInteger<T> &obj)
{
    return CMicInteger<T>(this->GetValue() - obj.GetValue());
}

template<typename T>
CMicInteger<T> &CMicInteger<T>::operator+=(const T &arg)
{
    m_pLocker->lock();
    this->m_Var += arg;
    m_pLocker->unlock();
    return *this;
}

template<typename T>
CMicInteger<T> &CMicInteger<T>::operator+=(const CMicInteger<T> &obj)
{
    m_pLocker->lock();
    this->m_Var += obj.GetValue();
    m_pLocker->unlock();
    return *this;
}

template<typename T>
CMicInteger<T> &CMicInteger<T>::operator-=(const T &arg)
{
    m_pLocker->lock();
    this->m_Var -= arg;
    m_pLocker->unlock();
    return *this;
}

template<typename T>
CMicInteger<T> &CMicInteger<T>::operator-=(const CMicInteger<T> &obj)
{
    m_pLocker->lock();
    this->m_Var -= obj.GetValue();
    m_pLocker->unlock();
    return *this;
}

template<typename T>
bool CMicInteger<T>::operator==(const T &arg)
{
    return this->GetValue() == arg;
}

template<typename T>
bool CMicInteger<T>::operator==(const CMicInteger<T> &obj)
{
    return this->GetValue() == obj.GetValue();
}

template<typename T>
bool CMicInteger<T>::operator<=(const T &arg)
{
    return this->GetValue() <= arg;
}

template<typename T>
bool CMicInteger<T>::operator<=(const CMicInteger<T> &obj)
{
    return this->GetValue() <= obj.GetValue();
}

template<typename T>
bool CMicInteger<T>::operator>=(const T &arg)
{
    return this->GetValue() >= arg;
}

template<typename T>
bool CMicInteger<T>::operator>=(const CMicInteger<T> &obj)
{
    return this->GetValue() >= obj.GetValue();
}

template<typename T>
bool CMicInteger<T>::operator<(const T &arg)
{
    return this->GetValue() < arg;
}

template<typename T>
bool CMicInteger<T>::operator<(const CMicInteger<T> &obj)
{
    return this->GetValue() < obj.GetValue();
}

template<typename T>
bool CMicInteger<T>::operator>(const T &arg)
{
    return this->GetValue() > arg;
}

template<typename T>
bool CMicInteger<T>::operator>(const CMicInteger<T> &obj)
{
    return this->GetValue() > obj.GetValue();
}

template<typename T>
T CMicInteger<T>::GetValue()const
{
    T Ret;
    m_pLocker->lock();
    Ret = m_Var;
    m_pLocker->unlock();
    return Ret;
}

template<typename T>
void CMicInteger<T>::print()
{
    cout << m_Var << endl;
}


template class CMicInteger<int>;
template class CMicInteger<short>;
template class CMicInteger<time_t>;