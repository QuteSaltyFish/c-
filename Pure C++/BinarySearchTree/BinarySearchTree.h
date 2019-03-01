/*************************************************************************
	> File Name: BinarySearchTree.h
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Dec 2018 04:39:18 PM PST
 ************************************************************************/

#ifndef _BINARYSEARCHTREE_H
#define _BINARYSEARCHTREE_H
#include<iostream>
using namespace std;
template <class T>
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        T data;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const T &theData, BinaryNode *lt, BinaryNode * rt):data(theData),left(lt), right(rt){}
    };

    BinaryNode *root;

public:
    BinarySearchTree(BinaryNode *t = NULL){root = t;}
    ~BinarySearchTree(){makeEmpty(root);}
    bool find(const T &x);
    void insert(const T &x);
    void remove(const T &x);

private:
    void insert(const T &x, BinaryNode *&t) const;
    void remove(const T &x, BinaryNode *&t) const;
    bool find(const T &x, BinaryNode *t)const;
    void makeEmpty(BinaryNode *&t);
};

//The implementation of the function makeEmpty
template <class T> 
void BinarySearchTree<T>::makeEmpty(BinaryNode *&t)
{
    if(t==NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}
//The implementation of the function FIND
template <class T>
bool BinarySearchTree<T>::find(const T &x)
{
    return find(x,root);
}

template <class T>
bool BinarySearchTree<T>::find(const T&x, BinaryNode *t) const
{
    if(t==NULL)
        return false;
    else if (x<t->data)
        return find(x, t->left);
    else if (x>t->data)
        return find(x, t->right);
    else return true;
}

//The implementation of the function insert
template <class T>
void BinarySearchTree<T>::insert(const T &x)
{
    insert(x, root);
}

template <class T>
void BinarySearchTree<T>::insert(const T&x, BinaryNode *&t)const
{
    if (t==NULL)
        t= new BinaryNode(x, NULL,NULL);//new Data can only insert as a leaf node
    //else find the last node
    else if (x<t->data)
        insert(x, t->left);
    else if(t->data<x) insert(x, t->right);
}

//The implementation of the function remove
template <class T>
void BinarySearchTree<T>::remove(const T &x)
{
    remove(x, root);
}

template <class T>
void BinarySearchTree<T>::remove(const T &x, BinaryNode *&t) const
{
    if (t==NULL)
        return;
    else if(x<t->data)//move to the operating node
        remove(x, t->left);
    else if (x>t->data)
        remove(x, t->right);
    else if (t->left!=NULL && t->right!=NULL)//delete the node with two children
    {
        BinaryNode *tmp =t->right;
        while (tmp->left != NULL)
            tmp = tmp->left;//find the smallest node in its right tree;
        t->data = tmp->data;//copy the value to the operating node;
        remove(t->data, t->right);//delete the node being moved;
    }
    else//delete the node with only one child or no child
    {
        BinaryNode *oldNode =t;
        t=(t->left!=NULL? t->left : t->right);
        delete oldNode;
    }
}

#endif
