//栈的应用实现文件

#include "Small_Trick.h"
#include "linkStack.h"
#include "seqStack.h"
#include <cstring>
#include <cmath>


//判断是否为回文序列
bool isReverse(char *s)
{
    linkStack<char> st;

    for (int i = 0; i < strlen(s); ++i)
        st.push(s[i]);
    
    for (int k = 0; !st.isEmpty(); ++k)
        if(s[k]!=st.pop())
            return false;
    return true;
}

/*递归消除（函数调用是通过栈实现的，如果可以控制栈，则可以消除递归调用）*/
//打印整数的递归函数
void printInt_re(int num)
{
    if(num < 10)//递归的终止条件
        cout.put(num+'0');
    else{
        printInt_re(num/10);//递归调用自身
        cout.put(num%10 + '0');
    }
}

//打印整数的非递归函数
void printInt_nore(int num)
{
    linkStack<int> number;//构造一个链栈
    int tmp;

    number.push(num);//将数字存入栈顶
    while (!number.isEmpty())
    {
        tmp = number.pop();
        if(tmp > 9)
        {
            number.push(tmp%10);//如果大于10则将其对10取模的数字存入栈（原来的个位数）
            number.push(tmp/10);//再将他，p除以10的结果存入栈（少了原来的个位数）
        }
        else cout.put(tmp+'0');
        //此函数的理解，须结合递归的栈的使用图
    }
}


/*括号配对的实现*/

//构造函数
Balance::Balance(const char *s)
{
    fin.open(s);//打开文件
    if(!fin)
        throw noFile();//打开文件不存在则抛出异常

    //给一部分数字赋初值
    currentLine = 1;
    Errors = 0;
}

//checkbalance函数的实现
int Balance::CheckBalance()
{
    struct Symbol node;//构建存储错误的对象
    linkStack<Symbol> st;//构建栈对象，用于存储左括号
    char LastChar,Match;//分别为读入符号和栈顶符号

    while (LastChar = GetNextSymbol())//从文件中读入符号直到文件结束
    {
        switch (LastChar)
        {
        case '(' : case '[' : case '{'://若是三种左括号之一，则进栈
            node.Token = LastChar;
            node.TheLine = currentLine;
            st.push(node);
            break;
        case ')' : case ']' : case '}'://若是三种右括号之一，则进行检查配对
            if(st.isEmpty()){//没有对应的左括号
                ++Errors;//错误+1
                cout << "There is an unwanted '" << LastChar <<"' in line" << currentLine << endl;
            }
            else
            {
                node = st.pop();//弹出栈顶的左括号
                Match = node.Token;
                if(!CheckMatch(Match,LastChar,node.TheLine,currentLine))//对左右括号进行匹配
                    ++Errors;//匹配不成功则错误+1
            }
            break;
        }
    }

    while (!st.isEmpty())//此时的栈中仍然存在的左括号均没有遇到右括号
    {
        ++Errors;
        node = st.pop();//将元素栈顶弹出来
        cout << "There is a unwanted '" << LastChar <<"' in line" << currentLine << endl; 
    }
    return Errors;
}

//总结错误个数，并输出
void Balance::ReportError(int num)
{
    if(num>1)
        cout << num << " errors in total." << endl;
    else
        cout << num << " error in total." << endl;
}

//工具函数的实现
//检查括号是否配对
bool Balance::CheckMatch(char Symb1,char Symb2,int Line1,int Line2)
{
    if (Symb1=='(' && Symb2!=')' || Symb1=='[' && Symb2!=']' || Symb1=='{' && Symb2!='}')//括号不配对的情况
    {
        cout << Line2 << "'s " << Symb1 << "doesn't match " << Line1 << "'s " << Symb2 << endl;//输出错误信息
        return false;
    }
    else return true;
}

//获取程序的下一个字符（注释不算在内）
char Balance::GetNextSymbol()
{
    char ch;
    while (ch = NextChar())
    {
        if (ch=='\\')//出现斜杠，检查是否是注释
        {
            ch = NextChar();//再获取下一个字符
            if(ch=='*')//处理c风格的注释
                SkipComment(SlashStar);
            else if(ch=='/')
                    SkipComment(SlashSlash);//处理c++风格的注释
                else PutBackChar(ch);//不是注释，将ch放回到输入流中
        }
        else if(ch=='\\' || ch=='"')
                SkipQuote(ch);//处理字符常量或字符串常量或者转义的字符
            else if(ch=='{' || ch=='[' || ch=='(' || ch==')' || ch==']' || ch=='}')
                return ch;//如果是非注释和字符串的括号，直接返回
    }
    return NULL;//while循环结束，则文件也结束了(函数的返回值分明是char，但是可以用null作为返回值？)
}

//从输入的文件流中读取下一个字符
char Balance::NextChar()
{
    char ch;
    if((ch=fin.get())==EOF)
        return NULL;//文件结束，返回null
    if(ch=='\n')
        ++currentLine;//读入换行符，行数+1
    return ch;//返回读入的字符
}

//将传入的字符放回输入流
void Balance::PutBackChar(char ch)
{
    fin.putback(ch);//这个函数？还没有见过
    if(ch=='\n')
        --currentLine;//如果放回的是回车，则行号-1
}

//跳过字符或字符串常量
void Balance::SkipQuote(char type)
{
    char ch;
    while(ch=NextChar())
    {
        if(ch==type)
            return;//如果双引号或者单引号配对（说明是字符或者字符串），成功跳过常量，直接返回
        else if(ch=='\n'){
            ++Errors;//字符或者字符串不允许跨行
            cout << "Missing closing quote at line " << currentLine << endl;
            return;
        }
            else if(ch=='\\')
                ch = NextChar();//跳过转义字符（在此处读取了斜杠的下一个字符，下次读取的就不是转义字符了）
    }
}

//跳过注释
void Balance::SkipComment(enum CommentType type)
{
    char ch;
    if(type == SlashSlash){//处理双斜杠类型的注释
        while((ch=NextChar())&&(ch!='\n'));//一直跳过直到换行（此注释不换行）
            return;
    }
    
    //处理斜杠星类型的注释
    char flag = ' ';//设置flag的初值为空
    while((ch=NextChar())!=NULL){
        if(flag=='*' && ch=='/')
            return;
        flag = ch;//保存ch，以便下一个循环和ch进行比较配对
    }

    //如果直到文件结束，注释都没有结束，错误+1
    ++Errors;
    cout << "Comment is unterminated!" << endl;
}

/*简单的计算器的实现*/

//result函数的实现
int Calc::result()
{
    token lastOp,topOp;//在此可看到枚举类型的使用，token是枚举'类'型
    int result_value,current_value;
    seqStack<token> opStack;//运算符栈
    seqStack<int> dataStack;//运算数栈

    char *p = expression;//保存指针指向的动态空间的首地址

    while ((lastOp=getOp(current_value))!=EOL)//扫描表达式,并判断表达式是否结束
    {
        switch(lastOp)//当前符号
        {
            case VALUE://数字，则存入运算数栈
                dataStack.push(current_value);
                break;
            case OPAREN://是(,则存入运算符栈
                opStack.push(OPAREN);
                break;
            case CPAREN://是),进行括号内的运算，同时检查括号配对
                while (!opStack.isEmpty()&&(topOp=opStack.pop())!=OPAREN)
                    BinaryOp(topOp,dataStack);//执行算术运算
                if(topOp!=OPAREN)//while循环结束，没有左括号配对
                    cerr << "Lack of '('." << endl;//报错
                break;
            case EXP://是^,则存入运算符栈
                opStack.push(EXP);
                break;
            case MULTI:case DIV://是*或者/，则栈中优先级不低于*的运算符(*、/、^)退栈执行，并将当前运算符进栈
                while(!opStack.isEmpty() && opStack.top()>=MULTI)
                    BinaryOp(opStack.pop(),dataStack);
                opStack.push(lastOp);
                break;
            case ADD:case SUB://是+或者-，则栈中优先级不低于*的运算符(，除开左括号之外)退栈执行，并将当前运算符进栈
                while(!opStack.isEmpty() && opStack.top()!=OPAREN)
                    BinaryOp(opStack.pop(),dataStack);
                opStack.push(lastOp);
        }
    }
    //运算符栈中的所有运算符出栈执行
    while(!opStack.isEmpty())
        BinaryOp(opStack.pop(),dataStack);
    if (dataStack.isEmpty())//运算数栈空
    {
        cout << "No result." << endl;//出错，无结果
        return 0;
    }
    result_value = dataStack.pop();//保存结果
    if (!dataStack.isEmpty())//弹出结果后，运算数栈非空
    {
        cout << "Lack of operator." ;//出错，缺少运算符
        return 0;
    }
    
    expression = p;
    return result_value;
}

//执行一个算术运算
void Calc::BinaryOp(token op,seqStack<int> &dataStack)
{
    int num1,num2;
    if (dataStack.isEmpty())
    {
        cerr << "Lack of right operator.";
        exit(1);
    }
    else num2 = dataStack.pop();//取出右运算数

    if (dataStack.isEmpty())
    {
        cerr << "Lack of left operator.";
        exit(1);
    }
    else num1 = dataStack.pop();//取出左运算数

    switch (op)//执行结果，并将结果进栈
    {
    case ADD:
        dataStack.push(num1+num2);
        break;
    case SUB:
        dataStack.push(num1-num2);
        break;
    case MULTI:
        dataStack.push(num1*num2);
        break;
    case DIV:
        dataStack.push(num1/num2);
        break;
    case EXP:
        dataStack.push(pow(num1,num2));
    }
}

//从表达式中取出一个合法的符号
Calc::token Calc::getOp(int &value)//注意这种写法
{
    //跳过表达式中的空格
    while(*expression!='\0' && *expression==' ')
        ++expression;

    if(*expression=='\0')//判断是否运算结束
        return EOL;

    //处理运算数(转换称为整型数存入value中，这也体现了引用传递的优越性)
    if (*expression>='0' && *expression<='9')
    {
        value = 0;
        while (*expression>='0' && *expression<='9')
        {
            value = value*10 + *expression - '0';
            ++expression;
        }
        return VALUE;
    }

    //处理运算符
    switch (*expression)
    {
    case '(':
        ++expression;
        return OPAREN;
    case ')':        
        ++expression;
        return CPAREN;
    case '+':
        ++expression;
        return ADD;
    case '-':
        ++expression;
        return SUB;
    case '*':
        ++expression;
        return MULTI;
    case '/':
        ++expression;
        return DIV;
    case '^':
        ++expression;
        return EXP;
    }
}