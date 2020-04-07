#include "Tree.h"
#include "BinaryTree.h"
#include "Small_Trick.h"

int main()
{
    /*cout << "Input flag for NULL:";//创建表示空的符号
    char flag;
    cin >> flag;

    BinaryTree<char> tree;
    tree.creatTree(flag);
    tree.preOrder();//前序遍历
    tree.midOrder();//中序遍历
    tree.postOrder();//后序遍历
    printTree(tree,flag);//打印树

    cout << "Please input the node which you want to delete it's left side:";
    char left;
    cin >> left;
    tree.delLeft(left);

    cout << "Please input the node which you want to delete it's right side:";
    char right;
    cin >> right;
    tree.delLeft(right);

    //表达式树
    cout << "Please input the expression you want to calculate:";
    char expression[30];
    cin.get();//除去回车符号
    cin.getline(expression,30);
    Calc exp(expression);
    cout << "The result is " << exp.result() << endl;

    //哈夫曼树
    int length;
    cout << "Please input the length of your string:";
    cin >> length;

    
    char *str = new char[length+1];
    cout << "Please input the string:";
    cin.get();//除去多余的回车
    cin.getline(str,length+1);//getline函数获取字符串后，会在给定的个数最后一个放置\0

    int *weight = new int[length];
    cout << "Please input the weigth of the string:";
    for(int i=0;i<length;++i)
        cin >> weight[i];

    hfTree<char> hftree(str,weight,length);
    hfTree<char>::hfCode result[7];//创建类型数组，在编译前必须是常量，否则运行时出错（改变length时要注意改变这个）
    hftree.getCode(result);

    for(int k=0;k<length;++k)
        cout << result[k].data << " " << result[k].code << endl;

    delete [] str;
    delete [] weight;*/

    BinaryTree<int> a(1);

    return 0;
}