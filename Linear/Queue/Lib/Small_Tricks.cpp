/*队列的应用实现文件*/

#include "Small_Trick.h"
#include "linkQueue.h"
#include <cstdlib>
#include <ctime>

/*火车车厢重排问题(顺序排列)*/
//车厢进入合适的缓冲轨道
//参数：入轨上的车厢序列，车厢个数，缓冲轨道数
void arrange(int in[],int n,int k)
{
    linkQueue<int> *buffer = new linkQueue<int>[k];//表示k条缓冲轨道
    int last = 0;//出轨上最后一节车厢的编号

    for (int i = 0; i < n; ++i)//依次处理入轨上的车厢
    {
        if(!putBuffer(buffer,k,in[i]))//检测是否有合适的缓冲轨道（合适则放上去）
            exit(-1);//没有可用轨道则直接结束此函数
        checkBuffer(buffer,k,last);//将队列中是否合适的车厢放到出轨上
    }
}


//判断是否进入了合适的缓冲队列
//参数：一组缓冲队列，缓冲队列数，即将进入缓冲队列的车厢编号
bool putBuffer(linkQueue<int> *buffer,int size,int in)
{
    int avail = -1,max = 0;//avail为最合适的缓冲队列号，max是该队列尾元素的编号

    for (int i = 0; i < size; ++i)//寻找最合适的队列
    {
        if(buffer[i].isEmpty())//找到空队列，备用
        {    if(avail==-1)
                avail = i;
        }
        else if (buffer[i].getTail()<in && buffer[i].getTail()>max)//如果队列非空，判断是否合适
        {
            avail = i;//合适则将其安排为对应的队列
            max = buffer[i].getTail();
        }
    }

    if (avail!=-1)//找到了合适的队列
    {
        buffer[avail].enQueue(in);//进入队列
        cout << in << " move into buffer " << avail << endl;
        return true;
    }
    else
    {
        cout << "No suitable scheme." << endl;
        return false;
    }
}

//将缓冲队列中合适的车厢放到出轨上
//参数：一组缓冲队列，队列数，出轨上最后一节车厢的编号
void checkBuffer(linkQueue<int> *buffer,int size,int &last)
{
    bool flag = true;

    int k;
    while (flag)//反复检查所有队列，将合适的元素出队
    {
        flag = false;

        for ( k = 0; k < size; ++k)//逐个队列进行检查
        {
            if (!buffer[k].isEmpty() && buffer[k].getHead()==last+1)//判断队列的头元素是否适合进入出轨
            {//出队
                cout << "Move " << buffer[k].deQueue() << " from buffer " << k << " to the track." << endl;
                ++last;
                flag = true;
                break;
            }
        }
    }
}


/*模拟排队系统*/
//构造函数
Simulator::Simulator()
{
    cout << "Please input the longest and shortest interval of arrival:";
    cin >> arrivalHigh >> arrivalLow;

    cout << "Please input the longest and shortest interval of service:";
    cin >> serviceTimeHigh >> serviceTimeLow;

    cout << "Please input the number of customs:";
    cin >> customNum;

    srand(time(NULL));//初始化随机数发生器
}

//模拟过程
int Simulator::avgWaitTime() const
{
    int currentTime = 0;//当前时间
    int totalWaitTime = 0;//总的等待时间
    int eventTime;
    linkQueue<int> customerQueue;//顾客到达事件队列

    for (int i = 0; i < customNum; ++i)//生成所有的到达事件
    {
        currentTime += arrivalLow + (arrivalHigh-arrivalLow+1)*rand()/(RAND_MAX+1);//将时间拨到顾客到达时刻
        customerQueue.enQueue(currentTime);//将生成的到达事件入队
    }

    //处理所有的到达事件
    currentTime = 0;
    while (!customerQueue.isEmpty())
    {
        eventTime = customerQueue.deQueue();//将要处理的顾客事件弹出队列
        if(eventTime<currentTime)
            totalWaitTime += currentTime-eventTime;//顾客已经在等待
        else
            currentTime = eventTime;//顾客没有在等待，将时间拨到顾客到达的时间
        currentTime += serviceTimeLow+(serviceTimeHigh-serviceTimeLow+1)*rand()/(RAND_MAX+1);//将时间拨到服务完成时刻
    }
    
    if(customNum<=0)
        throw "custom number error!";
    else
        return totalWaitTime/customNum;//返回顾客平均等待时间
}