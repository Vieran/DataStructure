/*交换排序*/

#include "Set.h"

#ifndef EXCHANGESORT_H
#define EXCHANGESORT_H

//冒泡排序
//复杂度O(n)~O(n^2)
template <class KEY, class OTHER>
void bubbleSort(Set<KEY, OTHER> a[], int size)
{
    Set<KEY, OTHER> tmp;
    bool flag; //记录一次起泡中是否发生过交换

    for (int i = 0; i < size && flag; i++)
    {
        flag = false;
        for (int j = 0; j < size - 1; ++j)
            if (a[j + 1].key < a[j].key) //前后顺寻不对，交换元素位置
            {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                flag = true
            }
    }
}

//快速排序
//复杂度O(nlog2n)，不稳定排序
template <class KEY, class OTHER>
void quickSort(Set<KEY, OTHER> a[], int size)
{
    quickSort(a, 0, size - 1);
}

//划分函数（寻找划分点）
template <class KEY, class OTHER>
int divide(Set<KEY, OTHER> a[], int low, int high)
{
    Set<KEY, OTHER> tmp = a[low];
    do
    {
        while (low < high && a[high].key >= tmp.key) //移动high指针直到遇到比tmp小的元素
            --high;
        if (low < high) //确定仍然是没有结束循环，进行元素的交换
        {
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low].key <= tmp.key) //移动low指针直到遇到比tmp大的元素
            ++low;
        if (low < high) //确定仍然是没有结束循环，进行元素的交换
        {
            a[high] = a[low];
            --high;
        }
    } while (low != high);
    a[low] = tmp; //将tmp放到划分点
    return low;
}

template <class KEY, class OTHER>
void quickSort(Set<KEY, OTHER> a[], int low, int high)
{
    int mid;
    if (low >= high) //带分段元素个数为1或者0，直接结束
        return;
    mid = divide(a, low, high);
    quickSort(a, low, mid - 1);  //排序左半个数组
    quickSort(a, mid + 1, high); //排序右半个数组
}

#endif