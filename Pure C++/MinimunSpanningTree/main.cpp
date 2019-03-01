#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>
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
    
    
    int verNum;
    cout<<"请输入有多少门课：";
    cin>>verNum;
    string *ver=new string[verNum];
    int *weight=new int[verNum];
    for (int i=0; i<verNum; ++i)
    {
        cout<<"请输入课程名：";
        cin>>ver[i];
        cout<<"请输入该课程的学分";
        cin>>weight[i];
    }

    string preCourse,nextCourse;
    int numberofEdge=0;
    queue<Edge<string>> q;
    while (true)
    {
        cout<<"请输入先修课程：(用#结束)";
        cin>>preCourse;
        cout<<"请输入该课程：（用#结束)";
        cin>>nextCourse;
        if (preCourse == "#" || nextCourse == "#")
            break;
        q.push(Edge<string>{preCourse,nextCourse});
        numberofEdge++;
    }
    Edge<string> *edge=new Edge<string>[numberofEdge];
    for (int i=0; i<numberofEdge; ++i)
    {
        edge[i]=q.front();
        q.pop();
        cout<<edge[i].a<<'\t'<<edge[i].b;
    }
//    for (int i=0; i<12; ++i)
//        ver[i]=i+1;
    adjListGraph<string, int> g(verNum,ver,weight);
//    for (int i=0; i<16; ++i)
//    {
//        g.insert(ver[edge[i].a,edge[i].b,1);
//        g.showEdge();
//    }
//
    g.dfs();
    g.bfs();
    g.topsort();
    g.way1sort();
    g.way2sort();
    std::cout<<"Hello WOrld";
    return 0;
}

