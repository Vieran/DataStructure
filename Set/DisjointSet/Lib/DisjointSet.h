//不相交集的头文件
//按规模归并和路径压缩实现

#include <iostream>
using namespace std;

#ifndef DISJOINTSET_H
#define DISJOINTSET_H


class DisjointSet
{
	private:
		int size;//集合的大小
		int *parent;//双亲表示法的数组
	public:
		DisjointSet(int s);
		~DisjointSet()
		{
			delete [] parent;
		}
		void Union(int root1,int root2);//合并根节点为root1和root2的两个集合
		int Find(int x);//找到元素x所在的集合
}; 
#endif


//根据集合大小构建集合
DisjointSet::DisjointSet(int n)
{
	size = n;
	parent = new int [size];//申请存储的空间
	for(int i=0;i<size;++i)//每个元素都是独立的
		parent[i] = -1;//每个子集只有其自身一个元素
}

//查找操作
//递归实现路径压缩的方法
int DisjointSet::Find(int x)
{
	if(parent[x]<0)
		return x;
	return parent[x]=Find(parent[x]);//利用递归的方式，将根节点的值赋给路径上的每一个节点
}

//归并操作
//按规模归并
void DisjointSet::Union(int root1,int root2)
{
	if(root1==root2)//同一个子集，则不必进行归并
		return;
	
	//将规模小的子集归并到规模大的子集中（根节点是用负值表示的）
	if(parent[root1]>parent[root2]){
		parent[root2] += parent[root1];//更新根节点的数值（子集中元素的个数）
		parent[root1] = root2;
	}
	else{
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}
