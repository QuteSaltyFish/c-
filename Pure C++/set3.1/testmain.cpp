/*************************************************************************
	> File Name: testmain.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 06:19:08 PM PST
 ************************************************************************/

#include<iostream>
#include<ctime>
#include<cstdlib>
#include"bubblesort.h"
#include"insertsort.h"
#include"selectsort.h"
#include"quicksort.h"
#include"shellsort.h"
#include"binaryheap.h"
#include"binaryinsertsort.h"
#include"mergesort.h"
using namespace std;
int main()
{
    srand((unsigned int)time(NULL));
    cout<<"pls input the number of the node tobe sort: ";
    int n;
    cin>>n;
    cout<<"please input the loop time: ";
    int sample;
    cin>>sample;
    int* a= new int[n]{0};
    int ***sum=new int**[sample];
    for (int j=0; j<sample; ++j)
    {
        for (int i=0; i<n; ++i)
            a[i]=rand();
        priorityQueue<int> queue(a,n);
        sum[j]=new int*[7];
        sum[j][0]=bubblesort(a,n);
        sum[j][1]=insertsort(a,n);
        sum[j][2]=selectsort(a,n);
        sum[j][3]=quicksort(a,n);
        sum[j][4]=shellsort(a,n);
        int *tmp=queue.getTime();
        sum[j][5]=new int[2];
        sum[j][5][0]=tmp[0];
        sum[j][5][1]=tmp[1];
        sum[j][6]=mergesort(a,n);
        for (int i=0; i<7; ++i)
            cout<<sum[j][i][0]<<'\t'<<sum[j][i][1]<<endl;
    }
    cout<<endl<<endl;
    for (int i=0; i<sample; ++i)
    {
        cout<<"The "<<i+1<<" th result is:\n";
        for (int j=0; j<7; ++j)
            cout<<sum[i][j][0]<<'\t'<<sum[i][j][1]<<endl;
        cout<<endl;
    }
    int **average = new int*[7];
    for (int i=0; i<7; ++i)
        average[i]= new int[2];
    for(int i=0; i<7; ++i)
    {
        for (int j=0; j<sample; ++j)
        {
            average[i][0]+=sum[j][i][0];
            average[i][1]+=sum[j][i][1];
        }
        average[i][0]/=sample;
        average[i][1]/=sample;
        cout<<"The average result is: "<<endl;
        cout<<average[i][0]<<'\t'<<average[i][1]<<endl;
    }
    delete []a;
    for (int i=0; i<sample; ++i)
    {
        for (int j=0; j<7; ++j)
            delete[]  sum[i][j];
        delete[] sum[i];
    }
    delete []sum;
    delete []average;
    return 0;
}
