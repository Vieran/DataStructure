/*基于邻接表的图类的定义*/

#include "Graph.h"
#include "linkQueue.h"
#include <iostream>
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
    int *inDegree = new int[this->Vers],*top = new int[this->Vers];//top保存拓扑序列
    for (int i = 0; i < this->Vers; ++i)//计算每个结点的入度
    {
        inDegree[i] = 0;
        for(edgeNode *p=verList[i].head;p!=NULL;p = p->next)
            ++inDegree[p->end];
    }

    //将入度为0的结点入队
    linkQueue<int> q;
    for(int i= 0;i < this->Vers;++i)
        if(inDegree[i]==0)
            q.enQueue(i);
    
    int k=0;
    while (!q.isEmpty())
    {
        top[k] = q.deQueue();
        for(edgeNode *p = verList[top[k]].head;p!=NULL;p = p->next)
            if(--inDegree[p->end]==0)
                q.enQueue(p->end);
        ++k;
    }
    
    //找最早发生时间
    TypeOfEdge *ee = new TypeOfEdge[this->Vers];
    for(int i= 0;i < this->Vers;++i)
        ee[i] = 0;
    for (int i = 0; i < this->Vers; ++i)
    {
        for(edgeNode *p=verList[top[i]].head;p!=NULL;p = p->next)
            if(ee[p->end] < ee[top[i]]+p->weight)
                ee[p->end] = ee[top[i]]+p->weight;
    }

    //找最晚发生时间
    TypeOfEdge *le = new TypeOfEdge[this->Vers];
    for(int i= 0;i < this->Vers;++i)
        le[i] = 0;
    for (int i = this->Vers-1; i >= 0; --i)
    {
        for(edgeNode *p=verList[top[i]].head;p!=NULL;p = p->next)
            if(le[p->end]-p->weight< le[top[i]])
                le[top[i]] = le[p->end]-p->weight;
    }
    
    //找出关键路径
    for(int i = 0; i< this->Vers;++i)
        if(le[top[i]] == ee[top[i]])
            cout << "(" << verList[top[i]].ver << "," << ee[top[i]] << ")";

}