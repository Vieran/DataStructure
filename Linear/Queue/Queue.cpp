#include "Small_Trick.h"
#include "seqQueue.h"
#include <cstring>

int main()
{
    //火车车厢重排
    cout << "Please input the number of the train carbin:";
    int number;
    cin >> number;

    cout << "Please input the sequence of the train carbin:";
    int *sequence = new int[number];
    for(int i=0;i<number;++i)
        cin >> sequence[i];
    
    cout << "Please input the number of buffer:";
    int buffer;
    cin >> buffer;

    arrange(sequence,number,buffer);
    delete [] sequence;


    //模拟排队系统
    Simulator sim;
    try{
        cout << "Average waiting time: " << sim.avgWaitTime() << endl;
    }
    catch(const char *msg){
        cerr << msg << endl;
    }

    return 0;
}