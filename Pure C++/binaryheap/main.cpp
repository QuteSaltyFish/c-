/*************************************************************************
        > File Name: main.cpp
        > Author:
        > Mail:
        > Created Time: Wed 05 Dec 2018 11:46:49 PM PST
 ************************************************************************/

#include "binaryheap.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
    srand((unsigned int)time(NULL));
    int a[20] = { 0 };
    for (int i = 0; i < 20; ++i)
        a[i] = rand();
    priorityQueue<int> b(a, 20);
    for (int i = 0; i < 20; ++i)
        cout << b.deQueue() << endl;
}
