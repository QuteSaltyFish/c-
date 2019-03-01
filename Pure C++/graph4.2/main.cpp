#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <ctime>
#include "adjListGraph.h"
using namespace std;
template <class T>
struct Edge
{
    T a;
    T b;
};
int main()
{
    
    srand((unsigned int)time(NULL));
    int verNum;
    cout<<"请输入有多少个节点:";
    cin>>verNum;
    string *ver=new string[verNum];
    int *weight=new int[verNum]{1};
    for (int i=0; i<verNum; ++i)
    {
        cout<<"请输入节点名：";
        cin>>ver[i];
//        cout<<"请输入该课程的学分";
//        cin>>weight[i];
    }

    string preCourse,nextCourse;
    int numberofEdge=0;
    queue<Edge<string>> q;
    while (true)
    {
        cout<<"请输入起始节点：(用#结束)";
        cin>>preCourse;
        cout<<"请输入后继节点：（用#结束)";
        cin>>nextCourse;
        if (preCourse == "#" || nextCourse == "#")
            break;
        q.push(Edge<string>{preCourse,nextCourse});
        numberofEdge++;
    }
    Edge<string> *GroupOfEdge=new Edge<string>[numberofEdge];
    for (int i=0; i<numberofEdge; ++i)
    {
        GroupOfEdge[i]=q.front();
        q.pop();
    }
//    for (int i=0; i<12; ++i)
//        ver[i]=i+1;
    adjListGraph<string, int> g(verNum,ver,weight);
    for (int i=0; i<numberofEdge; ++i)
    {
        int value=rand()%100+1;
        g.insert(GroupOfEdge[i].a,GroupOfEdge[i].b, value);
        g.insert(GroupOfEdge[i].b,GroupOfEdge[i].a, value);
    }

    g.showEdge();
    g.dfs();
    g.bfs();
//    g.topsort();
//    g.way1sort();
//    g.way2sort();
    g.kruskal();
    g.prim(1000);
    std::cout<<"Hello WOrld";
    delete []ver;
    delete []weight;
    delete []GroupOfEdge;
    return 0;
}

