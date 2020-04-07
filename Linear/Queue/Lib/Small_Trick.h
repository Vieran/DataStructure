/*队列的应用声明文件*/

#ifndef SMALL_TRICK_H
#define SMALL_TRICK_H

#include "linkQueue.h"

/*火车车厢重排问题(顺序排列)*/
//车厢进入合适的缓冲轨道
//参数：入轨上的车厢序列，车厢个数，缓冲轨道数
void arrange(int in[],int n,int k);

//判断是否进入了合适的缓冲队列
//参数：一组缓冲队列，缓冲队列数，即将进入缓冲队列的车厢编号
bool putBuffer(linkQueue<int> *buffer,int size,int in);

//车厢进入出轨
//参数：一组缓冲队列，队列数，出轨上最后一节车厢的编号
void checkBuffer(linkQueue<int> *buffer,int size,int &last);



/*模拟排队系统*/
//Simulator类的定义
class Simulator
{
private:
    int arrivalLow;//到达间隔时间的下限
    int arrivalHigh;//到达间隔时间的上限
    int serviceTimeLow;//服务时间下限
    int serviceTimeHigh;//服务时间上限
    int customNum;//模拟顾客数
public:
    Simulator();
    int avgWaitTime() const;
};


#endif