
// http://www.cnblogs.com/skywang12345/p/3638342.html
#include "LeftistHeap.h"

int main()
{
	int i = 0;
	int a[]= { 10, 40, 24, 30, 36, 20, 12, 16 };
	int b[]= {17, 13, 11, 15, 19, 21, 23};
	int alen = sizeof(a) / sizeof(a[0]);
	int blen = sizeof(b) / sizeof(b[0]);
	LeftistHeap<int>* ha = new LeftistHeap<int>();
	LeftistHeap<int>* hb = new LeftistHeap<int>();

	cout << "== �����(ha)���������: ";
	for (i = 0; i < alen; ++i)
	{
		cout << a[i] << " ";
		ha->insert(a[i]);
	}
	cout << "\n== �����(ha)����ϸ��Ϣ: " << endl;
	ha->print();

	cout << "\n�����(hb)���������: ";
	for (i = 0; i < blen; ++i)
	{
		cout << b[i] << " ";
		hb->insert(b[i]);
	}
	cout << "\n== �����(hb)����ϸ��Ϣ: " << endl;
	hb->print();

	// ��hb�ϲ���ha��
	ha->merge(hb);
	cout << "\n== �ϲ����ha����ϸ��Ϣ: " << endl;
	ha->print();

	system("pause");
	return 0;
}