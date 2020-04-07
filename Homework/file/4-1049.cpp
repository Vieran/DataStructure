//2020.3.25---火车调度
//题目链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1049
//判断能否成功调度

#include <stdio.h>
#include <stack>
using namespace std;

int main()
{
    int t; //总共多少个测试点
    scanf("%d", &t);
    bool *flag1 = new bool[t];

    int n, m; //分别是火车数量，调度站最大容量
    for (int i = 0; i < t; i++)
    {
        stack<int> attempt;
        scanf("%d%d", &n, &m);
        int *goal = new int[n];
        for (int i = 0; i < n; i++) //获取目标
            scanf("%d", &goal[i]);

        //判断是否能够调度
        bool flag = false;
        int num = 0, goalnum = 0, count; //当前处理的火车编号，目标数组的下标（需要放行的火车编号），计数器
        for (count = 0; count < n; count++)
        {
            if (goal[goalnum] != count) //即将到来的列车不满足放行的要求
            {
                while (!attempt.empty())
                {
                    if (!attempt.empty() && attempt.top() == goal[goalnum]) //如果栈顶火车需要放行
                    {
                        attempt.pop(); //放行
                        ++goalnum;     //数组下标+1
                    }
                    else
                        break; //直到没有需要放行的
                }
                //栈顶火车不能放行
                if (goal[goalnum] < count) //遇到的火车编号比需要出栈的大，且栈顶火车不能放行
                    break;                 //直接结束，不可能再出现符合要求的了

                if (attempt.size() < m)  //调度站未满
                    attempt.push(count); //入栈
                else
                    break; //必须出栈，不满足条件，跳出循环，结束
            }
            else           //即将到来的列车满足放行要求
                ++goalnum; //放行，处理数组下一个元素
        }
        for (int k = 0; !attempt.empty(); k++) //处理所有还在栈里的火车
        {
            if (attempt.top() == goal[goalnum]) //如果栈顶火车需要放行
            {
                attempt.pop(); //放行
                ++goalnum;     //数组下标+1
            }
            else
                break; //一旦遇到不能放行的火车，终止
        }
        if (goalnum == n && attempt.empty()) //全部火车都符合条件且放行了
            flag = true;

        if (flag)
            flag1[i] = true;
        else
            flag1[i] = false;

        delete[] goal; //回收空间
    }

    //统一输出答案
    for (int i = 0; i < t; i++)
    {
        if (flag1[i])
            printf("%s\n", "YES");
        else
            printf("%s\n", "NO");
    }
    delete[] flag1;

    return 0;
}

/*
1.将要求的顺序收入数组
2.对进来的列车一个个与数组进行比较，比它小则进栈，遇到则直接给过，比它大则到栈顶去找（注意是栈顶）
3.需要进栈的时候没有空间则no，没有遇到也no，比它大而且栈顶没有也no
4.一直不no则yes
*/
//错误1：此题目是栈而不是队列
//错误2：应该每次检查所有栈中火车是否需要出栈，而不是只检查一列，否则将会缩小yes的可能性