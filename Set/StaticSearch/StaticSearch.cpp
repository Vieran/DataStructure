#include "Set.h"

int main()
{
    Set<int,int> a[10];
    for(int i=1;i<10;++i)
    {
        a[i].key = i;
        a[i].other = 0;
    } 

    int k;
    cout << "Please input the number you want to find:";
    cin >> k;

    int result = binarySearch(a,9,k);
    if(result==0)
        cout << "NOT FOUND.";
    else
        cout << "Find it on index " << result;
    
    return 0;
}