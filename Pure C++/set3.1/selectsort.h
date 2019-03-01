/*************************************************************************
	> File Name: selectsort.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 08:01:51 PM PST
 ************************************************************************/

#ifndef _SELECTSORT_H
#define _SELECTSORT_H
#include<iostream>
using namespace std;
int* selectsort(int* data, int size)
{
    int *time =new int[2]{0};
    int array[size]={0};
    for (int i=0; i<size; ++i)
        array[i] = data[i];
    for (int i=0; i<size; ++i)
    {
        int minIndex=i;
        for (int j=i;j<size;++j)//find the minimun index
        {
            time[0]++;
            if (array[j]<array[minIndex])
                minIndex=j;
        }
        time[0]++;
        if (minIndex!=i)
        {
            time[1]++;
            int tmp= array[minIndex];
            array[minIndex]=array[i];
            array[i]=tmp;
        }
    }
    return time;
}
#endif
