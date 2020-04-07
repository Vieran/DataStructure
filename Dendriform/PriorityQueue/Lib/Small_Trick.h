/*排队系统的模拟定义文件*/
#ifndef SMALL_TRICKS_H
#define SMALL_TRICKS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Simulator
{
private:
    int NumOfServer;//服务台个数
    int arrivalLow;//到达时间间隔的下限
    int arrivalHigh;//到达时间间隔的上限
    int serviceTimeLow;//服务时间间隔的下限
    int serviceTimeHigh;//服务时间间隔的上限
    int customNum;//模拟的顾客数

    enum Type{ARRIVE,LEAVE};//事件类型，到达是0，离开是1

    struct eventT
    {
        int time;//事件发生的时间
        Type type;//事件类型
        bool operator<(const eventT &e) const
        {
            return time<e.time;
        }
    };
    
public:
    Simulator();
    int avgWaitTime();
};

#endif