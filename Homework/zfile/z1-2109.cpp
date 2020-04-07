//二次方程，匹配a和b,c
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/2109
//读入和输出用scanf和printf，知识链接https://www.cnblogs.com/michaeljunlove/p/3883717.html

#include <stdio.h>
using namespace std;

int main()
{
    int n;
    scanf("%d",&n);
    int *N = new int[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d",&N[i]);
        fflush(stdin);
    }

    int k,b,c;
    scanf("%d",&k);
    int *KI = new int[k];
    for (int i = 0; i < k; ++i)
    {
        int ki=0;
        scanf("%d%d",&b,&c);
        fflush(stdin);
        for (int l = 0; l < n; ++l)
        {
            if (b*b-4*N[l]*c < 0)
                break;
            
            ++ki;
        }
        KI[i] = ki;
    }
    for(int i =0;i < k;++i)
        printf("%d\n",KI[i]);
    delete [] N;
    delete [] KI;
    
    return 0;
}

/*如下写，才不会超时
int main()
{
    int n;
    scanf("%d",&n);
    int N[100000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d",&N[i]);
    }

    int k,b,c;
    scanf("%d",&k);
    int KI[100000];
    int ki;
    for (int i = 0; i < k; ++i)
    {
        ki=0;
        scanf("%d%d",&b,&c);
        for (int l = 0; l < n; ++l)
        {
            if (b*b-4*N[l]*c < 0)
                break;
            
            ++ki;
        }
        KI[i] = ki;
    }
    for(int i =0;i < k;++i)
        printf("%d\n",KI[i]);
    //delete [] N;
    //delete [] KI;
    
    return 0;
}
*/