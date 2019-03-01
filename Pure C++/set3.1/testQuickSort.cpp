#include <iostream>
#include"quicksort.h"
using namespace std;
int main()
{
    int a[8]={7,24,1,54,7,97,52,65};
    int *time;
    time = quicksort(a, 8);
    std::cout <<time[0] <<'\t'<<time[1];
    return 0;
}

