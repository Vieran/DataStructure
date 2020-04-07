//留下的水
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1550

#include <stdio.h>
using namespace std;

int main()
{
    int length;
    scanf("%d", &length);
    int *height = new int[length];
    char str;
    //scanf("%c",&str);
    for (int i = 0; i < length; i++)
        scanf("%d", &height[i]);
    //scanf("%c",&str);

    int standard1, standard2, k, i, sum;
    standard1 =  height[0];
    standard2 =  height[1];
    i = k = sum = 0;
    //先找到一个可以开始积水的地方
    while ( i < length && standard2>=standard1)
    {
        standard2 = height[i];
        standard1 = standard2;
        ++i;
    }

    while (i < length)
    {
        //寻找standard2
        while (standard2 < standard1 && k < length)
        {
            ++k;
            standard2 = height[k];
        }

        //计算积水
        if (standard2 >= standard1)
            for (; i < k; i++)
                sum += standard1 - height[i];
        else
            ++i;
        
        standard2 = height[++k];
    }
    printf("%d", sum);

    delete[] height;
    return 0;
}

//基本思路：从某一位置开始寻找与其相等的高度的位置，按照最大高度获取积分