#include <iostream>
#include <string>
using namespace std;

#ifndef SMALL_TRICK_H
#define SAMLL_TRICK_H
//表达式树的定义
class Calc
{
private:

    //表示:运算数,+,-,*,/,(,),行结束
    enum Type{DATA,ADD,SUB,MULTI,DIV,OPAREN,CPAREN,EOL};

    struct node//表达式树的节点类
    {
        Type type;//节点元素类型（数字/字符）
        int data;//节点元素的值
        node *lchild,*rchild;//指向左右子节点的指针
        node(Type t,int d=0,node *lc=NULL,node *rc=NULL)
        {
            type = t;
            data = d;
            lchild = lc;
            rchild = rc;
        }
    };

    node *root;//保存整棵树只要保存根节点

    //工具函数
    node *creat(char *&s);//从s创建一颗表达式树
    Type getToken(char *&s,int &value);//从s中获取一个语法单位
    int result(node *t);//计算以t为根的表达式树的结果
    
public:
    Calc(char *s)//构造一个cacl类对象
    {
        root = creat(s);
    }
    int result()//计算结果
    {
        if(root==NULL)
            return 0;
        return result(root);
    }
};



//哈夫曼树的定义和实现
template <class elemType>
class hfTree
{
private:
    struct node//数组中的元素类型
    {
        elemType data;//节点值
        int weight;//节点的权值
        int parent,left,right;//父节点及左右子节点的下标地址
    };

    node *elem;//数组的起始地址
    int length;//数组规模
    
public:
    struct hfCode//保存哈夫曼编码的类
    {
        elemType data;//待编码的字符
        string code;//对应的哈夫曼编码
    };

    hfTree(const elemType *x,const int *w,int size);//构造一棵哈夫曼树
    void getCode(hfCode result[]);//从哈夫曼树生成哈夫曼编码
    ~hfTree()
    {
        delete [] elem;
    }
};

//参数：待编码的符号，符号对应的权值，数组的规模(前两个数组的规模相同)
template <class elemType>
hfTree<elemType>::hfTree(const elemType *v,const int *w,int size)
{
    //置初值
    length = 2*size;
    elem = new node[length];//申请保存哈夫曼树的数组（下标为0的地方不存放任何东西）
    for (int i = size; i < length; ++i)//赋初值
    {
        elem[i].weight = w[i-size];//将符号和对应的权值放在数组的后半部分
        elem[i].data = v[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;//将父节点、左右子节点的下标都设置为0
    }

    //归并森林中的树
    const int MAX_INT = 32767;
    int min1,min2;//最小树、次最小树的权值
    int x,y;//最小树、次小树的下标
    for (int i = size-1; i > 0; --i)
    {
        min1 = min2 = MAX_INT;
        x = y = 0;
        for (int j = i+1; j < length; ++j)//逐个遍历，找出最小的树，并归并
            if(elem[j].parent==0)
                if (elem[j].weight<min1)//元素j最小
                {
                    min2 = min1;//改变次小值
                    min1 = elem[j].weight;//改变最小值
                    y = x;//改变次小树的下标
                    x = j;//改变最小树的下标
                }
                else
                    if (elem[j].weight<min2)//元素j次小
                    {
                        min2 = elem[j].weight;//改变次小值
                        y = j;//改变次小树的下标
                    }
                
        //进行归并
        elem[i].weight = min1+min2;
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}


//找出所有叶节点的哈夫曼编码，放在参数result中
template <class elemType>
void hfTree<elemType>::getCode(hfCode result[])
{
    int size = length/2;
    int p,s;//s是追溯过程中处理的节点，p是s的父节点下标

    //对每个待编码的符号向根追溯
    for (int i = size; i < length; ++i)
    {
        result[i-size].data = elem[i].data;
        result[i-size].code = "";
        p = elem[i].parent;
        s = i;
        while (p)
        {
            if(elem[p].left==s)//当前节点是父节点的左孩子，则编码字符串前添加0
                result[i-size].code = '0'+result[i-size].code;//string类的+操作表示字符串的拼接！
            else//当前节点是父节点的右孩子，则编码字符串前添加1
                result[i-size].code = '1'+result[i-size].code;
            s = p;
            p = elem[p].parent;
        }    
    }    
}


#endif