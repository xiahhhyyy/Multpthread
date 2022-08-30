//
// Created by xia.hy on 2022/8/23.
//

#ifndef CMICINTEGER_H
#define CMICINTEGER_H
#include "mutex"
#include "iostream"
using namespace std;
template <typename T>
class CMicInteger
{
public:
    CMicInteger();
    explicit CMicInteger(T arg);
    CMicInteger(const CMicInteger<T> &obj);
    ~CMicInteger();

    CMicInteger<T> &operator=(const T &arg);

    CMicInteger<T> operator+(const T &arg);
    CMicInteger<T> operator+(const CMicInteger<T> &obj);

    CMicInteger<T> operator-(const T &arg);
    CMicInteger<T> operator-(const CMicInteger<T> &obj);

    CMicInteger<T>& operator+=(const T &arg);
    CMicInteger<T>& operator+=(const CMicInteger<T> &obj);

    CMicInteger<T>& operator-=(const T &arg);
    CMicInteger<T>& operator-=(const CMicInteger<T> &obj);

    bool operator==(const T &arg);
    bool operator==(const CMicInteger<T> &obj);

    bool operator<=(const T &arg);
    bool operator<=(const CMicInteger<T> &obj);

    bool operator>=(const T &arg);
    bool operator>=(const CMicInteger<T> &obj);

    bool operator<(const T &arg);
    bool operator<(const CMicInteger<T> &obj);

    bool operator>(const T &arg);
    bool operator>(const CMicInteger<T> &obj);

    void print();

    T GetValue()const;
private:
    T m_Var;

    mutex *m_pLocker;
};




#endif //CMICINTEGER_H
