#include "Small_Trick.h"

/*表达式树的实现文件*/

//将中缀表达式转换成表达式树
Calc::node * Calc::creat(char *&s)
{
    Calc::node *p,*root=NULL;
    Type returnType;
    int value;

    while (*s)//顺序扫描表达式
    {
        returnType = Calc::getToken(s,value);//获取表达式的下一个语法单位
        switch (returnType)
        {
        case DATA: case OPAREN:
            if(returnType==DATA)//是运算数，申请一个节点保存运算数
                p = new node(DATA,value);//getToken函数将数值保存在value中了
            else//是(，创建一个节点保存()中的子表达式
                p = creat(s);
            if(root!=NULL)//如果根树非空，根据前一运算符的位置确定运算数的是哪个节点的右子节点
                if(root->rchild==NULL)//树根的右子节点为空
                    root->rchild = p;//将运算数存入其右子节点
                else
                    root->rchild->rchild = p;//树根的右子节点非空，则将运算数存入其右子节点的右子节点
            break;
        case CPAREN: case EOL://一棵树的构建完成了
            return root;
        case ADD:case SUB://+和-的优先级最低，总是作为当前树的根，原来的树是它的左子节点
            if(root==NULL)
                root = new node(returnType,0,p);
            else
                root = new node(returnType,0,root);
            break;
        case MULTI: case DIV:
            if(root==NULL)
                root = new node(returnType,0,p);
            else
                if(root->type==MULTI || root->type==DIV)//当根节点是*或者/时，从左到右计算
                    root = new node(returnType,0,root);//作为当前节点的根节点
                else
                    root->rchild = new node(returnType,0,root->rchild);
        }
    }
    return root;
}


//获取表达式中的下一个语法单位
Calc::Type Calc::getToken(char *&s,int &data)
{
    char type;

    while(*s==' ')//跳过空格
        ++s;
    
    if (*s>='0' && *s<='9')//遇到运算数
    {
        data = 0;
        while (*s>='0' && *s<='9')//一直取运算数，直到非运算数
        {
            data = data*10+*s-'0';
            ++s;
        }
        return DATA;
    }
    if(*s=='\0')
        return EOL;

    type = *s;
    ++s;
    switch (type)
    {
    case '+':
        return ADD;
    case '-':
        return SUB;
    case '*':
        return MULTI;
    case '/':
        return DIV;
    case '(':
        return OPAREN;
    case ')':
        return CPAREN;
    default:
        return EOL;
    }
}

//计算结果(递归实现)
int Calc::result(Calc::node *t)
{
    int num1,num2;

    if(t->type==DATA)
        return t->data;
    num1 = result(t->lchild);//计算左子表达式
    num2 = result(t->rchild);//计算右子表达式
    switch (t->type)
    {
    case ADD:
        t->data = num1 + num2;
        break;
    case SUB:
        t->data = num1 - num2;
        break;
    case MULTI:
        t->data = num1 * num2;
        break;
    case DIV:
        t->data = num1 / num2;
        break;
    }
    return t->data;
}