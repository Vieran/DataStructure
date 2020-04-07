//2020.3.4---从前有座山
//题目链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1021
//给定n的值，输出n*n矩形山的海拔高度图


#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    //cout << "Please input the altitude of the mountain:";
    int N, n, outside, add; //分别为阶数，层数，外层总和，增量
    cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (i < j) //计算层数
                n = i < (N - j + 1) ? i : (N - j + 1);
            else
                n = j < (N - i + 1) ? j : (N - i + 1);

            outside = 4 * (n - 1) * (N - n + 1); //由4*[(N-1)+(N-2)+…+(N-1-2*(n-1-1))]化简而来

            //计算增量
            if (i < j || (i == n && j == n))
                add = i - n + j - n + 1;
            else
                add = 2 * (N - 2 * (n - 1) - 1) + (N - n + 1 - i) + (N - n + 1 - j) + 1;
            cout << setw(6) << outside + add;
        }
        cout << endl;
    }
    return 0;
}

//根据程序一步一步看吧，其实或许可以更加简化一点
//思路：要么直接输出；要么建一个数组，将数字先填好，然后将数组输出
//都需要将数字和位置的关系找清楚