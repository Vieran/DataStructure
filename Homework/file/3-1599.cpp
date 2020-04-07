//2020.3.18---brackets stack
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1599

#include <iomanip>
using namespace std;

class stack
{
private:
    //enum TYPE{smallOPEN,smallCLOSE,midOPEN,midCLOSE,bigOPEN,bigCLOSE};
    //原意使用enum，但是发现没必要（程序太小了）
    struct Node
    {
        char data;
        Node *next;

        Node(char str, Node *n = NULL) : data(str), next(n) {}
    };
    Node *head;

public:
    //构造函数
    stack()
    {
        head = NULL;
    }

    //析构函数
    ~stack()
    {
        Node *p = head, *q;
        while (p != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }

    //操作1，插入
    void push(char str)
    {
        //将head一直放在栈顶，方便操作
        if (head == NULL)
            head = new Node(str);
        else
            head = new Node(str, head);
    }

    //操作2，弹出栈顶元素
    void pop()
    {
        if (head == NULL)
            return;

        Node *p = head, *q = head->next;
        delete head;
        head = q;
    }

    //操作3，输出栈顶元素
    char top()
    {
        if (head == NULL)
            return '-';//用-作为null的标记
        return head->data;
    }

    //操作4，判断括号是否匹配
    bool match()
    {
        stack OPEN;
        Node *p = head;
        if(p==NULL)
            return true;
        while (p != NULL)
        {
            if (p->data == ')' || p->data == ']' || p->data == '}')
                OPEN.push(p->data);
            else if (p->data == '(' && OPEN.top() == ')')
                OPEN.pop();
            else if (p->data == '[' && OPEN.top() == ']')
                OPEN.pop();
            else if (p->data == '{' && OPEN.top() == '}')
                OPEN.pop();
            else
                return false;
            
            p = p->next;
        }
        if(OPEN.head==NULL)
            return true;
        return false;
    }
};

int main()
{
    stack link;
    int op, times,k=0;
    char str, str1; //str1用于存储空格
    scanf("%d", &times);
    char n[10];
    for (int i = 0; i < times; i++)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            scanf("%c", &str1);
            scanf("%c", &str);
            link.push(str);
            break;

        case 2:
            link.pop();
            break;

        case 3:
            n[k] = link.top();
            ++k;
            break;

        case 4:
            if (link.match())
                n[k] = '1';
                //printf("%s", "YES");
            else
                n[k] = '0';
                //printf("%s", "NO");
            ++k;
            break;
        }
        //fflush(stdin);
    }

    for (int i = 0; i < k; i++)
    {
        switch (n[i])
        {
        case '1':
            printf("%s\n","YES");
            break;
        case '0':
            printf("%s\n","NO");
            break;
        case '-':
            break;
        default:
            printf("%c\n",n[i]);
            break;
        }
    }
    

    return 0;
}
