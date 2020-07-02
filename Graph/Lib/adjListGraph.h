/*基于邻接表的图类的定义*/

#include "Graph.h"
#include "linkQueue.h"
#include "DisjointSet.h"
#include <iostream>
#include <queue>
using namespace std;

#ifndef ADJLISTGRAPH_H
#define ADJLISTGRAPH_H

template <class TypeOfVer, class TypeOfEdge>
class adjListGraph : public graph<TypeOfVer, TypeOfEdge>
{
private:
    //保存边的邻接表的数据元素类型
    struct edgeNode
    {
        int end;           //终点的编号
        TypeOfEdge weight; //边的权值
        edgeNode *next;

        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL) //构造函数
        {
            end = e;
            weight = w;
            next = n;
        }
    };

    //保存结点的数据元素类型
    struct verNode
    {
        TypeOfVer ver;  //顶点值
        edgeNode *head; //对应单链表的头指针

        verNode(edgeNode *h = NULL) { head = h; } //构造函数
    };

    verNode *verList; //保存结点所在的数组的指针

    //查找值为v的结点
    int find(TypeOfVer v) const
    {
        for (int i = 0; i < this->Vers; ++i)
            if (verList[i].ver == v)
                return i;
    }

    //图的遍历工具函数
    void dfs(int start, bool visited[]) const; //深度优先搜索

    /*欧拉回路*/
    struct EulerNode //欧拉路径中的结点类
    {
        int NodeNum;     //结点编号
        EulerNode *next; //指向下一结点的指针
        EulerNode(int ver)
        {
            NodeNum = ver;
            next = NULL;
        }
    };
    void EulerCircuit(int start, EulerNode *&beg, EulerNode *&end); //私有的工具函数
    verNode *clone() const;

    /*拓扑排序*/
    void topSort() const;

    /*关键路径*/
    void criticalPath() const;

public:
    //基本运算
    adjListGraph(int vSize, const TypeOfVer d[]);
    ~adjListGraph();
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;

    //图的遍历
    void dfs() const; //深度优先搜索
    void bfs() const; //广度优先搜索

    //欧拉回路(对外公开的接口)
    void EulerCircuit(TypeOfVer start);

    //最小生成树
    void kruskal() const;
    void prim(TypeOfEdge noEdge) const;

    //非加权图最短路径问题
    void unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const;
    void printPath(int start, int end, int prev[]) const;

    //加权图最短路径问题(dijkstra算法)
    void Dijkstra(TypeOfVer start, TypeOfEdge noEdge) const;

    //所有顶点对的最短路径问题(floyd算法)
    void Floyd() const;
};

#endif

//构造函数
//参数：结点数组的大小，结点数组的首地址
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    //初始化节点数和边数的值
    this->Vers = vSize;
    this->Edges = 0;

    verList = new verNode[vSize];        //为存储结点的数组申请空间
    for (int i = 0; i < this->Vers; ++i) //将结点一一赋给数组
        verList[i].ver = d[i];
}

//析构函数
template <class TypeOfVer, class TypeOfEdge>
adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *p;                               //为释放存储边的链表作准备
    for (int i = 0; i < this->Vers; ++i)       //释放每个结点对应的单链表的空间
        while ((p == verList[i].head) != NULL) //释放链表的每一个结点
        {
            verList[i].head = p->next;
            delete p;
        }
    delete[] verList;
}

//在x和y之间插入权值为w的边
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w)
{
    int u = find(x), v = find(y);                          //找到结点x和y对应的内部编号
    verList[u].head = new edgeNode(v, w, verList[u].head); //为插入的边申请一个单链表的结点（将新的边插入表头以提高效率）
    ++this->Edges;                                         //边增加1
}

//删除x和y之间的边
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    int u = find(x), v = find(y);      //找到x和y对应的内部编号
    edgeNode *p = verList[u].head, *q; //获取被删结点x的边的链表

    if (p == NULL) //结点x没有相连的边
        return;

    if (p->end == v) //单链表中的第一个结点就是被删除的边（因为没有设置头节点，所以得特殊处理第一个节点）
    {
        verList[u].head = p->next;
        delete p;
        --this->Edges; //边数减少1
        return;
    }

    while (p->next != NULL & p->next->end != v) //查找需要被删除的边
        p = p->next;

    if (p->next != NULL) //执行删除操作
    {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges; //边数减少1
    }
}

//判断x和y之间是否存在边
template <class TypeOfVer, class TypeOfEdge>
bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
    int u = find(x), v = find(y);  //找到x和y对应的内部编号
    edgeNode *p = verList[u].head; //获取被删结点x的边的链表

    while (p != NULL && p->end != v)
        p = p->next;

    if (p == NULL) //结点x和y之间没有边
        return false;
    else
        return true;
}

/*-------------------------------------------------------------图的遍历-----------------------------------------------------------------------------*/

//深度优先搜索dfs
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited = new bool[this->Vers]; //记录每个结点是否已经被访问
    for (int i = 0; i < this->Vers; ++i)  //将所有结点设为未访问
        visited[i] = false;

    cout << "The result of depth first search is :" << endl;

    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true)
            continue;
        dfs(i, visited);
        cout << endl;
    }
}

//从第一个参数结点开始遍历，第二个参数记录结点是否被访问过
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head; //获取结点对应的单链表

    cout << verList[start].ver << '\t'; //访问结点
    visited[start] = true;

    while (p != NULL) //对start的后继结点执行dfs
    {
        if (visited[p->end] == false)
            dfs(p->end, visited);
        p = p->next;
    }
}

//广度优先搜索
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool[this->Vers];
    int currentNode;
    linkQueue<int> q;
    edgeNode *p;

    for (int i = 0; i < this->Vers; ++i) //初始化所有元素为未访问
        visited[i] = false;

    cout << "The result of breadth first search:" << endl;

    for (int i = 0; i < this->Vers; ++i)
    {
        if (visited[i] == true)
            continue;
        q.enQueue(i);
        while (!q.isEmpty())
        {
            currentNode = q.deQueue();
            if (visited[currentNode] == true)
                continue;
            cout << verList[currentNode].ver << '\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p != NULL) //将currentNode的后继结点入队
            {
                if (visited[p->end] == false)
                    q.enQueue(p->end);
                p = p->next;
            }
        }
        cout << endl;
    }
}

/*--------------------------------------------------------欧拉路径-------------------------------------------------------------------------------*/

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(TypeOfVer start)
{
    //检查是否存在欧拉回路
    if (this->Edges == 0) //总的度为0
    {
        cout << "Euler circuit does not exist!" << endl;
        return;
    }
    for (int i = 0; i < this->Vers; ++i) //计算每个结点的度，并判断是否为偶数或者0
    {
        int numOfDegree;               //每个结点的度
        edgeNode *r = verList[i].head; //结点i的边
        while (r != NULL)
        {
            ++numOfDegree;
            r = r->next;
        }
        if (numOfDegree % 2)
        {
            cout << "Euler circuit does not exist!" << endl;
            return;
        }
    }

    verNode *tmp = clone;      //创建一份邻接表的副本
    int i = find(start);       //寻找起始结点的编号
    EulerNode *beg, *end;      //欧拉回路的起点和终点
    EulerCircuit(i, beg, end); //获取从i出发的路径，单链表路径的起点和终点的地址是beg和end

    EulerNode *p;
    while (true)
    {
        p = beg;
        while (p->next != NULL) //检查p的后继结点是否有边尚未被访问
        {
            if (verList[p->next->NodeNum].head != NULL)
                break;
            else
                p = p->next;

            if (p->next == NULL) //所有的边都已被访问
                break;

            //存在未被访问边的结点
            EulerNode *q, *tb, *te;
            q = p->next;
            EulerCircuit(q->NodeNum, tb, te); //从此结点开始找一段回路
            te->next = q->next;               //将搜索到的路径拼接到原来的路径上
            p->next = tb;
            delete q;
        }
    }

    //恢复原图
    delete[] verList;
    verList = tmp;

    //显示得到的欧拉回路并释放存储欧拉回路所占用的空间
    cout << "Euler circuit is:" << endl;
    while (beg != NULL)
    {
        cout << verList[beg->NodeNum].ver << '\t';
        p = beg;
        beg = beg->next;
        delete p;
    }

    cout << endl;
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::EulerCircuit(int start, EulerNode *&beg, EulerNode *&end)
{
    beg = end = new EulerNode(start); //将起始结点放入欧拉回路

    int nextNode;
    while (verList[start].head != NULL) //起始结点尚有边未被访问
    {
        nextNode = verList[start].head->end;
        remove(start, nextNode); //无向图需要删除两次
        remove(nextNode, start);
        start = nextNode;
        end->next = new EulerNode(start);
        end = end->next;
    }
}

//复制当前图的邻接表，返回保存结点数组的首地址
template <class TypeOfVer, class TypeOfEdge>
typename adjListGraph<TypeOfVer, TypeOfEdge>::verNode *adjListGraph<TypeOfVer, TypeOfEdge>::clone() const
{
    verNode *tmp = new verNode[this->Vers];
    edgeNode *p;

    for (int i = 0; i < this->Vers; ++i) //复制每个结点在邻接表中的信息
    {
        tmp[i].ver = verList[i].ver; //复制每个结点i的信息
        p = verList[i].head;
        while (p != NULL) //复制结点i对应的边的信息
        {
            tmp[i].head = new edgeNode(p->end, p->weight, tmp[i].head);
            p = p->next;
        }
    }
    return tmp;
}

/*------------------------------------------------------------拓扑排序----------------------------------------------------------------------*/

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
    //计算每个结点的入度
    int *inDegree = new int[this->Vers];
    edgeNode *p;
    for (int i = 0; i < this->Vers; ++i)
    {
        inDegree[i] = 0;
        for (p = verList[i].head; p != NULL; p = p->next)
            ++inDegree[p->end];
    }

    //将入读为0的结点入队
    linkQueue<int> q;
    for (int i = 0; i < this->Vers; ++i)
        if (inDegree[i] == 0)
            q.enQueue(i);

    //输出拓扑排序
    cout << "Top sort is:" << endl;
    int current;
    while (!q.isEmpty())
    {
        current = q.deQueue();
        cout << verList[current].ver << '\t';
        for (p = verList[current].head; p != NULL; p = p->next)
            if (--inDegree[p->end] == 0)
                q.enQueue(p->end);
    }
    cout << endl;
}

/*------------------------------------------------------------关键路径---------------------------------------------------------------------*/

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
    //找出拓扑序列，放入数组top
    int *inDegree = new int[this->Vers], *top = new int[this->Vers]; //top保存拓扑序列
    for (int i = 0; i < this->Vers; ++i)                             //计算每个结点的入度
    {
        inDegree[i] = 0;
        for (edgeNode *p = verList[i].head; p != NULL; p = p->next)
            ++inDegree[p->end];
    }

    //将入度为0的结点入队
    linkQueue<int> q;
    for (int i = 0; i < this->Vers; ++i)
        if (inDegree[i] == 0)
            q.enQueue(i);

    int k = 0;
    while (!q.isEmpty())
    {
        top[k] = q.deQueue();
        for (edgeNode *p = verList[top[k]].head; p != NULL; p = p->next)
            if (--inDegree[p->end] == 0)
                q.enQueue(p->end);
        ++k;
    }

    //找最早发生时间
    TypeOfEdge *ee = new TypeOfEdge[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
        ee[i] = 0;
    for (int i = 0; i < this->Vers; ++i)
    {
        for (edgeNode *p = verList[top[i]].head; p != NULL; p = p->next)
            if (ee[p->end] < ee[top[i]] + p->weight)
                ee[p->end] = ee[top[i]] + p->weight;
    }

    //找最晚发生时间
    TypeOfEdge *le = new TypeOfEdge[this->Vers];
    for (int i = 0; i < this->Vers; ++i)
        le[i] = 0;
    for (int i = this->Vers - 1; i >= 0; --i)
    {
        for (edgeNode *p = verList[top[i]].head; p != NULL; p = p->next)
            if (le[p->end] - p->weight < le[top[i]])
                le[top[i]] = le[p->end] - p->weight;
    }

    //找出关键路径
    for (int i = 0; i < this->Vers; ++i)
        if (le[top[i]] == ee[top[i]])
            cout << "(" << verList[top[i]].ver << "," << ee[top[i]] << ")";
}

/*----------------------------------------------------------最小生成树的实现------------------------------------------------------------------------*/

//Kruskal算法
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const
{
    //存储一个图的另外一种结构
    struct edgeKruskal
    {
        int beg, end;                               //一条边的起止点
        TypeOfEdge w;                               //边的权值
        bool operator<(const edgeKruskal &rp) const //重载比较边的权值大小的运算符
        {
            return w < rp.w;
        }
    };

    DisjointSet ds(Vers); //构建一个有节点数个元素的并查集

    //生成优先级队列
    priority_queue<edgeKruskal> pq; //优先级队列
    edgeNode *p;                    //原有的图的元素结构
    for (int i = 0; i < Vers; i++)
    {
        for (p = verList[i].head; p != NULL; p = p->next)
            if (i < p->end) //为了实现每条边只保存一次，只有当每条边的终节点的下标小于起始节点才保存
            {
                e.beg = i;       //将起始节点下标保存
                e.end = p->end;  //将终点下标保存
                e.w = p->weight; //保存该边的权值
                pq.enQueue(e);   //将边入队
            }
    }

    //开始归并
    int edgesAccepted = 0; //接受的边的条数
    int u, v;
    edgeKruskal e;                   //特殊存储结构的图
    while (edgesAccepted < Vers - 1) //最终的边数等于节点数-1
    {
        e = pq.deQueue(); //取出权值最小的边

        //对边的起止点进行搜寻，看看加入边十分会出现回路
        u = ds.Find(e.beg);
        v = ds.Find(e.end);

        if (u != v) //没有出现回路，将边加入
        {
            edgesAccepted++;                                                 //边数+1
            ds.Union(u, v);                                                  //将两个节点所在的集合合并
            cout << '(' << verList[e.beg] << ',' << verList[e.end] << ")\t"; //输出加入的边的信息
        }
    }
}

//Prim算法
template <class TypeOfVer, class TypeOfEdge> //此函数中以U为已经加入的点的集合，以V为全部点的集合
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const
{
    //专门用于Prim算法（主要服务于表示边的最小权值的数组，数组的下标表示节点的编号）
    struct edgePrim
    {
        TypeOfEdge lowestCost; //从U到V-U的边的权值最小值
        int startNode;         //该最小权值的边的起始节点下标
    };

    edgePrim *prim = new edgePrim[Vers]; //初始构建的数组个数和节点数相同
    bool *flag = new bool[Vers];         //对应的下标为true表示节点已经加入

    for (int i = 0; i < Vers; i++)
    {
        flag[i] = false;             //所有节点都未加入
        prim[i].lowestCost = noEdge; //初始化边的权值为无穷大
    }

    edgeNode *p;    //每个节点的边指向的另一端
    TypeOfEdge min; //边的权值的最小值
    int start = 0;  //start是开始节点的下标，这里准备将第一个元素加入到U
    for (int i = 0; i < Vers; i++)
    {
        for (p = verList[start].head; p != NULL; p = p->next) //寻找节点i的所有边
        {
            //边的另一个端点在V-U中，且该边的权值小于已经录入的权值，也即需要更新prim[i]
            if (!flag[p->end] && prim[p->end].lowestCost > p->weight)
            {
                prim[p->end].lowestCost = p->weight;
                prim[p->end].startNode = start;
            }

            flag[start] = true; //在更新完成后，将节点加入

            //在整个prim表格里面寻找下一个需要加入的节点
            min = noEdge;
            for (int j = 0; j < Vers; ++j) //寻找权值最小的边
                if (prim[j].lowestCost < min)
                {
                    min = prim[j].lowestCost;
                    start = j; //更新开始节点
                }

            //输出本次连接的两个端点的值（端点的编号就是[]里的）
            cout << '(' << verList[prim[start].startNode].ver << ',' << verList[start].ver << ")\t";
            prim[start].lowestCost = noEdge; //将已经被加入的节点的值设为无穷大
        }

        delete[] flag;
        delete[] prim;
    }
}

/*----------------------------------------------------------最短路径问题----------------------------------------------------------------------------*/
//非加权图最短路径问题
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::unweightedShortDistance(TypeOfVer start, TypeOfEdge noEdge) const
{
    linkQueue<int> q;
    TypeOfEdge *distance = new TypeOfEdge[Vers];
    int *prev = new int[Vers];
    int u, sNo;
    edgeNode *p;
    for (int i = 0; i < Vers; i++)
        distance[i] = noEdge;

    sNo = find(start);

    distance[sNo] = 0;
    prev[sNo] = sNo;
    q.enQueue(sNo);

    while (!q.isEmpty())
    {
        u = q.deQueue();
        for (p = verList[u].head; p != NULL; p = p->next)
            if (distance[p->end] == noEdge)
            {
                distance[p->end] = distance[u] + 1;
                prev[p->end] = u;
                q.enQueue(p->end);
            }
    }

    for (int i = 0; i < Vers; i++)
    {
        cout << "from " << start << " to " << verList[i].ver << "'s path is:" << endl;
        printPath(sNo, i, prev);
        cout << endl;
    }
}

template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(int start, int end, int prev[]) const
{
    if (start == end)
    {
        cout << verList[start].ver;
        return;
    }
    printPath(start, prev[end], prev);
    cout << "-" << verList[end].ver;
}

//加权图最短路径问题(dijkstra算法)
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Dijkstra(TypeOfVer start, TypeOfEdge noEdge) const
{
    TypeOfEdge *distance = new TypeOfEdge[Vers];
    int *prev = new int[Vers];
    bool *known = new bool[Vers];

    int u, sNo, i, j;
    edgeNode *p;
    TypeOfEdge min;

    for (i = 0; i < Vers; i++)
    {
        known[i] = false;
        distance[i] = noEdge;
    }

    sNo = find(start);

    distance[sNo] = 0;
    prev[sNo] = sNo;

    for (i = 1; i < Vers; i++)
    {
        min = noEdge;

        for (j = 0; j < Vers; j++)//课堂讨论，此处是大于0？
            if (!known[j] && distance[j] < min)
            {
                min = distance[j];
                u = j;
            }

        known[u] = true;
        for (p = verList[u].head; p != NULL; p = p->next)
            if (!known[p->end] && distance[p->end] > min + p->weight)
            {
                distance[p->end] = min + p->weight;
                prev[p->end] = u;
            }
    }

    for (i = 0; i < Vers; i++)
    {
        cout << "from " << start << " to " << verList[i].ver << "'s path is:" << endl;
        printPath(sNo, i, prev);
        cout << " length is " << distance[i] << endl;
    }
}

//所有顶点对的最短路径问题(floyd算法)
template <class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::Floyd() const
{
    TypeOfEdge **d = new TypeOfEdge *[Vers];
    int **prev = new int *[Vers];
    int i, j, k;

    for (i = 0; i < Vers; i++)
    {
        d[j] = new TypeOfEdge[Vers];
        prev[i] = new int[Vers];
        for (j = 0; j < Vers; j++)
        {
            d[i][j] = edge[i][j];
            prev[i][j] = (edge[i][j] != noEdge) ? i : -1;
        }
    }

    for (k = 0; k < Vers; k++)
        for (i = 0; i < Vers; ++i)
            for (j = 0; j < Vers; ++j)
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                    prev[i][j] = prev[k][j];
                }

    cout << "The shortest path's length is:" << endl;
    for (i = 0; i < Vers; i++)
    {
        cout << endl;
        for (j = 0; j < Vers; ++j)
            cout << d[i][j] << '\t';
    }

    cout << "The shortest path is:" << endl;
    for (i = 0; i < Vers; ++i)
    {
        cout << endl;
        for (j = 0; j < Vers; ++j)
            cout << prev[i][j] << '\t';
    }
}