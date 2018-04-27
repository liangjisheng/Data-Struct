
#include <iostream>
#include "SplayTree.h"

using std::cout;
using std::endl;

static int arr[]= { 10, 50, 40, 30, 20, 60 };
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main()
{
	SplayTree<int>* tree = new SplayTree<int>();
	cout << "�������: ";
	int nLen = TBL_SIZE(arr);
	for (int i = 0; i < nLen; ++i)
	{
		cout << arr[i] << ' ';
		tree->insert(arr[i]);
	}

	cout << "\nǰ�����: ";
	tree->preOrder();

	cout << "\n�������: ";
	tree->inOrder();

	cout << "\n�������: ";
	tree->postOrder();
	cout << endl << endl;

	cout << "== ��Сֵ: " << tree->minimum() << endl;
	cout << "== ���ֵ: " << tree->maximum() << endl;
	cout << "== ������ϸ��Ϣ: " << endl;
	tree->print();
	cout << endl;

	int num = 30;
	cout << "\n��ת�ڵ�(" << num << ")Ϊ���ڵ�";
	tree->splay(num);
	cout << "\n== ������ϸ��Ϣ: " << endl;
	tree->print();
	cout << endl;

	tree->destroy();
	system("pause");
	return 0;
}