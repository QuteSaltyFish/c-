/*************************************************************************
	> File Name: mergesort.h
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Dec 2018 04:15:50 AM PST
 ************************************************************************/

#ifndef _MERGESORT_H
#define _MERGESORT_H
#include<iostream>
using namespace std;
void mergearray(int a[], int first, int mid, int last, int *time);
void mergesort(int a[], int first, int last, int *time);
int* mergesort(int *data, int size)
{
    int array[size]={0};
    int *time= new int[2]{0};

    for (int i=0; i<size; ++i)
        array[i]=data[i];
    mergesort(array, 0, size-1,time);
    return time;
}

void mergesort(int a[], int first, int last, int *time)
{
    if (first < last)
    {
        int mid= (first + last)/2;
        mergesort(a, first, mid, time);
        mergesort(a, mid+1, last, time);
        mergearray(a, first, mid, last, time);
    }
}
void mergearray(int a[], int first, int mid, int last, int *time)
{
    int i=first, j=mid+1;
    int m=mid, n=last;
    int k=0;
    int temp[last-first+1]={0};
    while(i<=m && j<=n)
    {
        time[0]++;
        time[1]++;
        if (a[i]<=a[j])
            temp[k++]=a[i++];
        else 
            temp[k++]=a[j++];
    }
    while(i<=m)
    {
        temp[k++] = a[i++];
        time[1]++;
    }
    while(j<n)
    {
        time[1]++;
        temp[k++] = a[j++];
    }

    for (int i=0; i<k; ++i)
        a[first+i]=temp[i];
}
#endif
