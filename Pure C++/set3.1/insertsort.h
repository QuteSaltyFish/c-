/*************************************************************************
	> File Name: insertsort.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 06:32:17 PM PST
 ************************************************************************/

#ifndef _INSERTSORT_H
#define _INSERTSORT_H
#include<iostream>
using namespace std;
int* insertsort(const int*data, int size)
{
    int* time = new int[2];
    int array[size]={0};
    for (int i=0; i<size; ++i)
        array[i] = data[i];
    for (int i=1; i<size; ++i)
    {
        int item=array[i];
        int j=i;
        for (j=i-1; j>=0 && array[j]>item; --j)
        {
            time[0]++;
            time[1]++;
            array[j+1] = array[j];
        } 
        array[j+1]= item;
        time[1]++;
    }
    return time;
}
#endif
