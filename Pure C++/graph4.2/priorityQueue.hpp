//
//  priorityQueue.hpp
//  priorityQueue
//
//  Created by Mingke Wang on 2018/11/9.
//  Copyright © 2018 Mingke Wang. All rights reserved.
//

#ifndef priorityQueue_hpp
#define priorityQueue_hpp

#include <iostream>
using namespace std;
template <class T>
class myQueue {
public:
    virtual bool isEmpty() const = 0;
    virtual void enQueue(const T &x) = 0;
    virtual T deQueue() = 0;
    virtual T getHead() const = 0;
    virtual ~myQueue(){}
};

template <class T>
class priorityQueue: public myQueue<T> {
public:
    priorityQueue(int capacity = 100);
    priorityQueue(const T data[], int size);
    ~priorityQueue();
    bool isEmpty() const;
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;
private:
    int currentSize;    //队列长度
    T *array;
    int maxSize;    //容量
    
    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

//构造函数，析构函数， isEmpty，gethead函数的实现：
template <class T>
priorityQueue<T>::priorityQueue(int capacity)
{
    array = new T[capacity];
    maxSize = capacity;
    currentSize = 0;
}

template <class T>
priorityQueue<T>::~priorityQueue<T>()
{
    delete [] array;
}

template <class T>
bool priorityQueue<T>::isEmpty() const
{
    return currentSize == 0;
}

template <class T>
T priorityQueue<T>::getHead() const
{
    return array[1];    //array[0]不存放数据，仅作为根节点的标志
}


//enQueue函数的实现
template <class T>
void priorityQueue<T>::enQueue(const T &x)
{
    if (currentSize == maxSize-1)
        doubleSpace();
    
    //向上过滤
    int hole = ++currentSize;
    for (; hole>1 && x<array[hole/2]; hole/=2)  //存在父节点且b小于父节点
        array[hole] = array[hole/2];
    array[hole] = x;
}

//deQueue和percolateDown函数的实现
template <class T>
T priorityQueue<T>::deQueue()
{
    T minItem;
    minItem = array[1];
    array[1] = array[currentSize--];    //假设把最后一位数据点放在根节点，然后开始重新排列
    percolateDown(1);   //对于根节点的元素开始重新排列
    return minItem;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
    int child;  //正在比较的子节点的下标
    T tmp = array[hole];
    
    for (; hole * 2 <= currentSize; hole = child)   //判断条件：存在子节点
    {
        child = hole *2;
        if (child != currentSize && array[child+1] < array[child])
            child++;    //若存在右孩子，且右孩子大于左孩子
        if (array[child]<tmp)
            array[hole] = array[child]; //较大的节点往上走
        else
            break;
    }
    array[hole] = tmp;
}

template <class T>
void priorityQueue<T>::buildHeap()
{
    for (int i = currentSize/2; i>0; i--)   //从第一个非叶节点开始往前一次次判断是否满足堆的有效性
        percolateDown(i);
}

template <class T>
priorityQueue<T>::priorityQueue(const T *items, int size):maxSize(size+10), currentSize(size)
{
    array = new T [maxSize];
    for (int i=0; i<size; i++)
        array[i+1] = items[i];
    buildHeap();
}

template <class T>
void priorityQueue<T>::doubleSpace()
{
    T *tmp = array;
    maxSize *= 2;
    array = new T[maxSize];
    for (int i=0; i<currentSize; ++i)
        array[i] = tmp[i];
    delete [] tmp;
}
#endif /* priorityQueue_hpp */
