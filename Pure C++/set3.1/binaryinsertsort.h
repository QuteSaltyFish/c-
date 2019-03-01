/*************************************************************************
	> File Name: binaryinsertsort.h
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Dec 2018 03:20:37 AM PST
 ************************************************************************/

#ifndef _BINARYINSERTSORT_H
#define _BINARYINSERTSORT_H
//gist:using binary method to find the insert index quickly
#include<iostream>
using namespace std;
int* binaryinsertsort(int* data, int size)
{
    int array[size]={0};
    for (int i=0; i<size; ++i)
        array[i]=data[i];
    int *time = new int[2]{0};

    for (int i=0; i<size; ++i)
    {
        
        int low=0, high=i-1;//start to search the sorted queue;
        int m;
        while(low<high)
        {
            time[0]++;
            m = (low+high)/2;
            if (array[m]<array[i])
                low = m+1;
            else high = m-1;
        }
        cout<<"high="<<high<<" low="<<low<<endl;
        if (low!=i)
        {
            int k;
            int tmp = array[i];
            for (k=i-1; k>=low; k--)
            {
                time[1]++;
                array[k+1] = array[k];
            }
            time[1]++;
            array[k+1]=tmp;
        }  
    }
    return time;
}
#endif
