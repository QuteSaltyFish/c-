/*************************************************************************
	> File Name: AvlTree.h
	> Author: 
	> Mail: 
	> Created Time: Thu 06 Dec 2018 05:57:31 AM PST
 ************************************************************************/

#ifndef _AVLTREE_H
#define _AVLTREE_H
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

template<class KEY, class OTHER>
class AvlTree:public dynamicSearchTable<KEY, OTHER>
{
    struct AvlNode
    {
        SET<KEY,OTHER> data;
        AvlNode *left;
        AvlNode *right;
        int height;     //the height of the node;

        AvlNode(const SET<KEY,OTHER> & element, AvlNode *lt, AvlNode *rt, int h=1):data(element), right(rt), left(lt), height(h){}
    };

    AvlNode *root;

    public:
    AvlTree(){root = NULL;}
    ~AvlTree(){makeEmpty(root);}
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY,OTHER> &x);
    void remove(const KEY &x);

    private:
    void insert(const SET<KEY,OTHER> &x, AvlNode *&t);
    bool remove(const KEY &x, AvlNode *&t);
    void makeEmpty(AvlNode *t);
    int height(AvlNode *t)const 
    {
        return t==NULL? 0:t->height;
    }
    void LL(AvlNode *&t);
    void LR(AvlNode *&t);
    void RL(AvlNode *&t);
    void RR(AvlNode *&t);
    int max(int a, int b){ return (a>b)? a:b;}
    bool adjust(AvlNode *&t, int subTree);
};

//The implementation of function find
template <class KEY, class OTHER>
SET<KEY,OTHER>* AvlTree<KEY, OTHER>::find(const KEY &x)const
{
    AvlNode *t=NULL;

    while (t!=NULL && t->data.key!=x)
    {
        if (t->data.key>x)
            t=t->left;
        else t=t->right;
    }

    if (t==NULL)
        return NULL;
    else return (SET<KEY, OTHER>*) t;
}

template <class KEY, class OTHER>
void AvlTree<KEY,OTHER>::LL(AvlNode *&t)
{
    AvlNode *t1 = t->left;//the supposed root after rotation
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left), heigh(t->right))+1;
    t1->height = max(height(t1->left), height(t))+1;
    t = t1;
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode *&t)
{
    AvlNode *t1=t->right;
    t->right = t1->left;
    t1->left=t;
    t->height=max(height(t->left),height(t->right))+1;
    t1->height=max(height(t1->right), height(t1->left))+1;
    t = t1;
}

template <class KEY, class OTHER>
void AvlTree<KEY,OTHER>::LR(AvlNode *&t)
{
    RR(t->left);
    LL(t);
}

template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode *&t)
{
    LL(t->right);
    RR(t);
}

template <class KEY, class OTHER>
void AvlTree<KEY,OTHER>::insert(const SET<KEY,OTHER> &x)
{
    insert(x,root);
}

template <class KEY, class OTHER>
void AvlTree<KEY,OTHER>::insert(const SET<KEY,OTHER>  &x, AvlNode *&t)
{
    if (t==NULL)//empty tree
        t = new AvlNode(x, NULL, NULL);
    else if(x.key<t->data.key)
    {
        insert(x,t->left); //normal insert
        if (height(t->left)-height(t->right)==2)
        {
            if (x.key<t->left->data.key)
                LL(t);
            else LR(t);
        }   
    }   
    else if(t->data.key < x.key)
    {
        insert(x, t->right);
        if (height(t->right)-height(t->left)==2) //outof balance
        {
            if (t->right->data < x.key)
                RR(t);
            else RL(t);
        }
    }
    t->height = max ( height(t->left), height(t->right))+1; //recalculate the height of the node t;
}

template <class KEY, class OTHER>
void AvlTree<KEY,OTHER>::remove(const KEY &x)
{
    remove(x,root);
}

template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlNode *&t)
{
    if (t==NULL)    //there is no tree
        return true;
    if (x == t->data.key)   //delete the root node
    {
        if (t->left == NULL || t->right == NULL)     //the node has at most 1 child   
        {
            AvlNode* oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
            return false;
        }
        else    //the node has two children
        {
             AvlNode* tmp = t->right;
            while (tmp->left != NULL)
                tmp = tmp->left;    //find the least number in its right tree;
            t->data = tmp->data;
            if (remove(tmp->data.key, t->right))    //after delete the node, the height doesn't change
                return true;
            return adjust(t, 1);
        }
    }

    if ( x < t->data.key)   //delete it from the left tree
    {
        if (remove(x, t->left))     //after delete the node, the height of the left tree does't change
            return true;
        return adjust(t,0);
    }
    else
    {
        if (remove(x, t->right))    //ater delete the node, the height of the right tree does't change
            return true;
        return adjust(t, 1);
    }
}

template<class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode *&t, int subTree)
{
    if (subTree)
    {
        if (height(t->left)-height(t->right) == 1)
            return true;
        if (height(t->right) == height(t->left))
        {
            --t->height;
            return false;
        }
        if (height(t->left->right) > height(t->right->left))
        {
            LR(t);
            return false;
        }
        LL(t);
        if (height(t->right)==height(t->left))
            return false;
        else return true;
    }
    else
    {
        if (height(t->right)-height(t->left)==1)    //circumstance A
            return true;
        if (height(t->right)==height(t->left))      //circumstance B
        {
            --t->height;
            return false;
        }
        if (height(t->right->left)>height(t->right->right))
        {
            RL(t);
            return false;
        }
        RR(t);
        if (height(t->right)==height(t->left))
            return false;
        else return true;
    }
}
#endif
