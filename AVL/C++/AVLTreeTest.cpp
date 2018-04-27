
#include "AVLTree.h"
#include <iostream>

using namespace std;

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};

#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

int main()
{
	AVLTree<int>* tree = new AVLTree<int>();
	cout << "�������: ";
	int ilen = TBL_SIZE(arr);
	for(int i = 0; i < ilen; i++)
	{
		cout << arr[i] << ' ';
		tree->insert(arr[i]);
	}

	cout << "\n== ǰ�����: ";
	tree->preOrder();

	cout << "\n== �������: ";
	tree->inOrder();

	cout << "\n== �������: ";
	tree->postOrder();
	cout << endl;
	cout << endl;

	cout << "== �߶�: " << tree->Height() << endl;
	cout << "== ��Сֵ: " << tree->minimum() << endl;
	cout << "== ���ֵ: " << tree->maximum() << endl;
	cout << "== ������ϸ��Ϣ: " << endl;
	tree->print();
	cout << endl;

	cout << "ɾ���ڵ�: " << 8;
	tree->remove(8);

	cout << "\n== �߶ȣ�" << tree->Height() << endl;
	cout << "\n== �������: ";
	tree->inOrder();
	cout << "\n== ������ϸ��Ϣ: " << endl;
	tree->print();

	tree->destroy();
	system("pause");
	return 0;
}

