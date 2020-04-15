#include <stack>
#include "linkQueue.h"

#ifndef BINARYTREE_H
#define BINARYTREE_H

//二叉树的抽象类声明
template <class elemType>
class BTree
{
public:
    virtual void clear() = 0;                                     //删除树中所有的节点
    virtual bool isEmpty() const = 0;                             //判断是否为空树
    virtual elemType Root(elemType flag) const = 0;               //找出树的根节点；如果树空则返回特殊值
    virtual elemType parent(elemType x, elemType flag) const = 0; //寻找x的父节点的值；如果树空则返回特殊值
    virtual elemType lchild(elemType x, elemType flag) const = 0; //寻找x的左子节点的值；如果树空则返回特殊值
    virtual elemType rchild(elemType x, elemType flag) const = 0; //寻找x的右子节点的值；如果树空则返回特殊值
    virtual void delLeft(elemType x) = 0;                         //删除x的左子节点
    virtual void delRight(elemType x) = 0;                        //删除x的右子节点
    virtual void preOrder() const = 0;                            //前序遍历
    virtual void midOrder() const = 0;                            //中序遍历
    virtual void postOrder() const = 0;                           //后序遍历
    virtual void levelOrder() const = 0;                          //层次遍历
};

//声明类，以便printTree可以使用
template <class elemType>
class BinaryTree;

//二叉树的输出函数(参数：要输出的树，空节点的特殊标记)
template <class elemType>
void printTree(const BinaryTree<elemType> &t, elemType flag)
{
    linkQueue<elemType> que;
    que.enQueue(t.root->data);
    cout << endl;

    while (!que.isEmpty())
    {
        char p, l, r;
        p = que.deQueue();
        l = t.lchild(p, flag);                     //获取左子节点
        r = t.rchild(p, flag);                     //获取右子节点
        cout << p << " " << l << " " << r << endl; //输出本节点、左子节点、右子节点

        //将子节点入队，方便输出它们的子节点
        if (l != flag)
            que.enQueue(l);
        if (r != flag)
            que.enQueue(r);
    }
}

//二叉链表类的声明和定义
template <class elemType>
class BinaryTree : public BTree<elemType>
{
    //声明一对一的友元，必须指明类型名，且在此类之前已经定义好此函数
    friend void printTree<elemType>(const BinaryTree &t, elemType flag);

private:
    struct node //二叉树的节点类
    {
        node *left, *right; //节点的左、右子节点的地址
        elemType data;      //节点的数据信息
        int TimesPop;       //为遍历的非递归形式准备，为进栈的次数

        node() : left(NULL), right(NULL) {}
        node(elemType item, node *L = NULL, node *R = NULL) : data(item), left(L), right(R), TimesPop(0) {}
        ~node() {}
    };

    node *root; //指向二叉树类的根节点

    node *find(elemType x, node *t) const; //找到存放x的节点

    //将实现过程与用户分隔开（用户不需要写传递的参数，但是这些是递归实现，必须传递参数，故使用包裹函数）
    void clear(node *&t);
    void preOrder(node *t) const;
    void midOrder(node *t) const;
    void postOrder(node *t) const;

public:
    BinaryTree() : root(NULL) {} //创建空一颗的二叉树
    BinaryTree(elemType x)       //创建一颗只有根节点的二叉树
    {
        root = new node(x);
    }

    ~BinaryTree()
    {
        clear(root);
    }

    void clear()
    {
        clear(root);
    }

    bool isEmpty() const //判断是否为空树
    {
        return root == NULL;
    }

    elemType Root(elemType flag) const;
    elemType lchild(elemType x, elemType flag) const;
    elemType rchild(elemType x, elemType falg) const;
    void delLeft(elemType x);
    void delRight(elemType x);
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    void creatTree(elemType flag); //创建一棵树
    elemType parent(elemType x, elemType flag) const
    {
        return flag;
    }

    //前中后序遍历的非递归实现
    void NpreOrder() const;
    void NmidOrder() const;
    void NpostOrder() const;
};

#endif

//返回根节点的值
template <class elemType>
elemType BinaryTree<elemType>::Root(elemType flag) const
{
    if (root == NULL)
        return flag;
    else
        return root->data;
}

//清除树的所有节点
template <class elemType>
void BinaryTree<elemType>::clear(BinaryTree<elemType>::node *&t)
{
    if (t == NULL)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = NULL;
}

//前序遍历
template <class elemType>
void BinaryTree<elemType>::preOrder(BinaryTree<elemType>::node *t) const
{
    if (t == NULL)
        return;
    cout << t->data << ' '; //输出本节点值
    preOrder(t->left);      //前序遍历左节点
    preOrder(t->right);     //前序遍历右节点
}

template <class elemType>
void BinaryTree<elemType>::preOrder() const
{
    cout << "\n前序遍历";
    preOrder(root);
}

//中序遍历
template <class elemType>
void BinaryTree<elemType>::midOrder(BinaryTree<elemType>::node *t) const
{
    if (t == NULL)
        return;
    midOrder(t->left);      //中序遍历左节点
    cout << t->data << ' '; //输出本节点的值
    midOrder(t->right);     //中序遍历右节点
}

template <class elemType>
void BinaryTree<elemType>::midOrder() const
{
    cout << "\n中序遍历";
    midOrder(root);
}

//后序遍历
template <class elemType>
void BinaryTree<elemType>::postOrder(BinaryTree<elemType>::node *t) const
{
    if (t == NULL)
        return;
    postOrder(t->left);     //后序遍历左节点
    postOrder(t->right);    //后序遍历右节点
    cout << t->data << ' '; //输出本节点的值
}

template <class elemType>
void BinaryTree<elemType>::postOrder() const
{
    cout << "\n后续遍历";
    postOrder(root);
}

//层次遍历
template <class elemType>
void BinaryTree<elemType>::levelOrder() const
{
    linkQueue<node *> que;
    node *tmp;

    cout << "\n层次遍历";
    que.enQueue(root); //这是什么操作？？？

    while (!que.isEmpty())
    {
        tmp = que.deQueue();
        cout << tmp->data << ' ';
        if (tmp->left)
            que.enQueue(tmp->left);
        if (tmp->right)
            que.enQueue(tmp->right);
    }
}

//寻找元素x存放的节点（在t的子孙节点中寻找）
template <class elemType> //需要加typename显式指定node是类型名
typename BinaryTree<elemType>::node *BinaryTree<elemType>::find(elemType x, BinaryTree<elemType>::node *t) const
{ //借鉴了前序遍历思想
    node *tmp;
    if (t == NULL)
        return NULL; //该指针为空，返回空
    if (t->data == x)
        return t;               //找到节点，直接返回
    if (tmp = find(x, t->left)) //递归调用find函数，寻找存放x的节点
        return tmp;             //如果左子节点非空，返回左子节点
    else
        return find(x, t->right); //左子节点为空，返回右子节点
}

//删除左子节点
template <class elemType>
void BinaryTree<elemType>::delLeft(elemType x)
{
    node *tmp = find(x, root);
    if (tmp == NULL)
        return;
    clear(tmp->left); //清除根节点的左子节点
}

//删除右子节点
template <class elemType>
void BinaryTree<elemType>::delRight(elemType x)
{
    node *tmp = find(x, root);
    if (tmp == NULL)
        return;
    clear(tmp->right);
}

//寻找x的左子节点
template <class elemType>
elemType BinaryTree<elemType>::lchild(elemType x, elemType flag) const
{
    node *tmp = find(x, root); //找到x所在的节点
    if (tmp == NULL || tmp->left == NULL)
        return flag; //如果节点为空，返回特殊值

    return tmp->left->data; //不为空则返回左子节点的值
}

//寻找x的右子节点
template <class elemType>
elemType BinaryTree<elemType>::rchild(elemType x, elemType flag) const
{
    node *tmp = find(x, root);
    if (tmp == NULL || tmp->right == NULL)
        return flag; //如果节点或子节点为空，返回特殊值

    return tmp->right->data; //不为空则返回右子节点的值
}

//创建树（根据父子节点的关系输入树上的每一个节点的子节点）,其中参数flag为设定的表示空节点特殊标志
template <class elemType>
void BinaryTree<elemType>::creatTree(elemType flag)
{
    linkQueue<node *> que;
    node *tmp;
    elemType x, ldata, rdata; //本节点值、左子节点值、右子节点值

    //创建树，输入flag表示空
    cout << "\n输入根节点:";
    cin >> x;
    root = new node(x);
    que.enQueue(root); //存储根节点

    //对已添加到树上的节点，一次输入其左右子节点的值
    while (!que.isEmpty())
    {
        tmp = que.deQueue(); //将队列中的节点一次出队（队列中是还没有输入子节点的节点）
        cout << "\n输入" << tmp->data << "的左右子节点(" << flag << "表示空节点):";
        cin >> ldata >> rdata;
        if (ldata != flag)
            que.enQueue(tmp->left = new node(ldata)); //生成子节点，并将节点存入未输入子节点的队列中
        if (rdata != flag)
            que.enQueue(tmp->right = new node(rdata)); //生成子节点，并将节点存入未输入子节点的队列中
    }
    cout << "Creat completed.\n";
}

//前序遍历非递归实现
template <class elemType>
void BinaryTree<elemType>::NpreOrder() const
{
    stack<node *> s;
    node *current;

    cout << "\n前序遍历的非递归实现：";
    s.push(root);
    while (!s.empty())
    {
        current = s.pop();
        cout << current->data;
        //将右左节点先后放入栈（此顺序考虑了栈的特性）
        if (current->right != NULL)
            s.push(current->right);
        if (current->left != NULL)
            s.push(current->ledft);
    }
}

//中序遍历非递归实现
template <class elemType>
void BinaryTree<elemType>::NmidOrder() const
{
    stack<node *> s;
    s.push(root);
    node *current;
    cout << "\n中序遍历的非递归实现：";

    while (!s.empty())
    {
        current = s.pop();
        if (++current->TimesPop == 2) //这里++和判断合为一个式子了
        {
            cout << current->data;
            if (current->right != NULL) //将右子树放入栈（左子树已经处理过了）
                s.push(current->right);
        }
        else
        {
            s.push(current);           //将其放回栈中
            if (current->left != NULL) //将左子树放入栈顶，以便后续处理
                s.push(current->left);
        }
    }
}

//后续遍历非递归实现
template <class elemType>
void BinaryTree<elemType>::NpostOrder() const
{
    stack<node *> s;
    s.push(root);
    cout << "\n后续遍历的非递归实现：";
    while (!s.empty())
    {
        current = s.pop();
        if (++current->TimesPop == 3)
        {
            cout << current->data;
            continue;
        }
        s.push(current); //将当前从新放回栈
        if (current->TimesPop == 1)
        {
            if (current->left != NULL)
                s.push(current->left);
        }
        else if (current->right != NULL)
            s.push(current->right);
    }
}