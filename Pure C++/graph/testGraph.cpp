#include <iostream>
#include "adjListGraph.h"
int main()
{
    int ver[7];
    for (int i=0; i<7; ++i)
        ver[i]=i+1;
    adjListGraph<int, int> g(10,ver);
    for (int i=0; i<11; ++i)
    {
        cout<<"Pls input the Edge:";
        int a,b;
        cin>>a>>b;
        g.insert(a,b,1);
    }
    g.dfs();
    std::cout<<"Hello WOrld";
    return 0;
}

