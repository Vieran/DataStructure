/*插入排序*/

#include "Set.h"

#ifndef INSERTSORT_H
#define INSERTSORT_H

//直接插入排序
//复杂度O(n^2)，稳定的排序
template <class KEY, class OTHER>
void simpleInsertSort(Set<KEY, OTHER> a[], int size)
{
    Set<KEY, OTHER> tmp;
    int k;
    for (int i = 1; i < size; i++)
    {
        tmp = a[i];
        for (k = i - 1; tmp.key < a[k].key && k >= 0; --k) //将所有比tmp大的元素向后移动一位
            a[k + 1] = a[k];
        a[k + 1] = tmp;
    }
}

//希尔排序
//无法计算（大约在n^1.25到1.6n^1.25范围内），不稳定的排序
template <class KEY, class OTHER>
void shellSort(Set<KEY, OTHER> a[], int size)
{
    Set<KEY, OTHER> tmp;
    int gap, i, j;

    //这种做法诠释了为什么希尔排序是插排的一种！！！妙啊
    for (gap = size / 2; gap > 0; gap /= 2) //设置希尔增量
        for (i = gap; i < size; i++)        //通过巧妙的方法，避免了一个for循环
        {
            tmp = a[i];
            for (j = i - gap; j >= 0 && a[j].key > tmp.key; j -= gap) //每次进行这个循环，该序列的前面的元素都是已经排好序的了
                a[j + gap] = a[j];
            a[j + gap] = tmp;
        }
}

#endif