//树的抽象类
#ifndef TREE_H
#define tree_h

#include <iostream>
using namespace std;

template <class elemType>
class Tree
{
public:
    virtual void clear() = 0;//删除树中所有的节点
    virtual bool isEmpty() const = 0;//判断是否为空树
    virtual elemType root(elemType flag) const = 0;//找出树的根节点；如果树空则返回特殊值
    virtual elemType parent(elemType x,elemType flag) const = 0;//寻找x的父节点的值；如果树空则返回特殊值
    virtual elemType child(elemType x,int i,elemType flag) const = 0;//寻找x的第i个子节点的值；如果树空则返回特殊值
    virtual void remove(elemType x,int i) = 0;//删除节点x的第i颗子树
    virtual void traverse() const = 0;//遍历整棵树访（问每一个节点一次）
};


#endif