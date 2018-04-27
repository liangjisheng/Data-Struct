
#include "B-Tree.h"

#define BMT_TEST
#ifdef BMT_TEST

//BMT: 10 45 24 53 90 3 37 50 61 70 100
using std::cin;

int main(void)
{
	BTree t;

	int n;
	cout << "�������ĸ�����" << endl;
	cin >> n;
	cout << "�����������ֵ��" << endl;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		t.insert_BTree(temp);
	}
	Node * head = t.gethead();
	t.WalkThrough(head);

	int key;
	cout << "������Ҫɾ����ֵ��" << endl;
	cin >> key;
	t.Delete_BTree(key);
	head = t.gethead();
	t.WalkThrough(head);

	return 0;
}
#endif