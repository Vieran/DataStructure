/*归并排序*/

#include "Set.h"

#ifndef MERGESORT_H
#define MERGESORT_H

template <class KEY, class OTHER>
void merge(Set<KEY, OTHER> a[], int left,int mid,int right)
{
    Set<KEY,OTHER> *tmp = new Set<KEY,OTHER>[right-left+1];

    int i=left,j=mid,k=0;
    while(i<mid && j<=right)//归并两个数组共同长度部分
        if(a[i].key<a[j].key)
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    while(i<mid)//前半部分没有结束，直接拷贝过来
        tmp[k++] = a[i++];
    while(j<=right)//后半部分没有结束，直接拷贝过来
        tmp[k++] = a[j++];

    for (i=0,k=left;k<=right;)//将排好序的tmp拷贝到原来的数组a中
        a[k++] = tmp[i++];
    delete [] tmp;//回收空间
}



template <class KEY, class OTHER>
void mergeSort(Set<KEY, OTHER> a[], int left,int right)
{
    int mid=(left+right)/2;
    if(left==right)
        return;
    mergeSort(a,left,mid);//归并左半个数组
    mergeSort(a,mid+1;right);//归并右半个数组
    merge(a,left,mid+1,right);//归并左半和右半数组
}


//归并排序
//复杂度O(nlog2n)，稳定的排序
template <class KEY, class OTHER>
void mergeSort(Set<KEY, OTHER> a[], int size)
{
    mergeSort(a,0,size-1);
}

#endif