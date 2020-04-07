#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"

//链接栈的定义
template <class elemType>
class linkStack:public stack<elemType>
{
    private:
    struct node//将节点类设置成struct类型，表示它的所有数据成员对链接栈类的成员函数公开
    {
        elemType data;
        node *next;
        //构造函数重载（一个包含了初始化列表，一个没有包含）
        node(const elemType &x,node *N = NULL)
        {
            data = x;
            next = N;
        }
        //node()::next(NULL){}此行明显出错，不知书中意为何，故暂时保留
        ~node(){}//析构函数
    };
    
    node *top_p;//指向栈顶的指针

    public:
    linkStack();
    ~linkStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

#include "Stack.h"
//链接栈的运算实现

//构造函数
template <class elemType>
linkStack<elemType>::linkStack()
{
    top_p = NULL;
}

//析构函数
template <class elemType>
linkStack<elemType>::~linkStack()
{
    node *tmp;
    while (top_p != NULL)
    {
        tmp = top_p;
        top_p = top_p->next;
        delete tmp;
    }
}

//判断是否为空函数
template <class elemType>
bool linkStack<elemType>::isEmpty() const
{
    return top_p == NULL;
}

//将元素存入表头
template <class elemType>
void linkStack<elemType>::push(const elemType &x)
{
    top_p = new node(x,top_p);
}

//弹出栈顶元素
template <class elemType>
elemType linkStack<elemType>::pop()
{
    node *tmp = top_p;
    elemType x = tmp->data;
    top_p = top_p->next;
    delete tmp;

    return x;
}

//返回栈顶元素值
template <class elemType>
elemType linkStack<elemType>::top() const
{
    return top_p -> data;
}


#endif