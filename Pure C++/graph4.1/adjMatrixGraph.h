#pragma once

template <class TypeOfVer, class TypeOfEdge>    //the parameter of the template is the type of Vertex and the type of weight
class Graph
{
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)=0;
    virtual void remove(TypeOfVer x, TypeOfVer y)=0;
    virtual bool exist(TypeOfVer x, TypeOfVer y)const=0;
    int numOfVer() const{return Vers;}
    int numOfEdge() const{return Edges;}

protected:
    int Vers, Edges;
};

template <class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph:public Graph<TypeOfVer, TypeOfEdge>
{
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y)const;
    ~adjMatrixGraph(); 

private:
    TypeOfEdge **edge;      //use to store the adjMatrix
    TypeOfVer *ver;     //use to store the value of vertex
    TypeOfEdge noEdge;
    int find(TypeOfVer v)const
    {
        for (int i=0; i<this->Vers; ++i)
            if (ver[i]==v)  return i;
    }
};


//construct function
//after construction, there is no edge
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag)
{
    int i,j;

    this->Vers = vSize;
    this->Edges = 0;
    noEdge = noEdgeFlag;

    //存放节点的数组的初始化
    ver = new TypeOfVer[vSize];
    for (i=0; i<vSize; ++i)
        ver[i] = d[i];
    
    //邻结矩阵的初始化
    edge = new TypeOfEdge*[vSize];
    for (i=0; i<vSize; ++i)
    {
        edge[i]= new TypeOfEdge[vSize];
        for (j=0; j<vSize; ++j)
            edge[i][j] = noEdge;
        edge[i][j] = 0;
    }
}

//destruction function
template <class TypeOfVer, class TypeOfEdge>
adjMatrixGraph<TypeOfVer, TypeOfEdge>::~adjMatrixGraph()
{
    delete[] ver;
    for (int i=0; i<this->Vers; ++i)
        delete []edge[i];
    delete[] edge;
}

//other function
template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u=find(x), v=(y);
    edge[u][v]=w;
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u=find(x), v=find(y);
    edge[u][v] = noEdge;
    --this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y)const
{
    int u=find(x), v=find(y);
    if (edge[u][v]==noEdge)
        return false;
    else 
        return true;
}

