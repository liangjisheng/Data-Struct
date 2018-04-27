
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

	cout << "ǰ�����:" << endl;
	tree.PreorderTraverse();
	cout << "�������:" << endl;
	tree.InorderTraverse();
	cout << "�������:" << endl;
	tree.PostorderTraverse();
	cout << "������ȱ���:" << endl;
	tree.DepthFristSearch();
	cout << "������ȱ���:" << endl;
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