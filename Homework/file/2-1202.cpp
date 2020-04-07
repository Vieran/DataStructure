//2020.3.11---bigint
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1202
//输入两个正整数，输出两个正整数的和(要求使用链表)

#include <iostream>
#include <cstring>
using namespace std;

class bigint
{

private:
    struct numNode
    {
        int num;       //存储一个数字
        numNode *next; //存储指向下一个数字的指针

        numNode()
        {
            num = 0;
            next = NULL;
        }
    };
    numNode *number;
    int len;

public:
    //构造函数
    bigint(char n[], int length)
    {
        len = length;
        number = new numNode;
        numNode *p=new numNode;
        number->num = n[length-1]-'0';
        p = number;
        for (int i = length-1; i >= 0; --i) //倒序存储
        {
            p->next = new numNode;
            p->num = n[i] - '0';//存储数值
            p = p->next;
        }
    }

    //析构函数
    ~bigint()
    {
        numNode *p=number,*q;
        while (p!=NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }

    //加法函数
    void add(bigint &n1, bigint &n2)
    {
        bool flag;
        int longer, shorter;
        if (n1.len > n2.len) //找出两个数字之间较大和较小者
        {
            flag = true;
            longer = n1.len;
            shorter = n2.len;
        }
        else
        {
            flag = false;
            longer = n2.len;
            shorter = n1.len;
        }

        numNode *result = new numNode,*p;
        p = result;
        for (int i = 0; i <= longer; ++i)//为结果创建空间并初始化为0
        {
            p->next = new numNode;
            p = p->next;
        }

        //进行加法并将结果保存
        numNode *m1=n1.number,*m2=n2.number;//保存n1和n2的结点
        p = result;
        for (int i = 0; i < shorter; ++i)
        {
            p->num = p->num + m1->num + m2->num;//进行加法
            if (p->num >= 10)
            {
                p->num -= 10;
                p->next->num += 1;
            }

            //将p,m1和m2向前移动
            p = p->next;
            m1 = m1->next;
            m2 = m2->next;
        }

        //处理没有对齐的位数
        if (flag)
        {
            for (int i = shorter; i < longer; ++i)
            {
                p->num += m1->num;
                if (p->num >= 10)
                {
                    p->num -= 10;
                    p->next->num += 1;
                }
                
                //向后移动
                p = p->next;
                m1 = m1->next;
            }
        }
        else
            for (int i = shorter; i < longer; ++i)
            {
                p->num += m2->num;
                if (p->num >= 10)
                {
                    p->num -= 10;
                    p->next->num += 1;
                }

                //向后移动
                p = p->next;
                m2 = m2->next;
            }

        //输出
        int realnum[longer+1];  
        for (int i = longer; i >= 0 ; --i)
        {
            realnum[i] = result->num;
            p = result->next;
            delete result;//回收空间
            result = p;
        }
        
        int k;
        if(realnum[0]==0)//判断最高位是否为0
            k = 1;
        else
            k = 0;
        
        while (k<=longer)
        {
            cout << realnum[k];
            ++k;
        }
        
    }
};

int main()
{
    char n1[10], n2[10];//原题要求1000000，自己测试则不需要那么大
    cin.getline(n1, 10);
    cin.getline(n2, 10);
    int m1 = strlen(n1), m2 = strlen(n2);
    bigint num1(n1, m1), num2(n2, m2);
    num1.add(num1,num2);

    return 0;
}

//很奇怪的报错（XX*类型不能用于初始化XX*的实体）

//本次作业反映自己对链表的创建不熟悉，容易犯错（请思考：头节点和后面的结点怎么链接起来？）