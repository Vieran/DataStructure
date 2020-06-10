#include <iostream>
#include <algorithm>
#include <functional> //改变排序方式
#include <vector>

using namespace std;

int main()
{
    int a[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    vector<int> va(a, a + 10);

    sort(va.begin(), va.end());            //默认升序排列（less的方式）
    sort(va.begin(), va.end(), greater()); //降序排列（greater的方式）

    return 0;
}