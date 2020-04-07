//图的抽象类

#ifndef GRAPH_H
#define GRAPH_H

template <class TypeOfVer,class TypeOfEdge>
class graph
{
protected:
    int Vers,Edges;//结点数和边数
public:
    virtual void insert(TypeOfVer x,TypeOfVer y,TypeOfEdge w) = 0;//在x和y之间添加一条权值为w的边
    virtual void remove(TypeOfVer x,TypeOfVer y) = 0;//删除x和y之间的边
    virtual bool exist(TypeOfVer x,TypeOfVer y) const = 0;//判断x和y之间有没有边
    int numOfVer() const {return Vers;}//返回结点的个数
    int numOfEdge() const {return Edges;}//返回边的条数
};

#endif 

//在vc++可以直接访问父类模板中的成员，在g++中则需要用this->成员，否则报错
//adjListGraph和adjMatrixGraph中的find函数均未设置检查是否找到对应值的判断，待改进