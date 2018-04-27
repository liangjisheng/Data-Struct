
// test for BSTree
#include <iostream>
#include <cstdlib>
#include "BSTeee.h"

using namespace std;

int main()
{
	BSTree tree;
	int arr[] = {5, 4, 8, 1, 7, 10};
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		tree.Insert(arr[i]);

	cout << "前序遍历:" << endl;
	tree.PreorderTraverse();
	cout << "中序遍历:" << endl;
	tree.InorderTraverse();
	cout << "后序遍历:" << endl;
	tree.PostorderTraverse();
	cout << "深度优先遍历:" << endl;
	tree.DepthFristSearch();
	cout << "广度优先遍历:" << endl;
	tree.BreadthFirstSearch();
	cout << endl;

	cout << "Remove 4" << endl;
	tree.Remove(4);
	tree.PreorderTraverse();
	cout << endl;

	cout << "Remove 5" << endl;
	tree.Remove(5);
	tree.PreorderTraverse();
	cout << endl;

	cout << "Remove 1" << endl;
	tree.Remove(1);
	tree.PreorderTraverse();
	cout << endl;

	cout << "Remove 8" << endl;
	tree.Remove(8);
	tree.PreorderTraverse();
	cout << endl;

	cout << "Remove 7" << endl;
	tree.Remove(7);
	tree.PreorderTraverse();
	cout << endl;

	cout << "Remove 10" << endl;
	tree.Remove(10);
	tree.PreorderTraverse();
	cout << endl;

	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		tree.Insert(arr[i]);
	for(int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << "Remove " << arr[i] << endl;
		tree.Remove(arr[i]);
		tree.PreorderTraverse();
		cout << endl;
	}

	system("pause");
	return 0;
}