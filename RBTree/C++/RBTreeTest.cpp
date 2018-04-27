
#include "RBTree.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	int check_insert = 1;	// "插入"动作的检测开关(0关闭;1打开)
	int check_remove = 1;	// "删除"动作的检测开关(0关闭;1打开)
	int i;
	int ilen = sizeof(a) / sizeof(a[0]);

	RBTree<int>* tree = new RBTree<int>();

	cout << "== 原始数据: " ;
	for (i = 0; i < ilen; ++i)
		cout << a[i] << ' ';
	cout << endl;

	for (i = 0; i < ilen; ++i)
	{
		tree->insert(a[i]);
		if(check_insert)
		{
			cout << "== 添加节点: " << a[i] << endl;
			cout << "== 树的详细信息: " << endl;
			tree->print();
			cout << endl;
		}
	}

	cout << "== 前序遍历: ";
	tree->preorder();
	cout << endl;

	cout << "== 中序遍历: ";
	tree->inorder();
	cout << endl;

	cout << "== 后序遍历: ";
	tree->postorder();
	cout << endl;
	cout << endl;

	if(check_remove)
	{
		for (i = 0; i < ilen; ++i)
		{
			tree->remove(a[i]);
			cout << "== 删除节点: " << a[i] << endl;
			cout << "== 树的详细信息: " << endl;
			tree->print();
			cout << endl;
		}
	}

	tree->destroy();

	system("pause");
	return 0;
}