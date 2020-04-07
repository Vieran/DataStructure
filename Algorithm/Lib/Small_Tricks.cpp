/*小型练习的集中地*/

#include <iostream>
#include <queue>
using namespace std;

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/*最大公因子问题：给出两个正整数x，y，最大公因子GCD是能够同时被两个数整除的最大数*/
/*设计函数   int GCD(int x,int y),求出x和y的最大公因子*/

//蛮力算法
int GCD_rough(int x,int y)
{
    int min = x<y ? x:y;//取x和y中较小者
    while (x%min!=0 || y%min!=0)//进行从大到小的循环（因为是求最大，所以从最大的开始减少）
        --min;
    return min;//返回最大公因子
}

//辗转相除法
int GCD_refined(int x,int y)
{
    int GCD,r;
    while(true)
    {
        r = x%y;//取s除以y的余数r
        if(r==0) break;//如果r=0，答案是y
        x = y;//如果x!=0，设x为原来y的值，y=r，重复过程
        y = r;
    }
    return y;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/*打印n个字符的全排列*/
/*设计函数 void allrange(int k,int n,char str[])，打印字符串数组str的第k位到第n-1位的全排列*/

//递归方法
void Swap(char &a,char &b);//声明工具函数
void allrange_recur(int k,int n,char str[])
{
    if(k==n-1){
        for(int i=0;i<n;++i)
            cout << str[i] << ' ';
        cout << '\t';
    }
    else
    {
        for (int i = k; i < n; ++i)
        {
            Swap(str[k],str[i]);
            allrange_recur(k+1,n,str);
            Swap(str[k],str[i]);
        }   
    }
}
//交换两个字符的位置（工具函数）
void Swap(char &a,char &b)
{
    char tmp = a;
    a = b;
    b = tmp;
}

//非递归方法
//I can't figure it out now.And i don't want to copy the answer.
//Emmm,just leave it.I will go back to fix it when i can work it out by myself.

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/


