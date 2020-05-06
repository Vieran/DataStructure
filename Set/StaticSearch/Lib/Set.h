//集合的声明文件+静态查找的实现文件
#ifndef SET_H
#define SET_H

#include <iostream>
using namespace std;

template <class KEY,class OTHER>
struct Set
{
    KEY key;//关键字值
    OTHER other;//其他信息
};
#endif

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/*无/有序表的顺序查找*/
template <class KEY,class OTHER>
int seqSearch(Set<KEY,OTHER> data [],int size,const KEY &x)
{
    data[0].key = x;//将需要查找的值存放在数组开头
    
    int i;
    for(i=size;x!=data[i].key;--i);//从最大开始找，避免每次都要检查下标是否越界
    return i;//找到则返回下标，没有则返回0（元素存在0位置）
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/*二分查找(升序排列表)*/
template <class KEY,class OTHER>
int binarySearch(Set<KEY,OTHER> data [],int size,const KEY &x)
{
    int low = 1,high = size ,mid;

    while (low <= high)//查找所在的区间
    {
        mid = (low+high)/2;//计算中间位置
        if(x==data[mid].key)
            return mid;
        else
            if(x<data[mid].key)
                high = mid-1;
            else
                low = mid+1;   
    }  
    return 0; 
}

