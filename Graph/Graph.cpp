#include <iostream>
#include "Graph.h"
#include "adjMatrixGraph.h"
#include "adjListGraph.h"
using namespace std;

int main()
{
    //测试邻接矩阵
    adjMatrixGraph<char,int> m(10,"abcdefghiz",-1);//构建对象m，10个结点分别为abcdefghiz，表示边不存在的标志是-1
    m.insert('a','f',9);//在a和f之间插入权值为9的边
    m.remove('a','f');//删除a和f之间的边

    //测试邻接表
    adjListGraph<char,int> l(10,"abcdefghiz");//构建对象l，10个结点分别为abcdefghiz
    l.insert('a','f',9);//在a和f之间插入权值为9的边
    l.remove('a','f');//删除a和f之间的边

    return 0;
}