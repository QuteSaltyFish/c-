#pragma once
#include<iostream>
using namespace std;
template <class KEY, class OTHER>
struct SET
{
    KEY key;
    OTHER other;
};

template<class KEY, class OTHER>
class dynamicSearchTable
{
public:
    virtual SET<KEY,OTHER> *find(const KEY &x) const = 0;
    virtual void insert(const SET<KEY, OTHER> &x)=0;
    virtual void remove (const KEY &x)=0;
    virtual ~dynamicSearchTable(){};
};

template<class KEY, class OTHER>
class openHashTable:public dynamicSearchTable<KEY, OTHER>
{
private:
    struct node //the node struct in the openHasTable
    {
        SET<KEY, OTHER> data;
        node* next;

        node(const SET<KEY, OTHER> &d, node *n=NULL)
        {
            data = d;
            next = n;
        }
        node()
        {
            next = NULL;
        }
    };

    node **array; //the group of pointer

    int size;
    int (*key)(const int &x);
    static int defaultKey(const int &x){return x;}

public:
    openHashTable(int length=101, int(*f)(const KEY &x)=defaultKey);
    ~openHashTable();
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);
};

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int length, int (*f)(const KEY &x))
{
    size = length;
    array = new node *[size];
    key = f;
    for (int i=0; i<size; ++i)
        array[i] = NULL;
}

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable()
{
    node *p, *q;

    for (int i=0; i<size; ++i)
    {
        p = array[i];
        while(p!=NULL)
        {
            q = p->next;
            delete p;
            p = q;
        };
    }

    delete [] array;
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const SET<KEY,OTHER> &x)
{
    int pos;
    node *p;

    pos = key(x.key)%size;
    array[pos] = new node(x,array[pos]);
}


template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int pos;
    node *p, *q;

    pos = key(x)%size;
    if (array[pos]==NULL)
        return;
    p = array[pos];
    if (array[pos]->data.key == x)
    {
        array[pos] = p->next;
        delete p;
        return;
    }
    while (p!=NULL && !(p->next->data.key == x))
        p=p->next;
    if (p->next!=NULL)  //which means that the next node is the one we want
    {
        q = p->next;
        p->next = q->next;
        delete q;
    }
}

template <class KEY, class OTHER>
SET<KEY, OTHER> *openHashTable<KEY, OTHER>::find(const KEY &x) const
{
    int pos;
    node *p;

    pos = key(x)%size;
    p = array[pos];
    while (p!=NULL && !(p->data.key == x))
        p=p->next;
    if (p==NULL)
        return NULL;
    else return (SET<KEY, OTHER> *)p;
}
