#ifndef SEQSTACK_H
#define SEQSTACK_H

#include "Stack.h"

//顺序栈类的定义
template <class elemType>
class seqStack:public stack<elemType>
{
private:
    elemType *elem;//存储数组名
    int top_p;//存储栈顶的位置
    int maxSize;//存储数组的规模
    void doubleSpace();//为数组扩容（设为私有函数，防止外部掉用）
public:
    seqStack(int initSize = 1);//构造函数，默认数组大小为1
    ~seqStack();
    bool isEmpty() const;
    void push(const elemType &x);
    elemType pop();
    elemType top() const;
};

//顺序栈的运算，除了进栈操作，所有运算实现的时间复杂度都是O(1)
//一般情况下，进栈操作的时间复杂度也为O(1),最坏的情况下（扩容）才会导致复杂度为O(n)，因此平均下来，复杂度也是O(1)
//综上，顺序栈的运算时间复杂度都是O(1)



//顺序栈的函数实现

//构造函数
template <class elemType>
seqStack<elemType>::seqStack(int initSize)
{
    elem = new elemType[initSize];//为数组申请动态空间
    maxSize = initSize;//数组规模
    top_p = -1;//栈空时，栈顶值设为-1
}

//析构函数
template <class elemType>
seqStack<elemType>::~seqStack()
{
    delete [] elem;//归还空间
}

//判断栈是否为空
template <class elemType>
bool seqStack<elemType>::isEmpty() const
{
    return top_p ==-1;
}

//进栈函数
template <class elemType>
void seqStack<elemType>::push(const elemType &x)
{
    if(top_p == maxSize-1)//判断是否栈满
        doubleSpace();//栈满则扩容
    elem[++top_p] = x;
}

//出栈函数
template <class elemType>
elemType seqStack<elemType>::pop()
{
    return elem[top_p--];
}

//取栈顶元素值
template <class elemType>
elemType seqStack<elemType>::top() const
{
    return elem[top_p];
}


template <class elemType>
void seqStack<elemType>::doubleSpace()
{
    elemType *tmp = elem;//将elem的值赋给临时指针
    elem = new elemType[2*maxSize];//为elem申请新的更大的空间

    for(int i=0;i<maxSize;++i)//将原来是栈的内容复制到新的空间中
        elem[i] = tmp[i];

    delete [] tmp;//回收原来的空间

    maxSize *= 2;//更改数组容量的值
}


#endif