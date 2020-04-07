//顺序队列的定义和实现

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include "Queue.h"

//此版本设置“服务台”来判断队列是否为空
template <class elemType>
class seqQueue:public Queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front,rear;//front所指的元素必须为空
    void doubleSpace();
public:
    seqQueue(int size=10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
};

/*顺序队列类的函数实现*/

//构造函数
template <class elemType>
seqQueue<elemType>::seqQueue(int size)
{
    elem = new elemType[size];//动态分配空间
    maxSize = size;
    front = rear = 0;//将初始值设置为0
}

//析构函数
template <class elemType>
seqQueue<elemType>::~seqQueue()
{
    delete [] elem;
}

//判断队列是否为空
template <class elemType>
bool seqQueue<elemType>::isEmpty() const
{
    return front == rear;
}

//进队函数
template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)
{
    if((rear+1)%maxSize==front)//判断队列是否满
        doubleSpace();//扩容
    rear = (rear + 1)%maxSize;
    elem[rear] = x;
}

//出队函数
template <class elemType>
elemType seqQueue<elemType>::deQueue()
{
    front = (front+1)%maxSize;
    return elem[front];
}

//返回队头元素
template <class elemType>
elemType seqQueue<elemType>::getHead() const
{
    return elem[(front+1)%maxSize];
}

//扩容函数
template <class elemType>
void seqQueue<elemType>::doubleSpace()
{
    elemType *tmp = elem;
    elem = new elemType[2*maxSize];
    for(int i=1;i <= maxSize;++i)
        elem[i] = tmp[(front+1)%maxSize];
    front = 0;//因为maxSize增大了，所以需要front减少来弥补
    rear = maxSize;
    maxSize *= 2;
    delete [] tmp;
}

//此版本设置“队列长度”来判断队列是否为空
/*
template <class elemType>
class seqQueue : public Queue<elemType>
{
private:
    elemType *elem;
    int maxSize;
    int front; //front所指的元素可不为空
    int length;
    void doubleSpace()
    {
        elemType *tmp = elem;

        elem = new elemType[2*maxSize];
        for (int i = 0; i < maxSize; i++)
            elem[i] = tmp[(front+i+1)%maxSize];
        front = -1;//这个操作是重点，牵涉到进队和出队函数！
        maxSize *= 2;

        delete [] tmp;
    }

public:
    //构造函数
    seqQueue(int size = 10)
    {
        elem = new elemType[size]; //动态分配空间
        maxSize = size;
        front = -1; //初始值设置为-1
        length = 0; //长度设置初值为0
    }

    //析构函数
    ~seqQueue()
    {
        delete [] elem;
    }

    //判断队列是否为空
    bool isEmpty() const
    {
        return length == 0;
    }

    //进队函数
    void enQueue(const elemType &x)
    {
        if (length == maxSize) //判断队列是否满
            doubleSpace();     //扩容
        int rear = (front + length + 1) % maxSize;
        elem[rear] = x;
        ++length;
    }

    //出队函数
    elemType deQueue()
    {
        front = (front + 1) % maxSize;
        --length;
        return elem[front];
    }

    //返回队头元素
    elemType getHead() const
    {
        return elem[(front + 1) % maxSize];
    }
};
*/

#endif