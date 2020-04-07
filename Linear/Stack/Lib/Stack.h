#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;


//栈的抽象类
template <class elemType>
class stack
{
public:
    virtual bool isEmpty() const = 0;//判断栈空
    virtual void push(const elemType &x) = 0;//进栈
    virtual elemType pop() = 0;//出栈
    virtual elemType top() const = 0;//取栈顶元素
    virtual ~stack(){}//虚析构函数
};

#endif