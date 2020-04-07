//链接队列的定义和实现

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <iostream>
using namespace std;


//队列的抽象类
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



template <class elemType>
class linkQueue:public  Queue<elemType>
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x,node *N=NULL)
        {
            data = x;
            next = N;
        }
        node():next(NULL){}//默认的构造函数，不传参，将next设置为空
        ~node(){}
    };

    node *front,*rear;
    
public:
    linkQueue();
    ~linkQueue();
    bool isEmpty() const;
    void enQueue(const elemType &x);
    elemType deQueue();
    elemType getHead() const;
    elemType getTail() const;
};

//构造函数
template <class elemType>
linkQueue<elemType>::linkQueue()
{
    front = rear = NULL;
}

//析构函数
template <class elemType>
linkQueue<elemType>::~linkQueue()
{
    node *tmp;
    while (front!=NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;//回收空间
    }
}

//判断队列是否为空
template <class elemType>
bool linkQueue<elemType>::isEmpty() const
{
    return front == NULL;
}

//返回队头元素
template <class elemType>
elemType linkQueue<elemType>::getHead() const
{
    return front->data;
}

//进队
template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
    if(rear==NULL)//判断队列是否为空
        front = rear = new node(x);
    else
        rear = rear->next = new node(x);
}

//出队，并返回出队元素的值
template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
    node *tmp = front;
    elemType value = front->data;
    front = front->next;
    if(front==NULL)//判断出队后队列是否为空
        rear = NULL;
    delete tmp;
    return value;
}

//返回队尾元素
template <class elemType>
elemType linkQueue<elemType>::getTail() const
{
    return rear->data;
}

#endif