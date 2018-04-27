
#include "RBTree.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	int check_insert = 1;	// "����"�����ļ�⿪��(0�ر�;1��)
	int check_remove = 1;	// "ɾ��"�����ļ�⿪��(0�ر�;1��)
	int i;
	int ilen = sizeof(a) / sizeof(a[0]);

	RBTree<int>* tree = new RBTree<int>();

	cout << "== ԭʼ����: " ;
	for (i = 0; i < ilen; ++i)
		cout << a[i] << ' ';
	cout << endl;

	for (i = 0; i < ilen; ++i)
	{
		tree->insert(a[i]);
		if(check_insert)
		{
			cout << "== ��ӽڵ�: " << a[i] << endl;
			cout << "== ������ϸ��Ϣ: " << endl;
			tree->print();
			cout << endl;
		}
	}

	cout << "== ǰ�����: ";
	tree->preorder();
	cout << endl;

	cout << "== �������: ";
	tree->inorder();
	cout << endl;

	cout << "== �������: ";
	tree->postorder();
	cout << endl;
	cout << endl;

	if(check_remove)
	{
		for (i = 0; i < ilen; ++i)
		{
			tree->remove(a[i]);
			cout << "== ɾ���ڵ�: " << a[i] << endl;
			cout << "== ������ϸ��Ϣ: " << endl;
			tree->print();
			cout << endl;
		}
	}

	tree->destroy();

	system("pause");
	return 0;
}