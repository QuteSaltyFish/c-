#include <iostream>
#include <ctime>
#include <cstdlib>
#include "heapSort.h"
using namespace std;
int main()
{
    int a[20]={0};
    srand((unsigned int)time(NULL));
    for (int i=0; i<20; ++i)
        a[i] = rand()%20;
    heapSort(a, 20);
    for (int i=0; i<20; ++i)
        cout<<a[i]<<'\t';
    
    return 0;
}


