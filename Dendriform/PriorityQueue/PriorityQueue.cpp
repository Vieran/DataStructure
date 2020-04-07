#include "PriorityQueue.h"
#include "Small_Trick.h"

int main()
{
    Simulator sim;
    try
    {
        cout << "Average waiting time: " << sim.avgWaitTime();
    }
    catch(const char *msg)
    {
        cerr << msg << '\n';
    }
    return 0;
}