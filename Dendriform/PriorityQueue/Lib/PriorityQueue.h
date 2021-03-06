//优先级队列类的定义
//最小化堆

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
using namespace std;

template <class elemType>
class PriorityQueue
{
private:
    int currentSize;//队列中元素的个数
    elemType *array;//保存二叉堆数组的起始地址
    int maxSize;//数组规模

    void doubleSpace();//扩大容量
    void buildHeap();//工具函数
    void percolateDown(int hole);//工具函数（向下过滤）
public:
    PriorityQueue(int capacity=10);//创建一个空的优先级队列
    PriorityQueue(const elemType data[],int size);//对一批已有的数据创建一个队列

    ~PriorityQueue()
    {
        delete [] array;
    }

    bool isEmpty() const//判断队列是否为空
    {
        return currentSize == 0;
    }

    void enQueue(const elemType &x);
    elemType deQueue();

    elemType getHead() const
    {
        return array[1];
    }
};
#endif

//构造函数
template <class elemType>
PriorityQueue<elemType>::PriorityQueue(int capacity)//函数定义的时候，不能将默认值写出？！
{
    array = new elemType[capacity];//用数组存储，因为是完全二叉树
    maxSize = capacity;//初始化数组大小
    currentSize = 0;
}

//存入元素
template <class elemType>
void PriorityQueue<elemType>::enQueue(const elemType &x)
{
    if(currentSize==maxSize-1)//检查是否存在可用位置
        doubleSpace();//如果空间不够则扩容
    
    //向上过滤
    int hole = ++currentSize;//申请下一个可用节点
    for (; hole>1 && x<array[hole/2]; hole/=2)//如果违反堆的有序性，则向上冒
        array[hole] = array[hole/2];
    array[hole] = x;
}

//删除元素
template <class elemType>
elemType PriorityQueue<elemType>::deQueue()
{
    elemType minItem;
    minItem = array[1];//将根节点暂存在变量minItem中
    array[1] = array[currentSize--];//将最后一个元素挪到根节点中
    percolateDown(1);//向下过滤
    return minItem;
}

//向下过滤
template <class elemType>
void PriorityQueue<elemType>::percolateDown(int hole)
{
	int child;//左右子节点中的较小者的下标（因为成为父节点必须要比另外一个子节点小）
    elemType tmp = array[hole];//将需要调整位置的值保存在变量tmp中

    //向下过滤
    while (hole*2<=currentSize)//从当前节点开始，逐层向下过滤
    {
        child = hole*2;//找到当前节点的左子节点，将其值存入child变量
		
        if(child!=currentSize && array[child+1]<array[child])//比较左右子节点，筛选出较小的子节点
            child++;//是则将下标保存于child变量

        if(array[child]<tmp)//判断较小的子节点是否小于需要调整位置的值
            array[hole] = array[child];//调节当前父节点和子节点的位置
        else//否则当前空节点是合适的位置
            break;
        
        hole = child;
    }
    array[hole] = tmp;//将tmp的值放入空节点
}

//对已经给定数据的堆进行排序
template <class elemType>
void PriorityQueue<elemType>::buildHeap()
{
    for(int i=currentSize/2;i>0;i--)//从最后一个非叶子节点开始，这样每次使用向下过滤的时候，都可以直接使用percolateDown函数
        percolateDown(i);//使堆有序
}

//实现给定初始数据的构造函数
template <class elemType>
PriorityQueue<elemType>::PriorityQueue(const elemType *items,int size):maxSize(size+10),currentSize(size)
{
    array = new elemType[maxSize];
    for(int i=0;i<size;++i)
        array[i+1] = items[i];
    buildHeap();
}

//扩容函数的实现
template <class elemType>
void PriorityQueue<elemType>::doubleSpace()
{
    elemType *tmp = array;
    maxSize *= 2;
    array = new elemType[maxSize];
    for(int i=0;i<=currentSize;++i)
        array[i] = tmp[i];
    delete [] tmp;
}

