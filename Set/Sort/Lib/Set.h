//集合的声明文件+静态查找的实现文件
#ifndef SET_H
#define SET_H

#include <iostream>

template <class KEY,class OTHER>
struct Set
{
    KEY key;//关键字值
    OTHER other;//其他信息
};
#endif
