
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

	cout << "== 左倾堆(ha)中依次添加: ";
	for (i = 0; i < alen; ++i)
	{
		cout << a[i] << " ";
		ha->insert(a[i]);
	}
	cout << "\n== 左倾堆(ha)的详细信息: " << endl;
	ha->print();

	cout << "\n左倾堆(hb)中依次添加: ";
	for (i = 0; i < blen; ++i)
	{
		cout << b[i] << " ";
		hb->insert(b[i]);
	}
	cout << "\n== 左倾堆(hb)的详细信息: " << endl;
	hb->print();

	// 将hb合并到ha中
	ha->merge(hb);
	cout << "\n== 合并后的ha的详细信息: " << endl;
	ha->print();

	system("pause");
	return 0;
}