/*************************************************************************
	> File Name: quicksort.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 09:00:18 PM PST
 ************************************************************************/

#ifndef _QUICKSORT_H
#define _QUICKSORT_H

//Gist: everytime, sort the array into two groups, the one smaller than the kay value and the one which don't.
#include<iostream>
#include<assert.h>
using namespace std;
int partsort(int* array, int left, int right, int* time);
void quicksort(int* array, int left, int right, int* time);
int* quicksort(const int*data, int size)
{
    int *time = new int[2]{0};
    int array[size];
    for (int i=0; i<size; ++i)
        array[i] = data[i];
    quicksort(array, 0, size-1, time); 
    for (int i=0; i<size; ++i)
        cout<<array[i]<<'\t';
    cout<<endl;
    return time;
}

void quicksort(int*array, int left, int right, int*time)
{
    assert(array);//if array is false, then end the program
    if (left>=right)
        return;
    int index= partsort(array, left, right, time);    //the middle axle;

    //after sorting, the middle axle must be place in the right place.
    quicksort(array, left, index-1, time);
    quicksort(array, index+1, right, time);
}

//the left,right array method
//find the first number from the left larger than the key and the find the first number from right smaller than the key and switch them.
int partsort(int *array, int left, int right, int *time)
{
    int& key= array[right];//let the right be the key.
    while(left < right)
    {
        while(left<right && array[left]<=key)
        {
            left++;
            time[0]++;
        }
        while(left<right && array[right]>=key)
        {
            right--;
            time[0]++;
        }
        time[1]++;
        swap(array[left], array[right]);
    }
    time[1]++;
    swap(array[right], key);
    return left;
}
#endif
