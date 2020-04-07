/*基于邻接矩阵的图类的定义*/

#include "Graph.h"
#include <iostream>
using namespace std;

#ifndef ADJMATRIXGRAPH_H
#define ADJMATRIXGRAPH_H

template <class TypeOfVer,class TypeOfEdge>
class adjMatrixGraph:public graph<TypeOfVer,TypeOfEdge>
{
private:
    TypeOfEdge **edge;//存放邻接矩(动态的二维数组)
    TypeOfVer *ver;//存放结点值（一位数组）
    TypeOfEdge noEdge;//存放矩阵中的∞表示值（标记结点不存在）
    int find(TypeOfVer v) const//找出值为v的结点的内部编号
    {
        for (int i = 0; i < this->Vers; ++i)
            if(ver[i] == v)
                return i;
    }

public:
    adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag);
    ~adjMatrixGraph();
    void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w);
    void remove(TypeOfVer x,TypeOfVer y);
    bool exist(TypeOfVer x,TypeOfVer y) const;
};

#endif



//构造函数（构造一个只有结点，没有边的图）
//参数：结点数，结点值，邻接矩阵中表示结点间无边的标
template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::adjMatrixGraph(int vSize,const TypeOfVer d[],const TypeOfEdge noEdgeFlag)
{
    //设置存放结点数和边数的值
    this->Vers = vSize;
    this->Edges = 0;
    
    //邻接矩阵的数据成员的初始化
    noEdge = noEdgeFlag;//无边标记着三个数据成员

    ver = new TypeOfVer[vSize];//申请存储结点的值的一维数组的动态空间
    for(int i=0;i<vSize;++i)//初始化一维数组
        ver[i] = d[i];
    
    edge = new TypeOfEdge*[vSize];//申请存放边的二维数组的动态空间
    for (int i = 0; i < vSize; ++i)//邻接矩阵的初始化
    {
        edge[i] = new TypeOfEdge[vSize];
        for(int j = 0; j < vSize; ++j)
            edge[i][j] = noEdge;
        edge[i][i] = 0;
    }
}


//析构函数
template <class TypeOfVer,class TypeOfEdge>
adjMatrixGraph<TypeOfVer,TypeOfEdge>::~adjMatrixGraph()
{
    delete [] ver;
    for(int i = 0;i < this->Vers; ++i)
        delete [] edge[i];//释放邻接矩阵中的每一行
    delete [] edge;
}


//在x和y之间加入一条权值为w的边
template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w)
{
    int u = find(x),v = find(y);//找到结点
    edge[u][v] = w;//将权值赋给邻接矩阵
    ++this->Edges;//边数增加1
}


//删除x和y之间的边
template <class TypeOfVer,class TypeOfEdge>
void adjMatrixGraph<TypeOfVer,TypeOfEdge>::remove(TypeOfVer x,TypeOfVer y)
{
    int u = find(x), v = find(y);
    edge[u][v] = noEdge;//将对应邻接矩阵中的值更改
    --this->Edges;//边数减少1
}


//判断x和y之间是否存在边
template <class TypeOfVer,class TypeOfEdge>
bool adjMatrixGraph<TypeOfVer,TypeOfEdge>::exist(TypeOfVer x,TypeOfVer y) const
{
    int u = find(x), v = find(y);//找到x和y的对应下标
    if(edge[u][v]==noEdge)//判断x和y之间是否存在边
        return false;
    else
        return true;
}