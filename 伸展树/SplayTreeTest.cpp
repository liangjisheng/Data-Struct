
#include <iostream>
#include "SplayTree.h"

using std::cout;
using std::endl;

static int arr[]= { 10, 50, 40, 30, 20, 60 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	SplayTree<int>* tree = new SplayTree<int>();
	cout << "依次添加: ";
	int nLen = TBL_SIZE(arr);
	for (int i = 0; i < nLen; ++i)
	{
		cout << arr[i] << ' ';
		tree->insert(arr[i]);
	}

	cout << "\n前序遍历: ";
	tree->preOrder();

	cout << "\n中序遍历: ";
	tree->inOrder();

	cout << "\n后序遍历: ";
	tree->postOrder();
	cout << endl << endl;

	cout << "== 最小值: " << tree->minimum() << endl;
	cout << "== 最大值: " << tree->maximum() << endl;
	cout << "== 树的详细信息: " << endl;
	tree->print();
	cout << endl;

	int num = 30;
	cout << "\n旋转节点(" << num << ")为根节点";
	tree->splay(num);
	cout << "\n== 树的详细信息: " << endl;
	tree->print();
	cout << endl;

	tree->destroy();
	system("pause");
	return 0;
}