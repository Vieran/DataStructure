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
        Set<KEY, OTHER> data; //保存节点数据
        RedBlackNode *left;   //左子树
        RedBlackNode *right;  //右子树
        colourT colour;       //节点颜色

        RedBlackNode(const Set<KEY, OTHER> &element, RedBlackNode *lt = NULL, RedBlackNode *rt = NULL, colourT h = RED)
            : data(element), left(lt), right(rt), colour(h) {} //默认插入红色节点
    };

    RedBlackNode *root;

    //工具函数
    void makeEmpty(RedBlackNode *&t);                                                 //清空
    void insertAdjust(RedBlackNode *gp, RedBlackNode *p, RedBlackNode *t);            //插入后调整平衡的
    void removeAdjust(RedBlackNode *&p, RedBlackNode *&c, RedBlackNode *&t, KEY del); //维持删除后的平衡
    void LL(RedBlackNode *gp);                                                        //左旋
    void LR(RedBlackNode *gp);                                                        //双旋
    void RL(RedBlackNode *gp);                                                        //双旋
    void RR(RedBlackNode *gp);                                                        //右旋

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
    while (t != NULL && t->data.key != x) //寻找对应值的节点
        if (t->data.key > x)
            t = t->left;
        else
            t = t->right;

    if (t == NULL)
        return NULL;
    else
        return (Set<KEY, OTHER> *)t; //找到了就将其转化为Set数据类型（大变小）返回
}

//清空函数
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::makeEmpty(RedBlackNode *&t)
{
    if (t != NULL) //递归调用
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
    RedBlackNode *t, *parent, *grandP; //

    if (root == NULL)
    {
        root = new RedBlackNode(x, NULL, NULL, BLACK); //根节点是黑色
        return;
    }

    parent = grandP = t = root;
    while (true) //寻找合适的插入点
    {
        if (t) //t非空
        {
            if (t->left && t->left->colour == RED && t->right && t->right->colour == RED) //边寻找边调整（左右子树都是红色）
            {
                t->left->colour = t->right->colour = BLACK; //将左右子树都染成黑色
                t->colour = RED;                            //将自身染成红色
                insertAdjust(grandP, parent, t);            //向上调整
            }
            grandP = parent;
            parent = t;
            t = (t->data.key > x.key ? t->left : t->right); //选择性地向下寻找
        }
        else
        {
            t = new RedBlackNode(x);      //找到插入点
            if (x.key < parent->data.key) //和父节点衔接
                parent->left = t;
            else
                parent->right = t;

            insertAdjust(grandP, parent, t); //调整
            //root->colour = BLACK;//这句应该不必要吧，本函数和调整函数都有相关的设置根节点为黑色的语句
            return;
        }
    }
}

//插入后的调整函数
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::insertAdjust(RedBlackNode *gp, RedBlackNode *p, RedBlackNode *t)
{
    if (p->colour) //如果父节点是黑色，值为1，无需调整，直接返回
        return;

    if (p == root) //p是根节点
    {
        p->colour = BLACK; //将根节点染成黑色（调用本函数的函数可能将根节点染成了红色）
        return;
    }
    if (gp->left == p)
        if (p->left == t)
            LL(gp); //祖父节点的外侧
        else
            LR(gp); //祖父节点的内侧

    else if (p->right == t)
        RR(gp); //祖父节点的外侧
    else
        RL(gp); //祖父节点的内侧
}

//左旋（交换gp和p）
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LL(RedBlackNode *gp)
{
    RedBlackNode *p = gp->left, *t = p->left;
    RedBlackNode tmp = *gp;
    gp->data = p->data; //将gp的数据改为p的
    gp->left = t;
    p->data = tmp.data;   //将p的数据改为原来gp的
    gp->right = p;        //这里是将p挂到gp右子树
    p->left = p->right;   //这里p是gp的值，所以p的右子树比p小，应该挂到左子树上
    p->right = tmp.right; //将原来gp的右子树挂上
}

//双旋（交换gp和t）
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::LR(RedBlackNode *gp)
{
    RedBlackNode *p = gp->left, *t = p->right;
    RedBlackNode tmp = *gp;
    gp->data = t->data;   //将gp的数据改为p的
    t->data = tmp.data;   //t的数据改成原来gp的
    gp->right = t;        //将gp的右子树改为t
    p->right = t->left;   //p的右子树挂t的左子树
    t->left = t->right;   //t（此时的值已经是原来gp的）的左子树挂t的右子树
    t->right = tmp.right; //将原来的gp的右子树挂上
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

/*前面的LL和LR函数我修改了一个语句顺序，但是这两个没有修改，因为道理一样，不作更多注释*/
/*这些旋转函数和AVL的大相径庭，可以对比学习，由传参就可以看出区别*/

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
    if (root == NULL) //树空
        return;
    if (root->data.key == x && root->left == NULL && root->right == NULL) //数仅树根，且需要删除树根
    {
        delete root;
        root = NULL;
        return;
    }

    RedBlackNode *t, *p, *c; //p为父节点，t为兄弟节点，c为当前节点
    p = c = t = root;        //从根节点开始找
    KEY del = x;             //被删节点的关键字
    while (true)
    {
        removeAdjust(p, c, t, del);                    //将当前节点调整为红色（为了在找到被删节点的时候，可以直接删除）
        if (c->data.key == del && c->right && c->left) //被删节点具有两棵子树
        {
            RedBlackNode *tmp = c->right;
            while (tmp->left) //寻找替代节点（右子树中最小值）
                tmp = tmp->left;
            c->data = tmp->data; //将被删节点的值改为替代节点的
            del = tmp->data.key; //将被删节点移动到替代节点处

            //接下来四个语句都是用于将层次往下推一层，然后通过下面的if语句实现删除
            p = c;
            c = c->right;
            t = p->left;
            continue;
        }

        if (c->data.key == del) //被删节点是叶子节点/只有一棵子树的节点，直接删除
        {
            delete c;
            if (p->left == c) //处理父节点
                p->left = NULL;
            else
                p->right = NULL;
            root->colour = BLACK; //前面可能调整了根节点，这里需要把根节点恢复为红色
            return;
        }

        //没有找到被删节点，下降一层继续找
        p = c;
        c = (del < p->data.key ? p->left : p->right);
        t = (c == p->left ? p->right : p->left);
    }
}

//将c调整为红色节点
template <class KEY, class OTHER>
void RedBlackTree<KEY, OTHER>::removeAdjust(RedBlackNode *&p, RedBlackNode *&c, RedBlackNode *&t, KEY del)
{
    if (c->colour == RED)
        return;
    if (c == root) //即使是根节点，也照样调整为红色（在调用这个函数的remove函数里，最后恢复了根节点）
        if (c->left && c->right && c->right->colour == c->left->colour)
        {
            c->colour = RED;
            c->left->colour = c->right->colour = BLACK;
            return;
        }

    if ((c->left && c->left->colour || c->left == NULL) && (c->right && c->right->colour || c->right == NULL)) //c的子树是空或者黑色节点
        if ((t->left && t->left->colour || t->left == NULL) && (t->right && t->right->colour || t->right == NULL))
        {                                //c的兄弟节点的子树都是空或者黑色
            p->colour = BLACK;           //将c的父节点改为红色
            t->colour = c->colour = RED; //c和兄弟节点改为红色
        }
        else //c的兄弟节点的存在红色子树
        {
            if (p->left == t)                          //c的兄弟节点是左子树
                if (t->left && t->left->colour == RED) //c的兄弟节点的左子树是红色
                {
                    t->left->colour = BLACK; //c的兄弟节点的左子树改成黑色
                    LL(p);                   //对p进行双旋转
                    p = t;
                }
                else
                {
                    LR(p);
                    p = p->right;
                    p->colour = BLACK;
                }
            else if (t->right && t->right->colour == RED) //c的兄弟节点是右子树
            {
                t->right->colour = BLACK;
                RR(p);
                p = t; //调整过后，需要将p指向t
            }
            else
            {
                RL(p);
                p = p->left;
                p->colour = BLACK;
            }

            c->colour = RED; //将c调整为红色
        }
    else //c存在红色子树
    {
        if (c->data.key == del)//c是被删节点
        {
            if (c->right && c->left)//c有两棵子树
            {
                if (c->right->colour == BLACK)//右子树是黑色（则左子树是红色）
                {
                    LL(c);//左旋后下降一层
                    c = c->right;
                }
                return;
            }
            if (c->left)//c只有左子树（红色）
            {
                LL(c);//左旋后下降一层
                p = c;
                c = c->right;
            }
            else//c只有右子树（红色）
            {
                RR(C);//右旋后下降一层
                p = c;
                c = c->left;
            }
        }
        else//c不是被删节点，向下一层寻找
        {
            p = c;
            c = (del < p->data.key ? p->left : p->right);
            t = (c == p->left ? p->right : p->left);
            if (c->colour == BLACK)//下一层的节点是黑色，得继续调整
            {
                if (t == p->right)
                    RR(p);
                else
                    LL(p);
                p = t;
                t = (c == p->left ? p->right : p->left);
                removeAdjust(p, c, t, del);//递归调用
            }
        }
    }
}