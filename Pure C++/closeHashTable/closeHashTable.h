#pragma once
#include<iostream>
using namespace std;
template<class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class dynamicSearchTable
{
    public:
    virtual SET<KEY,OTHER> *find(const KEY &x) const =0;
    virtual void insert(const SET<KEY, OTHER> &x)=0;
    virtual void remove(const KEY &x)=0;
    virtual ~dynamicSearchTable(){};
};

template <class KEY, class OTHER>
class closeHashTable:public dynamicSearchTable<KEY, OTHER>
{
public:
    closeHashTable(int length=101, int(*f)(const KEY &x)=defaultKey);
    ~closeHashTable(){delete []array;}
    SET<KEY, OTHER> * find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
private:
    struct node
    {
        SET<KEY,OTHER> data;
        int state;  //0-empty, 1-active, 2-deleted
        node(){state=0;};
    };

    node *array;
    int size;
    int(*key)(const KEY & x);   //the pointer of the coordinate function
    static int defaultKey(const int &x){return x;}
};

template <class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length, int (*f)(const KEY &x))
{
    size = length;
    array = new node[size];
    key = f;
}

template <class KEY, class OTHER>
void closeHashTable<KEY,OTHER>::insert(const SET<KEY, OTHER> &x)
{
    int initPos, pos;

    initPos = pos = key(x.key)%size;
    do
    {
        if (array[pos].state!=1)
        {
            array[pos].data = x;
            array[pos].state = 1;
            return;
        }

        pos=(pos+1)%size;
    }while(pos != initPos);
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int initPos, pos;

    initPos = pos =key(x)%size;
    do
    {
        if (array[pos].state == 0)
            return;
        if (array[pos].state == 1 && array[pos].data.key==x)    //node found and delete it
        {
            array[pos].state = 2;
            return;
        }
        pos = (pos+1)%size;
    }while(pos!=initPos);
}

template <class KEY, class OTHER>
SET<KEY, OTHER>* closeHashTable<KEY, OTHER>::find(const KEY &x)const
{
    int initPos, pos;

    initPos = pos = key(x)%size;
    do
    {
        if (array[pos].state == 0)
            return NULL;    //do not found
        if (array[pos].state == 1 && array[pos].data.key == x)  //foung
            return (SET<KEY, OTHER> *)&array[pos];
        pos = (pos+1)%size;
    }while(pos != initPos);
}
