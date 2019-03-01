#include <iostream>
#include "adjListGraph.h"
struct Edge
{
    int a;
    int b;
};
int main()
{
    int ver[7];
    Edge edge[11]{{5,6},{5,7},{7,6},{6,2},{2,4},{7,4},{1,2},{4,1},{4,3},{3,1},{2,3}};
    for (int i=0; i<7; ++i)
        ver[i]=i+1;
    adjListGraph<int, int> g(7,ver);
    for (int i=0; i<11; ++i)
    {
        g.insert(edge[i].a,edge[i].b,1);
        g.showEdge();
    }

    g.dfs();
    g.bfs();
    std::cout<<"Hello WOrld";
    return 0;
}

