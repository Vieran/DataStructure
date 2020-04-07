//栈的应用
#ifndef SMALL_TRICKS_H
#define SMALL_TRICKS_H

#include "seqStack.h"
#include <fstream>
#include <cstring>
using namespace std;

//判断是否为回文序列
bool isReverse(char *s);


/*递归消除（函数调用是通过栈实现的，如果可以控制）*/
void printInt_re(int num);//打印整数的递归函数
void printInt_nore(int num);//打印整数的非递归函数

/*括号配对*/
//balance类的声明
class Balance
{
    private:
        ifstream fin;//待检测的文件流(须注意，ifstream是在std命名空间里的)
        int currentLine;//正在处理的行号
        int Errors;//已发现的错误数

    struct Symbol//记录出错信息
    {
        char Token;//记录遇到的符号
        int TheLine;//记录出错的信息
    };
    
    enum CommentType{SlashSlash,SlashStar};//记录注释类型，双斜杠或者斜杠星

    //CheckBalance需要使用的工具函数
    bool CheckMatch(char Symb1,char Symb2,int Line1,int Line2);
    char GetNextSymbol();
    void PutBackChar(char ch);
    void SkipComment(enum CommentType type);
    void SkipQuote(char type);
    char NextChar();

    public:
        Balance(const char *s);//构造函数
        int CheckBalance();//检查fin中的括号是否匹配，返回错误个数
        void ReportError(int num);//总结错误个数，并输出
    
};

class noFile{};//当文件不存在时抛出此异常


/*简单的计算器*/
//calc类的声明
class Calc
{
    private:
    char *expression;//指向要计算的中缀表达式，避免了下标运算，同时使用了动态创建（指针的灵活性！）
    char *p;//使用此指针，便于回收空间

    //枚举类型，依次表示(,+,-.*,/,^,),数字,行结束符
    enum token{OPAREN,ADD,SUB,MULTI,DIV,EXP,CPAREN,VALUE,EOL};//此处是赋值的，可以代表优先级！

    //工具函数
    void BinaryOp(token op,seqStack<int> &dataStack);
    token getOp(int &value);

    public:
    Calc(char *s)
    {//构造函数
        expression = new char[strlen(s)+1];
        strcpy(expression,s);//此步骤导致析构函数出问题?(以s的结束为标志，可能导致expression溢出)
        expression[strlen(s)+1] = '\0';//提供检测表达式是否结束的标志
    }
    ~Calc()
    {//析构函数
        delete [] expression;//因为函数运行过程中expression会变化，会导致析构函数无法正常运行
    }
    int result();//计算表达式的结果
};


#endif