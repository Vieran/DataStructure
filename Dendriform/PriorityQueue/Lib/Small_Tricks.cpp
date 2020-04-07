//排队系统的模拟实现文件

#include "Small_Trick.h"
#include "linkQueue.h"
#include "PriorityQueue.h"

Simulator::Simulator()
{
    cout << "Please input the number of counter:";
    cin >> NumOfServer;

    cout << "Please input the longest and shortest interval of arrival time:";
    cin >> arrivalHigh >> arrivalLow;

    cout << "Please input the longest and shortest interval of service time:";
    cin >> serviceTimeLow >> serviceTimeHigh;

    cout << "Please input the number of customers:";
    cin >> customNum;

    srand(time(NULL));//随机数发生器初始化
}

int Simulator::avgWaitTime()
{
    int serverBusy = 0;//正在工作的服务台数
    int currentTime;//记录模拟过程的时间
    int totalWaitTime = 0;//模拟过程中所有顾客等待时间的总和
    linkQueue<eventT> waitQueue;//顾客等待队列
    PriorityQueue<eventT> eventQueue;//事件队列

    eventT currentEvent;

    //生成当前的时间队列
    int i;
    currentEvent.time = 0;
    currentEvent.type = ARRIVE;
    for ( i = 0; i < customNum; ++i)
    {
        currentEvent.time += arrivalLow+(arrivalHigh-arrivalLow+1)*rand()/(RAND_MAX+1);//生成到达事件
        eventQueue.enQueue(currentEvent);//将事件入队
    }
    
    //模拟过程
    while (!eventQueue.isEmpty())
    {
        currentEvent = eventQueue.deQueue();//弹出当前需要处理的事件
        currentTime = currentEvent.time;
        switch (currentEvent.type)
        {
        case ARRIVE://处理到达事件
            if (serverBusy!=NumOfServer)//存在空闲的服务台
            {
                ++serverBusy;//安排服务台为客户服务
                currentEvent.time += serviceTimeLow+(serviceTimeHigh-serviceTimeLow+1)*rand()/(RAND_MAX+1);//将时钟拨到服务结束的时间
                currentEvent.type = LEAVE;//将事件类型改为离开
                eventQueue.enQueue(currentEvent);//将离开事件插入到事件队列中
            }
            else
                waitQueue.enQueue(currentEvent);//没有空闲的服务台，将顾客安排到等待队列
            break;
        case LEAVE://处理离开事件
            if (!waitQueue.isEmpty())//存在排队的顾客
            {
                currentEvent = waitQueue.deQueue();//将排队的顾客弹出
                totalWaitTime += currentTime-currentEvent.time;//将其等待的时间加入顾客总等待时间
                currentEvent.time = currentTime+serviceTimeLow+(serviceTimeHigh-serviceTimeLow+1)*rand()/(RAND_MAX+1);//记录顾客离开时间
                currentEvent.type = LEAVE;//将事件类型改为离开
                eventQueue.enQueue(currentEvent);//将离开事件插入到队列中
            }
            else//不存在在排队的顾客
                --serverBusy;//服务台休息
        }
    }
    if(customNum==0)
        throw "Intend to divide by zero.";
    return totalWaitTime/customNum;
}