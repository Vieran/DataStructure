//2020.3.11---link
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1203
//将两个线性表合并成为一个线性表

#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class colink
{

    //friend colink<T> operator+(colink<T> data1, colink<T> data2);

private:
    struct dataNode
    {
        T data;
        dataNode *next;

        //构造结点
        dataNode(T x, dataNode *p = NULL) : data(x), next(p) {}
    };
    dataNode *head; //头节点

public:
    //构造函数
    colink(T *num = NULL, int lenth = 0)
    {
        head = new dataNode(0);
        dataNode *p = head;
        for (int i = 0; i < lenth; i++)
        {
            p->next = new dataNode(num[i]);
            p = p->next;
        }
    }

    //析构函数
    ~colink()
    {
        dataNode *p, *q;
        p = head->next;
        while (p != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
        delete head;
    }

    //赋值重载
    colink &operator=(const colink<T> &other)
    {
        if (this == &other)
            return *this;

        dataNode *p = head, *q = other.head->next;
        while (q != NULL)
        {
            p->next = new dataNode(q->data);
            p = p->next;

            other.head->next = q->next;
            delete q;
            q = other.head->next;
        }
        return *this;
    }

    //输出函数
    void print()
    {
        dataNode *p = this->head->next;
        while (p != NULL)
        {
            cout << p->data << ' ';
            p = p->next;
        }
    }

    //加法运算符重载
    colink<T> operator+(const colink<T> &data1)
    {
        colink<T> data2;

        dataNode *p = this->head->next, *q = data1.head->next, *result = data2.head;

        //进行链表拼接
        while (p != NULL)
        {
            result->next = new dataNode(p->data);
            result = result->next;
            p = p->next;
        }
        while (q != NULL)
        {
            result->next = new dataNode(q->data);
            result = result->next;
            q = q->next;
        }

        return data2;
    }
};

/*template <class T>
colink<T> operator+(colink<T> &data1, colink<T> &data2)
{
    colink<T> data3;

    typename colink<T>::dataNode *p = data1.head, *q = data2.head, *result = data3.head;

    //进行链表拼接
    while (p != NULL)
    {
        result->next = new dataNode(p->data);
        result = result->next;
        p = p->next;
    }
    while (q != NULL)
    {
        result->next = new dataNode(q->data);
        result = result->next;
        q = q->next;
    }

    return data3;
}*/

int main()
{
    /*判断链表类型*/
    enum TYPE
    {
        INT,
        CHAR,
        DOUBLE
    };
    TYPE type;
    char gettype[8];
    cin.getline(gettype, 8);
    if (strcmp(gettype, "int") == 0)
        type = INT;
    if (strcmp(gettype, "char") == 0)
        type = CHAR;
    if (strcmp(gettype, "double") == 0)
        type = DOUBLE;

    /*链表的创建+合并*/

    //获取链表长度
    int n, m;
    cin >> n >> m;

    //实例化模板并创建链表
    switch (type)
    {
    case INT:
    {
        //输入数组
        int *num1 = new int[n], *num2 = new int[m], i = 0, k = 0;
        while (i < n)
        {
            cin >> num1[i];
            ++i;
        }
        while (k < m)
        {
            cin >> num2[k];
            ++k;
        }

        //构建对象
        colink<int> data1(num1, n), data2(num2, m), data3;
        data3 = data1 + data2;

        //合并和输出链表
        data3.print();

        //回收数组空间
        delete[] num1;
        delete[] num2;
        break;
    }
    case CHAR:
    {
        //输入数组
        char *num1 = new char[n + 1], *num2 = new char[m + 1];
        int i = 0,k = 0;
        char blank;
        while (i<n)
        {
            cin >> blank;
            num1[i] = blank;
            ++i;
        }
        num1[n] = '\0';
        while (k<m)
        {
            cin >> blank;
            num2[k] = blank;
            ++k;
        }
        num2[m] = '\0';

        //构建对象
        colink<char> data1(num1, n), data2(num2, m), data3;
        data3 = data1 + data2;

        //合并和输出链表
        data3.print();

        //回收数组空间
        delete[] num1;
        delete[] num2;
        break;
    }
    case DOUBLE:
    {
        //输入数组
        double *num1 = new double[n], *num2 = new double[m];
        int i = 0, k = 0;
        while (i < n)
        {
            cin >> num1[i];
            ++i;
        }
        while (k < m)
        {
            cin >> num2[k];
            ++k;
        }

        //构建对象
        colink<double> data1(num1, n), data2(num2, m), data3;
        data3 = data1 + data2;

        //合并和输出链表
        data3.print();

        //回收数组空间
        delete[] num1;
        delete[] num2;
        break;
    }
    }
    return 0;
}

//控制传输跳过的实例化：case语句创建类模板的实例，需要用大括号将case语句括起来
//存在问题：无法实现类模板内定义的私有结构体在类模板的友元函数中使用？
//cin即使是对于char类型也不会记录入空格，所以当不需要空格的时候可以使用char逐个输入再赋值给char数组
//strcmp相同时返回值为0，在判断语句中是“非”