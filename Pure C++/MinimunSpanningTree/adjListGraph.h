#pragma once
#include <iostream>
#include <queue>
#include "DisjointSet.h"
using namespace std;
template <class TypeOfVer, class TypeOfEdge>
class Graph
{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)=0;
    virtual void remove(TypeOfVer x, TypeOfVer y)=0;
    virtual bool exist(TypeOfVer x, TypeOfVer y)const=0;
    int numOfVer()const{return Vers;}
    int numOfEdge()const{return Edges;}
protected:
    int Vers,Edges;
};

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph:public Graph<TypeOfVer, TypeOfEdge>
{
public:
    adjListGraph(int vSize, const TypeOfVer d[], const int weight[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y)const;
    ~adjListGraph();
    void dfs()const;
    void bfs()const;
    void showEdge();
    void topsort();
    void way1sort();
    void way2sort();
    void kruskal()const;
    void prim(TypeOfEdge noEdge)const;
private:
    int CreditSum;
    struct edge
    {
        int beg, end;
        TypeOfEdge w;
        bool operator<(const edge &rp)const{return w<rp.w;};
    };
    struct edgeNode //邻接表中存储边的节点类
    {
        int end;    //终点编号(应该是指这个节点)
        TypeOfEdge weight; //边的权值
       
        edgeNode *next; //后继指针
       
        edgeNode(int e, TypeOfEdge w, edgeNode* n=nullptr)
        {
            end = e;
            weight = w;
            next = n;
        }
    };   

    struct verNode  //保存顶点的数据元素类型
    {
        TypeOfVer ver;  //顶点值
        int Credit;
        edgeNode *head;     //对应的单链表的头指针

        verNode(edgeNode *h=nullptr)
        {
            head = h;
        }
    };

    verNode *verList;

    int find(TypeOfVer v)const
    {
        for (int i=0; i<this->Vers; ++i)
            if (verList[i].ver==v)
                return i;
        return -1;
    }

    void dfs(int start, bool visited[])const;
};
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topsort()
{
    
    queue<int> q;
    edgeNode *p;
    int current;
    int *inDegree = new int[this->Vers];
    for (int i=0; i<this->Vers; ++i)
    {
        inDegree[i]=0;
    }

    for (int i=0; i<this->Vers;++i)
    {
        for (p=verList[i].head; p!=nullptr; p=p->next)
            ++inDegree[p->end];
    }
    for (int i=0; i<this->Vers; ++i)
        if (inDegree[i]==0) q.push(i);
    cout<<"拓扑排序为："<<endl;
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        cout<<verList[current].ver<<'\t';
        for (p=verList[current].head; p!=nullptr; p=p->next)
        {
            if (--inDegree[p->end]==0)
                q.push(p->end);
        }
    }
    cout<<endl<<endl;
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge)const
{
    bool *flag = new bool[this->Vers];
    TypeOfEdge *lowCost=new TypeOfEdge[this->Vers];
    int *startNode=new int[this->Vers];

    edgeNode *p;
    TypeOfEdge min;
    int start, i, j;
    for (i=0; i<this->Vers; ++i)    //initiation: assuming that there is no edge 
    {
        flag[i]=false;
        lowCost[i]=noEdge;
    }

    start=0;    //first, add node 0 to the Tree
    for (i=1; i<this->Vers; ++i)
    {
        for (p=verList[i].head; p!=nullptr; p=p->next)
        {
            if (!flag[p->end] && lowCost[p->end]>p->weight)
            {   //upadte the distance information
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;
            }
            flag[start] = true;
            min = noEdge;
            for (j=0; j<this->Vers; ++j)    //find the minimize edge from U to V-U 
                if (lowCost[j]<min)
                {
                    min=lowCost[j];
                    start=j;
                }
            cout<<'('<<verList[startNode[start]].ver<<','<<verList[start].ver<<")\t";
            lowCost[start]=noEdge;     
        }
    }
    delete [] flag;
    delete [] startNode;
    delete []lowCost;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal()const
{
    int edgesAccepted=0, u, v;
    edgeNode *p;
    edge e;
    DisjointSet ds(this->Vers);
    priority_queue<edge> pq;

    //initiate prority_queue
    for (int i=0; i<this->Vers; ++i)
    {
        for (p=verList[i].head; p!=nullptr; p=p->next)
        {
            if (i<p->end)
            {
                e.beg=i;
                e.end=p->end;
                e.w=p->weight;
                pq.push(e);
            }
        }
    }

    while (edgesAccepted <this->Vers-1)
    {
        e=pq.top();     //get the minimun edge
        pq.pop();
        u=ds.Find(e.beg);
        v=ds.Find(e.end);
        if(u!=v)    //after add (u,v) there will not form a loop 
        {
            edgesAccepted++;
            ds.Union(u,v);
            cout<<'('<<verList[e.beg].ver<<','<<verList[e.end].ver<<")\t";
        }
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::way1sort()
{
    queue<int> q;
    edgeNode *p;
    int current;
    int *inDegree = new int[this->Vers];
    for (int i=0; i<this->Vers; ++i)
    {
        inDegree[i]=0;
    }

    for (int i=0; i<this->Vers;++i)
    {
        for (p=verList[i].head; p!=nullptr; p=p->next)
            ++inDegree[p->end];
    }
    for (int i=0; i<this->Vers; ++i)
        if (inDegree[i]==0) q.push(i);
    cout<<"第一种排序为："<<endl;
    int index=1;
    int creditsum=0;
    cout<<"第 "<<index<<"th 个学期:\n";
    while (!q.empty())
    {
        current = q.front();
        if (creditsum< CreditSum/(float)6 && (creditsum +verList[current].Credit)<=10 )
        {
            q.pop();
            creditsum+=verList[current].Credit;
            //cout<<"Size:"<<q.size()<<endl;
            cout<<verList[current].ver<<'\t';
            for (p=verList[current].head; p!=nullptr; p=p->next)
            {
                if (--inDegree[p->end]==0)
                    q.push(p->end);
            }
        }
        else
        {
            index++;
            creditsum=0;
            cout<<"\n\n";
            cout<<"第 "<<index<<"th 个学期:\n";
        }

    }
    cout<<endl<<endl;
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::way2sort()
{
    queue<int> q;
    edgeNode *p;
    int current;
    int *inDegree = new int[this->Vers];
    for (int i=0; i<this->Vers; ++i)
    {
        inDegree[i]=0;
    }

    for (int i=0; i<this->Vers;++i)
    {
        for (p=verList[i].head; p!=nullptr; p=p->next)
            ++inDegree[p->end];
    }
    for (int i=0; i<this->Vers; ++i)
        if (inDegree[i]==0) q.push(i);
    cout<<"第二种排序为："<<endl;
    int index=1;
    int creditsum=0;
    cout<<"第 "<<index<<"th 个学期:\n";
    while (!q.empty())
    {
        current = q.front();
        if ((creditsum +verList[current].Credit)<=10 )
        {
            q.pop();
            creditsum+=verList[current].Credit;
            //cout<<"Size:"<<q.size()<<endl;
            cout<<verList[current].ver<<'\t';
            for (p=verList[current].head; p!=nullptr; p=p->next)
            {
                if (--inDegree[p->end]==0)
                    q.push(p->end);
            }
        }
        else
        {
            index++;
            creditsum=0;
            cout<<"\n\n";
            cout<<"第 "<<index<<"th 个学期:\n";
        }

    }
    cout<<endl<<endl;
}
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer,TypeOfEdge>::showEdge()
{
    for (int i=0; i<this->Vers; ++i)
    {
        edgeNode *p= verList[i].head;
        cout<<verList[i].ver<<'\t';
        while (p!=nullptr)
        {
            cout<<verList[p->end].ver<<'\t';
            p=p->next;
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool[this->Vers];
    int currentNode;
    queue<int> q;
    edgeNode *p;

    for (int i=0; i<this->Vers; ++i)
        visited[i]=false;
    
    cout<<"当前图的广度优先序列为:"<<endl;

    for (int i=0; i<this->Vers; ++i)
    {
        if (visited[i]==true)
            continue;
        q.push(i);
        while(!q.empty())
        {
            currentNode = q.front();
            q.pop();
            if (visited[currentNode]==true)
                continue;
            cout<<verList[currentNode].ver<<'\t';
            visited[currentNode]=true;

            p=verList[currentNode].head;
            while(p!=nullptr)   //push the next node of curentnode into the queue
            {
                if (visited[p->end] == false)
                    q.push(p->end);
                p = p->next;
            }
        }
    }
    cout<<endl<<endl;
}


template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited = new bool[this->Vers];   //记录每个节点是否已被访问
    
    for (int i=0; i<this->Vers; ++i)
        visited[i]=false;

    cout<<"当前图的深度优先遍历为:"<<endl;

    for (int i=0; i<this->Vers; ++i)
    {
        if (visited[i]==true) 
            continue;
        dfs(i, visited);
        cout<<endl;
    }
    cout<<endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[])const
{
    edgeNode *p = verList[start].head;

    cout<<verList[start].ver<<'\t';     //visit the node
    visited[start] = true;

    while (p!=nullptr)
    {
        if (visited[p->end]==false)
            dfs(p->end, visited);
        p = p->next;
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[], const int weight[])
{
    this->Vers = vSize;
    this->Edges = 0;
    CreditSum = 0;
    verList = new verNode[vSize];
    for (int i=0; i<this->Vers; ++i)
    {
        verList[i].ver = d[i];
        verList[i].Credit = weight[i];
        CreditSum+=weight[i];
    }
}

template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    int i;
    edgeNode *p;

    for (i=0; i<this->Vers; ++i)
        while ((p=verList[i].head)!=nullptr)    //当节点还存在边
        {
            //release the single list of the i th node
            verList[i].head = p->next;
            delete p;
        }
    delete [] verList;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u=find(x), v=find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u=find(x), v=find(y);
    edgeNode *p=verList[u].head, *q;
    
    if (p==nullptr)
        return;     //没有相连的边

    if (p->end == v)    //the first node in the Edge List is the one to be deleted
    {
        verList[u].head = p->next;
        delete p;
        --this->Edges;
        return;
    }
    while (p->next!=nullptr && p->next->end!=v)
        p=p->next;
    //at this time p->next->end == v or p->next ==nullptr
    if (p->next != nullptr)
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y)const
{
    int u=find(x), v=find(y);
    edgeNode *p=verList[u].head;
    
    while (p!=nullptr && p->end!=v)
        p=p->next;
    
    if (p==nullptr)
        return false;
    else return true;
}

