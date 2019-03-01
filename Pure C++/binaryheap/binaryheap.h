/*************************************************************************
        > File Name: binaryheap.h
        > Author:
        > Mail:
        > Created Time: Wed 05 Dec 2018 10:49:11 PM PST
 ************************************************************************/

#ifndef _BINARYHEAP_H
#define _BINARYHEAP_H
template <class T>
class queue {
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const T& x) = 0;
    virtual T deQueue() = 0;
    virtual T getHead() const = 0;
    virtual ~queue() {};
};

template <class T>
class priorityQueue : public queue<T> {
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const T data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const T& x);
    T deQueue();
    T getHead() const;

private:
    int currentSize;
    T* array;
    int maxSize;

    void doublespace();
    void buildHeap();
    void percolateDown(int hole);
};

template <class T>
priorityQueue<T>::priorityQueue(int capacity)
{
    array = new T[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class T>
priorityQueue<T>::~priorityQueue() { delete[] array; }

template <class T>
bool priorityQueue<T>::isEmpty() const
{
    return currentSize == 0;
}

template <class T>
T priorityQueue<T>::getHead() const { return array[1]; }

template <class T>
void priorityQueue<T>::enQueue(const T& x)
{
    if (currentSize == maxSize - 1)
        doublespace();

    // fliter upwards
    int hole = ++currentSize;
    for (; hole > 1 && x < array[hole / 2]; hole /= 2)
        array[hole] = array[hole / 2]; // find upwords until the parent node is
            // smaller than new node;
    array[hole] = x;
}

template <class T>
T priorityQueue<T>::deQueue()
{
    T minItem;
    minItem = array[1]; // store the main root node;
    array[1] = array[currentSize--]; // put the last node to main root;
    percolateDown(1); // fliter downwards;
    return minItem;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
    int child;
    T tmp = array[hole];

    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && array[child + 1] < array[child]) // if right child exist and is smaller
            child++;
        if (array[child] < tmp) // compare and exchanged parent and child;
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

template <class T>
void priorityQueue<T>::buildHeap()
{
    for (int i = currentSize / 2; i > 0; i--)
        percolateDown(i);
}

template <class T>
priorityQueue<T>::priorityQueue(const T* item, int size)
    : maxSize(size + 10)
    , currentSize(size)
{
    array = new T[maxSize];
    for (int i = 0; i < size; ++i)
        array[i + 1] = item[i];
    buildHeap();
}

template <class T>
void priorityQueue<T>::doublespace()
{
    T* tmp = array;
    maxSize *= 2;
    array = new T[maxSize];
    for (int i = 0; i < maxSize; ++i)
        array[i] = tmp[i];
    delete[] tmp;
}
#endif
