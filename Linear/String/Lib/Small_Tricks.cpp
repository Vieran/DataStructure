/*字符串匹配的KMP算法*/
//其他的实现就暂时不写了，只写这个匹配算法

#include "String.h"

//sub是目标字符串
int seqString::find(const seqString &sub) const
{
    int *p = new int[sub.len];//失效函数p是指：当j匹配而j+1不匹配时，j的位置应该放置的元素下标
    int j,i;

    //生成失效函数
    p[0] = -1;//很显然p[0]=-1
    for (i = 1; i < sub.len; ++i)//i表示后缀，j表示前缀
    {
        j = i-1;//匹配的范围不能到达i，否则直接就是开头到结尾了
        while (j>=0 && sub.data[p[j]+1]!=sub.data[i])
            j = p[j];
        if(j<0)//后缀中没有元素和前缀匹配成功
            p[i] = -1;
        else//后缀和前缀存在匹配成功的元素
            p[i] = p[j]+1;
    }

    //查找
    i = j = 0;
    while (i<len && j<sub.len)
    {
        if (sub.data[j]==data[i])//对比目标字符串和主串的对应位元素
        {//对应元素匹配则进行下一位的对比
            ++i;
            ++j;
        }
        else//对应位元素不匹配，检查应该将目标字符串的哪一位移过来进行对比
            if(j==0)//第一个字符就不匹配
                ++i;//直接将主串向前进一位
            else
                j = p[j-1]+1;//此处的j是指匹配失败的位置应该回溯的下标
    }

    /*
    //对比
    //此处的p指：当j不匹配时，j回溯的元素下标
    p[0] = 0;
    i = 1;//表示后缀
    j = 0;//表示前缀
    while (i<sub.len)//寻找失效函数，直到目标字符串结束
    {
        if(sub.data[i]==sub.data[j] || j==0)
        {
            p[i] = p[j];
            ++j;
            ++i;

            //优化
            //if(sub.data[i]==sub.data[j])
                //p[i] = j;
            //else
                //p[i] = p[j];
        }
        else
            j = p[j];
    }

    while(j<sub.len && j<len)
    {
        if(sub.data[i]==sub.data[j])
        {
            ++i;
            ++j;
        }
        else
            j = p[j];
    }
    */

    delete [] p;
    if(j==sub.len)
        return i-j;//匹配成功，返回匹配的初始位置
    else
        return -1;
}

//为配合KMP算法，将seqString类的部分函数实现
//构造函数
seqString::seqString(const char *s)
{
    for(len=0;s[len]!='\0';++len);//计算字符串长度
    data = new char[len+1];//为其申请动态空间
    for(len=0;s[len]!='\0';++len)//将字符串内容拷贝到当前对象的data成员
        data[len] = s[len];

    data[len] = '\0';
}

//析构函数
seqString::~seqString()
{
    delete data;
}