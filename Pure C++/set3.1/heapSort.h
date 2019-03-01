#pragma once
template <class T>
void percolateDown(T a[], int hole ,int size)
{
    int child;
    T tmp = a[hole];

    for (; hole*2+1<size; hole=child)
    {
        child = hole*2+1;
        if (child!=size-1 && a[child+1]>a[child])
            child++;
        if (a[child]>tmp)
            a[hole] = a[child];
        else break;
    }
    a[hole] = tmp;
}
template <class T>
void heapSort(T a[], int size)
{
    int i;
    T tmp;

    //create the initial heap
    for (i=size/2-1; i>=0; i--)
        percolateDown(a, i, size);

    //execute deQueue for n-1 times
    for (int i=size-1; i>0; --i)
    {
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        //delete a[0]
        percolateDown(a, 0, i);
    }
}


