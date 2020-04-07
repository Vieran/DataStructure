//2020.3.18---stack overflow
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/3012


#include <stdio.h>
#include <stack>
using namespace std;

int main()
{
    int op,num,N,k=0;
    scanf("%d",&N);
    stack<int> stackoverflow;
    int operat[10];
    for (int i = 0; i < N; i++)
    {
        scanf("%d%d",&op,&num);
        switch (op)
        {
        case 1:
            stackoverflow.push(num);
            operat[k] = 1;//1表示ok
            break;
        
        case 2:
            if(stackoverflow.empty())
                operat[k] = 0;//0表示error
            else
            {
                if(stackoverflow.top()==num)
                    operat[k] = 2;//2表示yes
                else
                    operat[k] = 3;//3表示no
                stackoverflow.pop();
            }
        break;
        }
        ++k;
    }
    
    for (int i = 0; i < k; i++)
    {
        switch (operat[i])
        {
        case 0:
            printf("%s\n","ERROR");
            break;
        
        case 1:
            printf("%s\n","OK");
            break;

        case 2:
            printf("%s\n","YES");
            break;
        
        case 3:
            printf("%s\n","NO");
            break;
        }
    }
    
    return 0;
}