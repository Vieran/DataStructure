/*基数排序*/
//以十进制为例

#include "Set.h"

#ifndef BUCKETSORT_H
#define BUCKETSORT_H

//口袋排序的节点类
template <class OTHER>
struct node
{
    Set<int, OTHER> data;
    node *next;

    node() : next(NULL) {}
    node(Set<int, OTHER> d) : data(d), next(NULL) {}
};

//基数排序
//复杂度O(len*n)，稳定的排序（n是所有数据的最大位数）
template <class KEY, class OTHER>
void bucketSort(node<OTHER> *&p) //p是链表头
{
    node<OTHER> *tail;
    int max = 0;
    for (tail = p; tail != NULL; tail = tail->next) //寻找最大键值
        if (tail->data.key > max)
            max = tail->data.key;

    //求出最大键值的位数
    int len = 0;
    if (max == 0)
        len = 0;
    else
        while (max > 0)
        {
            ++len;
            max /= 10;
        }

    node<OTHER> *bucket[10], *last[10]; //bucket是口袋头，last是口袋尾
    int k, base = 1;
    for (int i = 1; i <= len; i++) //执行len次的分配与重组
    {
        for (int j = 0; j <= 9; ++j) //清空口袋
            bucket[j] = last[j] = NULL;

        while (p != NULL) //每个for循环内，此循环依次按照个位数、十位数……分配
        {
            k = p->data.key / base % 10;

            //将元素链接进去
            if (bucket[k] == NULL) //该链表为空
                bucket[k] = last[k] = p;
            else
                last[k] = last[k]->next = p;

            p = p->next;
        }

        p = NULL;                    //重组后的链表头
        for (int j = 0; j <= 9; j++) //将各个链表进行连接
        {
            if (bucket[j] == NULL)
                continue;
            if (p == NULL)
                p = bucket[j];
            else
                tail->next = bucket[j];

            tail = last[j]; //设置好整个链表的表尾
        }
        tail->next = NULL; //链表尾的下一个是空
        base *= 10;        //base翻10倍，为下一次分配作准备
    }
}

#endif