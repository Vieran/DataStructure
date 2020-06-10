/*散列表的定义和实现文件*/
//包含闭散列表和开散列表
//假设采用的散列函数是除留余数法

#include "DynamicSearch.h"
using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

/*基于线性探测法的闭散列表的实现*/
template <class KEY, class OTHER>
class closeHashTable : public DynamicSearchTable<KEY, OTHER>
{
private:
    struct node //散列表的节点类
    {
        enum STATE
        {
            EMPTY,
            ACTIVE,
            DELETED
        };
        Set<KEY, OTHER> data;
        STATE state; //当前节点的状态

        node() : state(EMPTY) {} //节点状态初始化为空
    };

    node *array;                        //保存查找表的元素
    int size;                           //数组的大小
    int (*key)(const KEY &x);           //指向函数的指针
    static int defaultKey(const int &x) //当用户不提供转换函数（将数据元素中的关键字转换成为整数）的时候，直接默认函数
    {
        return x;
    }

public:
    closeHashTable(int length = 11, int (*f)(const KEY &x) = defaultKey);
    ~closeHashTable()
    {
        delete[] array;
    }
    Set<KEY, OTHER> *find(const KEY &x) const;
    void insert(const Set<KEY, OTHER> &x);
    void remove(const KEY &x);
};

/*开散列表*/
template <class KEY, class OTHER>
class openHashTable : public DynamicSearchTable<KEY, OTHER>
{
private:
    struct node
    {
        Set<KEY, OTHER> data;
        node *next;

        node(const Set<KEY, OTHER> &d, node *n = NULL)
        {
            data = d;
            next = n;
        }
        node() : next(NULL) {} //默认构造函数
    };

    node **array; //指针数组
    int size;
    int (*key)(const KEY &x);
    static int defaultKey(const int &x)
    {
        return x;
    }

public:
    openHashTable(int length = 11, int (*f)(const KEY &x) = defaultKey);
    ~openHashTable();
    Set<KEY, OTHER> *find(const KEY &x) const;
    void insert(const Set<KEY, OTHER> &x);
    void remove(const KEY &x);
};

#endif

//第一个参数是数组长度，第二个参数是一个函数
template <class KEY, class OTHER>
closeHashTable<KEY, OTHER>::closeHashTable(int length = 11, int (*f)(const KEY &x) = defaultKey)
{
    size = length; //设置数组长度
    array = new node[size];
    key = f;
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::insert(const Set<KEY, OTHER> &x)
{
    int initPos, pos;
    initPos = pos = key(x.key) % size; //计算待插入元素的散列地址

    do //用线性探测法寻找插入的位置（找到空位）
    {
        if (array[pos].state != ACTIVE)
        {
            array[pos].data = x;
            array[pos].state = ACTIVE;
            return;
        }
        pos = (pos + 1) % size; //到下一个位置
    } while (pos != initPos);   //当pos回到initPos的时候，经过了一轮循环，但是没有找到插入位置，插入失败
}

template <class KEY, class OTHER>
void closeHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int initPos, pos;
    initPos = pos = key(x) % size;

    do //找到元素的位置
    {
        if (array[pos].state == EMPTY) //单元不存在
            return;
        if (array[pos].state == ACTIVE && array[pos].data.key == x) //单元存在且未被删除
        {
            array[pos].state = DELETED; //删除单元
            return;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos); //没有找到被删节点，删除失败
}

template <class KEY, class OTHER>
Set<KEY, OTHER> *closeHashTable<KEY, OTHER>::find(const KEY &x) const
{
    int initPos, pos;
    initPos = pos = key(x) % size;
    do
    {
        if (array[pos].state == EMPTY) //单元不存在
            return NULL;
        if (array[pos].state == ACTIVE && array[pos].data.key == x) //单元存在且未被删除
            return (Set<KEY, OTHER> *)&array[pos];                  //返回节点（采用引用返回的方式，返回的是指针）

        pos = (pos + 1) % size;
    } while (pos != initPos);
}

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::openHashTable(int length = 11, int (*f)(const KEY &x) = defaultKey)
{
    size = length;
    array = new node *[size]; //这里node和*一起表示指针类型

    key = f;
    for (int i = 0; i < size; i++) //设置指针为空
        array[i] = NULL;
}

template <class KEY, class OTHER>
openHashTable<KEY, OTHER>::~openHashTable()
{
    node *p, *q;
    for (int i = 0; i < size; i++) //释放存放散列表的数组和每个单链表的节点空间
    {
        p = array[i];
        while (p != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::insert(const Set<KEY, OTHER> &x)
{
    int pos;
    node *p;

    pos = key(x.key) % size;              //计算对应的散列地址
    array[pos] = new node(x, array[pos]); //将插入元素作为链表第一个元素（不设置头结点）
}

template <class KEY, class OTHER>
void openHashTable<KEY, OTHER>::remove(const KEY &x)
{
    int pos = key(x) % size; //计算位置;

    if (array[pos] == NULL) //被删结点不存在，直接返回
        return;

    node *p;
    p = array[pos];

    if (array[pos]->data.key == x) //特殊情况，被删结点是第一个结点
    {
        array[pos] = p->next;
        delete p;
        return;
    }

    while (p->next != NULL && !(p->next->data.key == x)) //到链表中寻找被删节点
        p = p->next;
    if (p->next != NULL) //找到结点则删除
    {
        node *q = p->next;
        p->next = q->next;
        delete q;
    }
}

template <class KEY, class OTHER>
Set<KEY, OTHER> *openHashTable<KEY, OTHER>::find(const KEY &x) const
{
    int pos = key(x) % size;//找到链表
    node *p = array[pos];

    while (p != NULL && !(p->data.key == x))//找到结点
        p = p->next;
    if (p == NULL)//没有找到，返回空
        return NULL;
    else//找到并返回
        return (Set<KEY, OTHER> *)p;
}