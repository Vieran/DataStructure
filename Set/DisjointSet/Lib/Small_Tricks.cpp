//生成迷宫的实现
//最近的共同祖先问题没有在这里实现，因为需要给定一棵树

/*
思路：单元之间的连通关系完全可以用等价来描述
1.开始时，所有的单元都是不连通的（每个单元是一个等价类）
2.随机选择两个相邻单元，判断两个的单元是否再一个等价类中
3.是则重新选择；否则敲开两个单元之间的墙，使之连通，归并两个等价类
4.重复2、3知道所有单元都再一个等价类中或者入口和出口在一个等价类中
*/

#include "DisjointSet.h"
#include <iostream>
#include <ctime>
using namespace std;

//参数size是迷宫的规模
void creatPuzzle(int size)
{
	int num1,num2;//保存相邻的两个单元的编号
	DisjointSet ds(size*size);//生成n*n的迷宫	
	srand(time(NULL));//生成随机数种子
	
	while(ds.Find(0) != ds.Find(size*size-1))//循环直到出口（size*size-1）和入口（0）连通
	{
		while(true)//随机选择两个不连通单元
		{
			num1 = rand()*size*size/(RAND_MAX+1);//生成0~size*size-1之间的随机数

			bool flag = false;//标记是否找到需要破除的墙
			num2 = rand()%3;//使用随机数来决定判断破除的墙是哪一个方向的
			switch(num2)
			{
				case 0:
			//检查上方元素
			num2 = num1-size;
			if(num2>0 && ds.Find(num1)!=ds.Find(num2))//num1不是最上方的元素，且上方单元不连通
				flag = true;
				break;
				
				case 1:
			//检查左方元素
			num2 = num1-1;
			if(num1%size!=0 && ds.Find(num1)!=ds.Find(num2))//num1不是左边界的元素，且和左方元素不连通
				flag = true;
				break;

				case 2:
			//检查右方元素
			num2 = num1+1;
			if(num1%size!=0 && ds.Find(num1)!=ds.Find(num2))//num1不是有边界元素，且和右方元素不连通
				flag = true;
				break;

				case 3:
			//检查下方元素
			num2 = num1+size;
			if(num2<size*size && ds.Find(num1)!=ds.Find(num2))//num1不是最下方的元素，且和下方元素不连通
				flag = true;
				break;
			}
			if(flag)
				break;
		}
		ds.Union(ds.Find(num1),ds.Find(num2));
		cout << '<' << num1 << ',' << num2 << '>';
	}
}

