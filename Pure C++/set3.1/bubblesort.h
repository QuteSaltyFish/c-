/*************************************************************************
	> File Name: bubblesort.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 06:05:25 PM PST
 ************************************************************************/

#ifndef _BUBBLESORT_H
#define _BUBBLESORT_H
#include <iostream>
using namespace std;
int* bubblesort(const int* data, int size)
{
    int* time=new int[2]{0,0};
    int *array = new int[size];
    for (int i=0; i<size; ++i)
    {
        array[i] = data[i];
    }
    for (int i=0; i< size-1; ++i)
    {
        bool flag = false;
        for (int j=0; j< size-1-i; ++j)
        {
            time[0]++;
            if (array[j]>array[j+1])
            {
                int tmp = array[j+1];
                array[j+1] = array[j];
                array[j] = tmp;
                flag =true;
                time[1]++;
            }
        }
        if (!flag)
            break;
    }
    delete array;
    return time;
}
#endif
