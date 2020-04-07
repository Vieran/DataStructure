#include <iostream>
#include "Small_Trick.h"
using namespace std;

int main()
{
    /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
    
    //最大公因子问题
    cout << "Please input x,y:";
    int x,y;
    cin >> x >> y;
    cout << "The greatest Common Divisor is " << GCD_refined(x,y) << "or" << GCD_rough(x,y);
    cout << endl;

    /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

    //全排列问题
    cout << "Please input the length of the string:";
    int length;
    cin >> length;
    cout << "Please intput the string:";
    char *str = new char[length+1];
    cin.get();//除去回车
    cin.getline(str,length+1);
    allrange_recur(0,length,str);
    delete [] str;

    return 0;
}