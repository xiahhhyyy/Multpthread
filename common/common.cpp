//
// Created by Xhy_m on 2022/8/9.
//
#include "common.h"

void helper(vector<int> &arr, int left, int right){
    if(left>= right) return;
    int i=left;
    {
        int j = right;
        int base = arr[i];
        while (i < j)
        {
            while (i < j && arr[j] >= base) --j;     //arr[i]的位置是多余的，在右边找到小于base的值，直接放到arr[i]位置
            arr[i] = arr[j];                        //将arr[j]的值放到arr[i]的位置，此时arr[j]的位置是多余的
            while (i < j && arr[i] < base) ++i;
            arr[j] = arr[i];
        }
        arr[i] = base;
    }
    helper(arr, left, i-1);
    helper(arr, i+1, right);
}

void fast_sort(vector<int> &arr){
    helper(arr, 0, arr.size()-1);
}

void aa::print()
{
    cout << "print " << endl;
}
