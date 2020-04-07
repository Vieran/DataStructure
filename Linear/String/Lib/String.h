/*String相关的类的声明文件*/
//实现文件有空再写
#ifndef STRING_H
#define STRING_H

#include <iostream>
using namespace std;


//顺序串类
class seqString
{
    friend seqString operator+(const seqString &s1,const seqString &s2);//运算符+重载
    friend bool operator==(const seqString &s1,const seqString &s2);//运算符==重载
    friend bool operator!=(const seqString &s1,const seqString &s2);//运算符!=重载
    friend bool operator>(const seqString &s1,const seqString &s2);//运算符>重载
    friend bool operator>=(const seqString &s1,const seqString &s2);//运算符>=重载
    friend bool operator<(const seqString &s1,const seqString &s2);//运算符<重载
    friend bool operator<=(const seqString &s1,const seqString &s2);//运算符<=重载
    friend ostream &operator<<(ostream &os,const seqString &s);//输出运算符重载

private:
    char *data;
    int len;
public:
    seqString(const char *s="");//构造函数
    seqString(const seqString &other);//拷贝构造函数
    ~seqString();//析构函数
    int length() const;//返回字符串的长度
    seqString &operator=(const seqString &other);//赋值运算符重载
    seqString subStr(int start,int num) const;//从start开始，取出长度为num的字符串
    void insert(int start,const seqString &s);//在start出插入字符串s
    void remove(int start,int num);//从start处移除长度为num的字符串
    int find(const seqString &sub) const;
};


//链接串类
class linkString
{
    friend seqString operator+(const linkString &s1,const linkString &s2);//运算符+重载
    friend bool operator==(const linkString &s1,const linkString &s2);//运算符==重载
    friend bool operator!=(const linkString &s1,const linkString &s2);//运算符!=重载
    friend bool operator>(const linkString &s1,const linkString &s2);//运算符>重载
    friend bool operator>=(const linkString &s1,const linkString &s2);//运算符>=重载
    friend bool operator<(const linkString &s1,const linkString &s2);//运算符<重载
    friend bool operator<=(const linkString &s1,const linkString &s2);//运算符<=重载
    friend ostream &operator<<(ostream &os,const linkString &s);//输出运算符重载
private:
    struct node
    {
        int size;//每个节点中的有效字符数
        char *data;//保存字符串的字符数组
        node *next;//指向下一个节点

        node(int s=1,node *n=NULL){
            data = new char[s];
            size = 0;
            next = n;
        }
    };

    node *head ;//设置头节点
    int len;//字符串的总长度（根据此设置size=√len）
    int nodeSize;//每个节点的容量

    void clear();//释放存储字符串的块状链表的所有空间
    void findPos(int start,int &pos,node *&p) const ;//寻找第start个字符所在的节点地址p，以及在节点p中的位置pos
    void split(node *p,int pos);//将指针p指向的节点以位置pos为界分裂成两个节点
    void merge(node *p);//检查p指向的节点是否能与它的直接后继合并成一个节点（可以则合并）
    
public:
    linkString(const char *s="");//构造函数
    linkString(const linkString &other);//拷贝构造函数
    ~linkString();//析构函数
    int length() const;//返回字符串的长度
    seqString &operator=(const linkString &other);//赋值运算符重载
    seqString subStr(int start,int num) const;//从start开始，取出长度为num的字符串
    void insert(int start,const linkString &s);//在start出插入字符串s
    void remove(int start,int num);//从start处移除长度为num的字符串
};


#endif