/*************************************************************************
	> File Name: shellsort.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 09:37:43 PM PST
 ************************************************************************/

#ifndef _SHELLSORT_H
#define _SHELLSORT_H

//Gist: imagine the array was put in to a matrix which has the row of x, and them sory the element on each column with insert sort;
#include<iostream>
using namespace std;
int* shellsort(const int* data, int size)
{
    int* time = new int[size]{0};
    int array[size];
    for (int i=0; i<size; ++i)
        array[i] = data[i];
    for (int k=size/2; k>=1; k=k/2)
    {
        for (int i=k; i<size; ++i)
        {
            int tmp=array[i];
            int j=i;
            while(j>=k && array[j-k]>tmp)
            {
                time[0]++;
                time[1]++;
                array[j]=array[j-k];
                j=j-k;
            }
            time[1]++;
            array[j]=tmp;
        }
    }
    return time;
}
#endif
