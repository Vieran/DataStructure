/*红黑树的定义+实现文件*/

#include "DynamicSearch.h"
#include <iostream>
using namespace std;

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
template <class KEY, class OTHER>
class RedBlackTree : public DynamicSearchTable<KEY, OTHER>
{
private:
    enum colourT
    {
        RED,
        BLACK
    };
    struct RedBlackNode
    {
        Set<KEY, OTHER> data;
        RedBlackNode *left;
        RedBlackNode *right;
        colourT colour;

        RedBlackNode(const Set<KEY, OTHER> &element, RedBlackNode *lt = NULL, RedBlackNode *rt = NULL, colourT h = RED)
            : data(element), left(lt), right(rt), colour(h) {}
    };

    RedBlackNode *root;

    //工具函数
    void makeEmpty(RedBlackNode *&t);
    void insertAdjust(RedBlackNode *gp, RedBlackNode *p, RedBlackNode *t);            //插入后调整平衡的
    void removeAdjust(RedBlackNode *&p, RedBlackNode *&c, RedBlackNode *&t, KEY del); //维持删除后的平衡
    void LL(RedBlackNode *gp);
    void LR(RedBlackNode *gp);
    void RL(RedBlackNode *gp);
    void RR(RedBlackNode *gp);

public:
    RedBlackTree(RedBlackNode *t = NULL) { root = t; }
    ~RedBlackTree() { makeEmpty(root); }
    Set<KEY, OTHER> *find(const KEY &x) const;
    void insert(const Set<KEY, OTHER> &x);
    void remove(const KEY &x);
};

#endif

/*---------------------------------------------------------------函数的实现-------------------------------------------------------------------------*/

//查找函数
template <class KEY, class OTHER>
Set<KEY, OTHER> *RedBlackTree<KEY, OTHER>::find(const KEY &x) const
{
    RedBlackNode *t = root;
    while (t != NULL && t->data.key != x)
        if (t->data.key > x)
            t = t->left;
        else
            t = t->right;

    if (t == NULL)
        return NULL;
    else
        return (Set<KEY, OTHER> *)t;
}

//清空函数
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::makeEmpty(RedBlackNode *&t)
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = NULL;
}

//插入函数
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::insert(const Set<KEY, OTHER> &x)
{
    RedBlackNode *t, *parent, *grandP;

    if (root == NULL)
    {
        root = new RedBlackNode(x, NULL, NULL, BLACK);
        return;
    }

    parent = grandP = t = root;
    while (true)
    {
        if (t)
        {
            if (t->left && t->left->colour == RED && t->right->colour == RED)
            {
                t->left->colour = t->right->colour = BLACK;
                t->colour = RED;
                insertAdjust(grandP, parent, t);
            }
            grandP = parent;
            parent = t;
            t = (t->data.key > x.key ? t->left : t->right);
        }
        else
        {
            t = new RedBlackNode(x);
            if (x.key < parent->data.key)
                parent->left = t;
            else
                parent->right = t;

            insertAdjust(grandP, parent, t);
            root->colour = BLACK;
            return;
        }
    }
}

//插入后的调整函数
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::insertAdjust(RedBlackNode *gp, RedBlackNode *p, RedBlackNode *t)
{
    if (p->colour) //如果父节点是黑色（）值为1，无需调整，直接返回
        return;

    if (p == root)
    {
        p->colour = BLACK;
        return;
    }
    if (gp->left == p)
        if (p->left == t)
            LL(gp);
        else
            LR(gp);

    else if (p->right == t)
        RR(gp);
    else
        RL(gp);
}

//旋转函数的实现(,交换gp和p的值)
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LL(RedBlackNode *gp)
{
    RedBlackNode *p = gp->left, *t = p->left;
    RedBlackNode tmp = *gp;
    gp->data = p->data;
    gp->left = t;
    gp->right = p;
    p->data = tmp.data;
    p->left = p->right;
    p->right = tmp.right;
}

template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LR(RedBlackNode *gp)
{
    RedBlackNode *p = gp->left, *t = p->right;
    RedBlackNode tmp = *gp;
    gp->data = t->data;
    gp->right = t;
    p->right = t->left;
    t->data = tmp.data;
    t->left = t->right;
    t->right = tmp.right;
}

template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::RR(RedBlackNode *gp)
{
    RedBlackNode *p = gp->right, *t = p->right;
    RedBlackNode tmp = *gp;
    gp->data = p->data;
    gp->right = t;
    gp->left = p;
    p->data = tmp.data;
    p->left = p->left;
    p->right = tmp.left;
}

template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::RL(RedBlackNode *gp)
{
    RedBlackNode *p = gp->left, *t = p->right;
    RedBlackNode tmp = *gp;
    gp->data = t->data;
    gp->left = t;
    p->left = t->right;
    t->data = tmp.data;
    t->right = t->left;
    t->left = tmp.left;
}

//删除操作
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::remove(const KEY &x)
{
    KEY del = x;             //被删节点的关键字
    RedBlackNode *t, *p, *c; //c为当前节点，p为父节点，t为兄弟节点

    if (root == NULL)
        return;
    if (root->data.key == x && root->left == NULL && root->right == NULL)
    {
        delete root;
        root = NULL;
        return;
    }

    p = c = t = root;
    while (true)
    {
        removeAdjust(p, c, t, del);
        if (c->data.key == del && c->right && c->left)
        {
            RedBlackNode *tmp = c->right;
            while (tmp->left)
                tmp = tmp->left;
            c->data = tmp->data;
            del = tmp->data.key;
            p = c;
            c = c->right;
            t = p->left;
            continue;
        }

        if (c->data.key == del)
        {
            delete c;
            if (p->left == c)
                p->left = NULL;
            else
                p->right = NULL;
            root->colour = BLACK;
            return;
        }
        p = c;
        c = (del < p->data.key ? p->left : p->right);
        t = (c == p->left ? p->right : p->left);
    }
}

template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::removeAdjust(RedBlackNode *&p, RedBlackNode *&c, RedBlackNode *&t, KEY del)
{
    if (c->colour == RED)
        return;
    if (c == root)
        if (c->left && c->right && c->right->colour == c->left->colour)
        {
            c->colour = RED;
            c->left->colour = c->right->colour = BLACK;
            return;
        }

    if ((c->left && c->left->colour || c->left == NULL) && (c->right && c->right->colour || c->right == NULL))
        if ((t->left && t->left->colour || t->left == NULL) && (t->right && t->right->colour || t->right == NULL))
        {
            p->colour = BLACK;
            t->colour = c->colour = RED;
        }
        else
        {
            if (p->left == t)
                if (t->left && t->left->colour == RED)
                {
                    t->left->colour = BLACK;
                    LL(p);
                    p = t;
                }
                else
                {
                    LR(p);
                    p = p->right;
                    p->colour = BLACK;
                }
            else if (t->right && t->right->colour == RED)
            {
                t->right->colour = BLACK;
                RR(p);
                p = t;
            }
            else
            {
                RL(p);
                p = p->left;
                p->colour = BLACK;
            }
            c->colour = RED;
        }
    else
    {
        if (c->data.key == del)
        {
            if (c->right && c->left)
            {
                if (c->right->colour == BLACK)
                {
                    LL(c);
                    c = c->right;
                }
                return;
            }
            if (c->left)
            {
                LL(c);
                p = c;
                c = c->right;
            }
            else
            {
                RR(C);
                p = c;
                c = c->left;
            }
        }
        else
        {
            p = c;
            c = (del < p->data.key ? p->left : p->right);
            t = (c == p->left ? p->right : p->left);
            if (c->colour == BLACK)
            {
                if (t == p->right)
                    RR(p);
                else
                    LL(p);
                p = t;
                t = (c == p->left ? p->right : p->left);
                removeAdjust(p, c, t, del);
            }
        }
    }
}