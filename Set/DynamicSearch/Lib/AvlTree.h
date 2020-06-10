/*AVL树的定义+实现文件*/

#include "DynamicSearch.h"

#ifndef AVLTREE_H
#define AVLTREE_H
template <class KEY, class OTHER>
class AvlTree : public DynamicSearchTable<KEY, OTHER>
{
private:
    struct AvlNode
    {
        Set<KEY, OTHER> data;
        AvlNode *left;  //左子树
        AvlNode *right; //右子树
        int height;     //节点的高度

        AvlNode(const Set<KEY, OTHER> &element, AvlNode *lt, AvlNode *rl, int h = 1) : data(element), left(lt), right(rt), height(h) {}
    };

    AvlNode *root;
    enum subTree
    {
        LEFT,
        RIGHT
    }; //定义枚举类型的子树表示，便于理解

    //工具函数
    void insert(const Set<KEY, OTHER> &x, AvlNode *&t);
    bool remove(const KEY &x, AvlNode *&t);
    void makeEmpty(AvlNode *t);
    int height(AvlNode *t) const
    {
        return t == NULL ? 0 : t->height;
    }
    void LL(AvlNode *&t);
    void LR(AvlNode *&t);
    void RL(AvlNode *&t);
    void RR(AvlNode *&t);
    int max(int a, int b) { return (a > b) ? a : b; }
    bool adjust(AvlNode *&t, subTree tree);

public:
    AvlTree() { root = NULL; }      //构造函数
    ~AvlTree() { makeEmpty(root); } //析构函数
    Set<KEY, OTHER> *find(const KEY &x) const;
    void insert(const Set<KEY, OTHER> &x);
    void remove(const KEY &x);
};

#endif

/*函数的实现*/

//寻找键值为x的元素，找到则返回指向x的指针，否则返回空
template <class KEY, class OTHER>
Set<KEY, OTHER> *AvlTree<KEY, OTHER>::find(const KEY &x) const
{
    AvlNode *t = root;

    while (t != NULL && t->data.key != x) //寻找x
        if (t->data.key > x)
            t = t->left;
        else
            t = t->right;

    if (t == NULL)
        return NULL;
    else
        return (Set<KEY, OTHER> *)t; //这里进行了一个强制类型转换，但是由于t比Set大，所以强制转换成功
}

//所有的旋转，只需要记住一个原则：指针t是连接其后面所有节点和树的线，框架是指针t决定的（画图就明白了）
//LL旋转
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LL(AvlNode *&t)
{
    AvlNode *t1 = t->left;                                  //t1是危机节点的左子树
    t->left = t1->right;                                    //将左右改成危机节点的左
    t1->right = t;                                          //将危机节点改成t1的右
    t->height = max(height(t->left), height(t->right)) + 1; //修改节点的高度
    t1->height = max(height(t->left), height(t)) + 1;
    t = t1; //将危机节点的左改成危机节点
}

//RR旋转
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RR(AvlNode *&t)
{
    AvlNode *t1 = t->right; //t1是危机节点的右子树
    t->right = t1->left;    //将右左改成危机节点的右
    t1->left = t;           //将危机节点改成t1的左
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t->left), height(t)) + 1;
    t = t1; //将危机节点的右改成危机节点
}

//LR旋转
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::LR(AvlNode *&t)
{
    RR(T->left); //先把左当作危机节点处理，然后即可当作LL插入进行处理
    LL(t);
}

//RL旋转
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::RL(AvlNode *&t)
{
    LL(t->right); //先把右当作危机节点处理，然后即可当作RR插入进行处理
    RR(t);
}

//插入键值为x的元素
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const Set<KEY, OTHER> &x)
{
    insert(x, root);
}

//内嵌的insert工具函数
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::insert(const Set<KEY, OTHER> &x, AvlNode *&t)
{
    if (t == NULL) //在空树上插入
        t = new AvlNode(x, NULL, NULL);
    else if (x.key < t->data.key) //在左子树上插入
    {
        insert(x, t->left);                          //递归调用，直到满足条件（插入空树）就进行调整
        if (height(t->left) - height(t->right) == 2) //t是危机节点
            if (x.key < t->left->data.key)           //判断是左左还是左右
                LL(t);                               //插入了左左
            else
                LR(t); //插入了左右
    }
    else if (t->data.key < x.key)
    {
        insert(x, t->right);
        if (height(t->left) - height(t->right) == 2)
            if (x.key < t->left->data.key)
                RR(t);
            else
                RL(t);
    }

    //重新计算t的高度
    t->height = max(height(t->left), height(t->right)) + 1;
}

//删除键值为x的节点
template <class KEY, class OTHER>
void AvlTree<KEY, OTHER>::remove(const KEY &x)
{
    remove(x, root);
}

//内嵌的remove工具（删除节点+判断删后节点高度是否变化）
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::remove(const KEY &x, AvlNode *&t)
{
    if (t == NULL)
        return;
    if (x == t->data.key) //找到被删节点
    {
        if (t->left == NULL || t->right == NULL) //被删节点是叶子节点/只有一棵子树
        {
            AvlNode *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right; //安排好后续的左右子树
            delete oldNode;                             //删除节点，并且返回信息，高度变矮（只有一棵子树，删除节点后，子树向上，节点必然变矮）
            return false;
        }
        else //被删节点有两棵子树
        {
            AvlNode *tmp = t->right;
            while (tmp->left != NULL) //找到被删节点的右子树上最后一个左子树
                tmp = tmp->left;
            t->data = tmp->data; //将该节点放到被删节点
            if (remove(tmp->data.key, t->right))
                return true;         //被删后右子树没有变矮
            return adjust(t, RIGHT); //判断是否调整右子树
        }
    }

    if (x < t->data.key) //到左子树上找
    {
        if (remove(x, t->left)) //删后左子树没有变矮
            return true;
        return adjust(t, LEFT); //判断是否调整左子树
    }
    else
    {

        if (remove(x, t->right))
            return true;
        return adjust(t, RIGHT);
    }
}

//检查tree是否需要调整
template <class KEY, class OTHER>
bool AvlTree<KEY, OTHER>::adjust(AvlNode *&t, subTree tree)
{
    if (tree == RIGHT) //处理在右子树上删除，使得右子树变矮的情况
    {
        if (height(t->left) - height(t->right) == 1)
            return true;
        if (height(t->left) == height(t->right))
        {
            --t->height;
            return false;
        }
        if (height(t->left->right) > height(t->left->left))
        {
            LR(t);
            return false;
        }
        LL(t);
        if (height(t->left) == height(t->right))
            return false;
        else
            return true;
    }
    else //处理左子树上的删除
    {
        if (height(t->left) - height(t->right) == 1)
            return true;
        if (height(t->left) == height(t->right))
        {
            --t->height;
            return false;
        }
        if (height(t->right->left) > height(t->right->right))
        {
            RL(t);
            return false;
        }
        RR(t);
        if (height(t->left) == height(t->right))
            return false;
        else
            return true;
    }
}