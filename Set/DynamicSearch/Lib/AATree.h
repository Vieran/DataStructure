/*AA树的定义+实现*/

#include "DynamicSearch.h"
#include <iostream>
using namespace std;

#ifndef AATREE_H
#define AATREE_H

template <class KEY, class OTHER>
class AATree : public dynamicSearchTable<KEY, OTHER>
{
private:
    struct AANode
    {
        Set<KEY, OTHER> data; //数据
        AANode *left;         //左子树
        AANode *right;        //右子树
        int level;            //保存节点的层次

        AANode(const Set<KEY, OTHER> &thedata, AANode *lt, AANode *rt, int lv = 1) : data(thedata), left(lt), right(rt), level(lv) {}
    };
    AANode *root;

    void insert(const Set<KEY, OTHER> &x, AANode *&t);
    void remove(const KEY &x, AANode *&t);
    void makeEmpty(AANode *t);
    void LL(AANode *&t);
    void RR(AANode *&t);
    int min(int a, int b)
    {
        return a < b ? a : b;
    }

public:
    AATree()
    {
        root = NULL;
    }
    ~AATree()
    {
        makeEmpty(root);
    }
    Set<KEY, OTHER> *find(const KEY &x) const;
    void insert(const Set<KEY, OTHER> &x)
    {
        insert(x, root);
    }
    void remove(const KEY &x)
    {
        remove(x, root);
    }
};

#endif

template <class KEY, class OTHER>
Set<KEY, OTHER> *AATree<KEY, OTHER>::find(const KEY &x) const
{
    AANode *t = root;
    while (t != NULL && t->data.key != x)
        if (t->data.key > x)
            t = t->left;
        else
            t = t->right;

    if (t == NULL)
        return NULL;
    else
        return (Set<KEY, OTHER> *)t; //强制类型转换成对应的数据类型
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::makeEmpty(AANode *t)
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::insert(const Set<KEY, OTHER> &x, AANode *&t)
{
    if (t == NULL)
        t = new AANode(x, NULL, NULL); //默认插入红色节点，也即节点层次为1
    else if (x.key < t->data.key)
        insert(x, t->left);
    else if (t->data.key < x.key)
        insert(x, t->right);
    else
        return;

    LL(t);
    RR(t);
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::LL(AANode *&t)
{
    if (t->left != NULL && t->left->level == t->lecel)
    {
        AANode *t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t = t1;
    }
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::RR(AANode *&t)
{
    if (t->right != NULL && t->right->right != NULL && t->right->level == t->lecel)
    {
        AANode *t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t = t1;
        t->level++;
    }
}

template <class KEY, class OTHER>
void AATree<KEY, OTHER>::remove(const KEY &x, AANode *&t)
{
    if (t == NULL)
        return;
    if (x < t->data.key)
        remove(x, t->left);
    else if (t->data.key < x)
        remove(x, t->right);
    else if (t->left != NULL && t->right != NULL)
    {
        AANode *tmp = t->right;
        while (tmp->left != NULL)
            tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data.key, t->right);
    }
    else
    {
        AANode *oldNode = t;
        t = (t->left != NULL) > t->left : t->right;
        delete oldNode;
        return;
    }

    if (t->left == NULL || t->right == NULL)
        t->level = 1;
    else
        t->level = min(t->left->level, t->right->level) + 1;
    if (t->right != NULL && t->right->level > t->level)
        t->right->level = t->level;
    LL(t);
    if (t->right != NULL)
        LL(t->right);
    if (t->right != NULL && t->right->right != NULL)
        LL(t->right->right);
    RR(t);
    if (t->right != NULL)
        RR(t->right);
}