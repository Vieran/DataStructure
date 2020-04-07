//队列的抽象类

#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

template <class elemType>
class Queue
{
public:
    virtual bool isEmpty() const = 0;//判断队列是否为空
    virtual void enQueue(const elemType &x) = 0;//进队
    virtual elemType deQueue() = 0;//出队
    virtual elemType getHead() const = 0;//读取对头元素
    virtual ~Queue(){};//虚析构函数
};

#endif