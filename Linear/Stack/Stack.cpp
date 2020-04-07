#include "linkStack.h"
#include "Small_Trick.h"

int main(int argc,char **argv)
{
    //判断输入的字符串是否为回文序列
    cout << "Please input the string:";
    char str[10];
    cin >> str;
    if(isReverse(str))
        cout << "It is a reverse!" << endl;
    else
        cout << "It isn't a reverse!" << endl;

    //检查源文件中的括号是否配对
    char filename[15];
    Balance *p;//创建一个指向balance类的指针，方便后面动态创建和回收空间
    int result;

    try
    {
        if (argc==1)//没有通过main函数传入文件名
        {
            cout << "Please input the file name:";
            cin >> filename;//输入文件名
            p = new Balance(filename);//构建文件对象
            result = p->CheckBalance();
            p->ReportError(result);//报告错误

            delete p;//回收空间
            return 0;
        }

        while(--argc)//通过main函数传入了文件名，依次检查传入的文件
        {
            cout << "Checking file " << *argv << endl;
            p = new Balance(*argv);
            result = p->CheckBalance();
            p->ReportError(result);//报告错误
            
            delete p;
        }
    }
    catch(noFile)
    {
        cerr << "No such file" << '\n';
    }

    //简单的计算器
    cout << "Please input the exprssion:";
    char exp[30];
    //cin >> exp;以这种方法输入的字符串，不会包含空格（遇到空格就停止输入了）
    cin.get();//将之前的回车清理
    cin.getline(exp,30);//自动补充了\0

    Calc expression(exp);
    cout << "The result is " << expression.result() << endl;

    
    return 0;
}


//到底是什么原因导致expression的的析构出问题？
//通过简单的程序发现，可以通过指针赋值直接回收空间