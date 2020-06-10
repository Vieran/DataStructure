/*STL中的动态查找*/

#include <iostream>
#include <set>
#include <map>
using namespace std;

int main()
{
    set<int> s;
    set<int>::iterator p;
    s.insert(1);
    p = s.begin();
    cout << *p << endl; //输出s中的第一个元素

    map<int, int> m; //第一个参数是关键字类型，第二个参数是值的类型
    map<int, int>::iterator q;
    m.insert(pair<int, int>(1, 0));
    q = m.begin();
    cout << q->first << '\t' << q->second << endl;

    return 0;
}

//set中不允许出现重复元素，所以插入可能不成功
//map中可以出现重复的值，但是关键字必须唯一