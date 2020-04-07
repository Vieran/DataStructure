//puzzle
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1338

#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
    int length;
    scanf("%d", &length);

    //int *num1 = new int[length], *num2 = new int[length];
    long long num1[10],num2[10];
    for (int i = 0; i < length; i++)
        scanf("%lld", &num1[i]);
    for (int i = 0; i < length; i++)
        scanf("%lld", &num2[i]);

    //对数组进行排序
    sort(num1, num1 + length);
    sort(num2, num2 + length);

    long long maxsum = 0, minsum = 0;
    for (int i = 0; i < length; i++)
    {
        maxsum += num1[i] * num2[i];
        minsum += num1[i] * num2[length - i - 1];
    }

    printf("%lld", maxsum);
    printf("%c", ' ');
    printf("%lld", minsum);

    //delete[] num1;
    //delete[] num2;
    return 0;
}

//据说sort函数时间复杂度比较小，十分适合用于排序
//sort默认从小到大排序，也可以从大到小排序（用到的时候再看看吧）
//使用int类型不够，得用long long类型，同时注意scanf和printf与之前的区别(与这两个函数的原理密切相关，空间长度)