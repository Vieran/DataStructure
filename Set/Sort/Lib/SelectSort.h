/*选择排序*/

#include "Set.h"

#ifndef SELECTSORT_H
#define SELECTSORT_H

//直接选择排序
//复杂度O(n^2),稳定的排序
template <class KEY, class OTHER>
void simpleSelectSort(Set<KEY, OTHER> a[], int size)
{
    int j, min; //min是最小元素的下标
    Set<KEY, OTHER> tmp;
    for (int i = 0; i < size - 1; i++)
    {
        min = i; //设置当前位置为最小，开始寻找更小的元素
        for (j = i + 1; j < size; ++j)
            if (a[j].key < a[min].key)
                min = j;

        //交换最小元素和当前位置元素
        tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }
}

//参数hole是向下过滤的起始下标
template <class KEY, class OTHER>
void percolateDown(Set<KEY, OTHER> a[], int hole, int size)
{
    Set<KEY, OTHER> tmp = a[hole];
    int child;                  //左子节点的下标
    while (hole * 2 + 1 < size) //寻找子树中的最大元素
    {
        child = hole * 2 + 1;
        if (child != size - 1 && a[child + 1].key > a[child].key) //获取左右子树中较大的一个
            ++child;
        if (a[child].key > tmp.key) //子节点比当前结点大，不符合定义
            a[hole] = a[child];     //当前结点和子节点互换
        else
            break;    //找到合适的位置，跳出循环
        hole = child; //继续向下过滤
    }
    a[hole] = tmp; //将tmp（原来的hole）放入合适的位置
}

//堆排序
//复杂度O(nlog2n)，不稳定的排序
template <class KEY, class OTHER>
void heapSort(Set<KEY, OTHER> a[], int size)
{
    Set<KEY, OTHER> tmp;

    //创建初始的堆
    for (int i = size / 2 - 1; i >= 0; i--) //对每一个非叶子结点进行调整（初始i是最后一个叶子结点的父节点）
        percolateDown(a, i, size);          //向下过滤，调整数组成为一个最大化堆

    //每一次循环中，a[0]都是最大元素
    for (int i = size - 1; i > 0; i--)
    {
        //将最大元素依次放到数组倒数第一个、第二个、第三个……
        tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        percolateDown(a, 0, i); //向下过滤，调整树
    }
}

#endif