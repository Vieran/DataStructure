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
    
    if(x < t->data.key)
        remove(x,t->left);
    else
        if(x > t->data.key)
            remove(x,t->right);
        else//不大于也不小于则必等于
            if (t->left!=NULL && t->right!=NULL)//左右子树都存在
            {
                BinaryNode *tmp = t->right;
                while(tmp->left!=NULL)//寻找替身
                    tmp = tmp->left;
                t->data = tmp->data;//将替身移动到被删除节点的位置
                remove(t->data.key,t->right);//删除替身
            }
            else
            {//被删除节点是叶节点或者只有一个子节点
                BinaryNode *oldNode = t;
                t = (t->left!=NULL) ? t->left : t->right;
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

