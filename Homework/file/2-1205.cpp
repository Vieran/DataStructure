//2020.3.11---Ackerman
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1205
//输入两个数字m，n，输出其对应的akerman函数值

#include <iostream>
using namespace std;

int Ackerman(int m, int n)
{
    if (m == 0)
        return n + 1;

    if (m > 0 && n == 0)
        return Ackerman(m - 1, 1);
    else if (m > 0 && n > 0)
        return Ackerman(m - 1, Ackerman(m, n - 1));
}

int main()
{
    int m, n;
    cin >> m >> n;
    cout << Ackerman(m, n);
    return 0;
}