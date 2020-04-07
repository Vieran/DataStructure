/*动态查找表的抽象类*/

#ifndef DYNAMICSEARCH_H
#define DYNAMICSEARCH_H

//集合类的声明文件
template <class KEY,class OTHER>
struct Set
{
    KEY key;//关键字值
    OTHER other;//其他信息
};

//动态查找抽象类
template <class KEY,class OTHER>
class DynamicSearchTable
{
public:
    virtual Set<KEY,OTHER> * find(const KEY &x) const = 0;
    virtual void insert(const Set<KEY,OTHER> &x) = 0;
    virtual void remove(const KEY &x) = 0;
    virtual ~DynamicSearchTable() = 0;
};

#endif