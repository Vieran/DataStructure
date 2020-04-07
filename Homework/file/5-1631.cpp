//2020.4.1---字符串相除
//链接https://acm.sjtu.edu.cn/OnlineJudge/problem/1631
//讲字符串倒过来，相除，再倒过来

#include <stdio.h>
#include <iostream>
using namespace std;

char tentotwo(char *s,int len)
{
    
}


int main()
{
    char str1[10],str2[10];
    cin.getline(str1,10);
    cin.getline(str2,10);


    
    return 0;
}

//整体思路：写一个bigbigint类型，将获取的字符串传递给它，执行除法函数，最后将除法结果返回(×)
//除法实现较难（数据太大了）
//改用二进制的算法实现除法，则直接将数字转换为二进制数字进行运算，最后将二进制数字转换回来