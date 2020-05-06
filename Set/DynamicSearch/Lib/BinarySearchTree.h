/*二叉查找树的声明+定义文件*/

#include "DynamicSearch.h"
#include <iostream>
using namespace std;

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

template <class KEY,class OTHER>
class BinarySearchTree:public DynamicSearchTable<KEY,OTHER>
{
private:
    struct BinaryNode
    {
        Set<KEY,OTHER> data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Set<KEY,OTHER> &thedata,BinaryNode *lt=NULL,BinaryNode *rt=NULL):data(thedata),left(lt),right(rt){}
    };

    BinaryNode *root;

    //工具函数
    void insert(const Set<KEY,OTHER> &x,BinaryNode *&t);
    void remove(const KEY &x,BinaryNode *&t);
    Set<KEY,OTHER> * find(const KEY &x,BinaryNode *t) const;
    void makeEmpty(BinaryNode *t);
    
public:
    BinarySearchTree();
    ~BinarySearchTree();
    Set<KEY,OTHER> * find(const KEY &x) const;
    void insert(const Set<KEY,OTHER> &x);
    void remove(const KEY &x);
};

#endif
/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
//find函数的实现
template <class KEY,class OTHER>
Set<KEY,OTHER> *BinarySearchTree<KEY,OTHER>::find(const KEY &x) const
{
    return find(x,root);
}

template <class KEY,class OTHER>
Set<KEY,OTHER> *BinarySearchTree<KEY,OTHER>::find(const KEY &x,BinaryNode *t) const
{
    if(t==NULL || t->data.key==x)//找到/不存在
        return (Set<KEY,OTHER> *) t;
    if(x<t->data.key)
        return find(x,t->left);//继续查找左子树
    else
        return find(x,t->right);//继续查找右子树
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
//insert函数的实现
template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::insert(const Set<KEY,OTHER> &x)
{
    insert(x,root);
}

//插入的一定是叶子节点
template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::insert(const Set<KEY,OTHER> &x,BinaryNode *&t)
{
    if(t==NULL)
        t = new BinaryNode(x,NULL,NULL);
    else
        if(x.key<t->data.key)
            insert(x,t->left);
        else
            insert(x,t->right);

}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
//remove函数的实现
template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::remove(const KEY &x)
{
    remove(x,root);
}

template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::remove(const KEY &x,BinaryNode *&t)
{
    if(t==NULL)
        return;
    
    if(x < t->data.key)//继续查找
        remove(x,t->left);
    else
        if(x > t->data.key)//继续查找
            remove(x,t->right);
        else//不大于也不小于则必等于，找到了
            if (t->left!=NULL && t->right!=NULL)//左右子树都存在
            {
                BinaryNode *tmp = t->right;
                while(tmp->left!=NULL)//寻找替身（右子树中最小的一个）
                    tmp = tmp->left;//小的只能是在左子树上
                t->data = tmp->data;//将替身移动到被删除节点的位置
                remove(t->data.key,t->right);//删除替身（此替身最多只有一棵子树）
                //此处为什么不直接传递tmp去删除呢？删除必须要有父节点在，否则会出现野指针，但是寻找tmp的过程中并没有保存它的父节点
            }
            else
            {//被删除节点是叶节点或者只有一个子节点
                BinaryNode *oldNode = t;
                t = (t->left!=NULL) ? t->left : t->right;//直接把子树/NULL挂到父节点上（替代被删节点）
                delete oldNode;
            }            
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/
//构造函数的实现
template <class KEY,class OTHER>
BinarySearchTree<KEY,OTHER>::BinarySearchTree()
{
    root = NULL;
}

//析构函数的实现
template <class KEY,class OTHER>
BinarySearchTree<KEY,OTHER>::~BinarySearchTree()
{
    makeEmpty(root);
}

//清空函数的实现
template <class KEY,class OTHER>
void BinarySearchTree<KEY,OTHER>::makeEmpty(BinaryNode *t)
{
    if(t==NULL)
        return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

