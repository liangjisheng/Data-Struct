
#include "BST.h"
#include <cstdlib>
#include <ctime>
#include <cstdio>

int main()
{
	// ����׼������ض���out.txt�ļ���
	freopen("out.txt", "w", stdout);
	BiTree<int> bitree;
	srand(time(NULL));
	int n;
	cout << "input number of the tree:" << endl;
	cin >> n;	// ֱ������һ����
	clock_t start, finish;
	start = clock();
	for(int i = 0; i < n; i++)
		bitree.insert(rand() % n);
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	bitree.printTree();
	cout << endl;
	// bitree.display();
	cout << endl;

	BiTree<int> bitree1(bitree);
	cout << endl;
	for(int i = 0; i <= n / 2; i++)
		bitree1.remove(i);
	cout << bitree1 << endl;
	cout << endl;
	cout << bitree << endl;

	fclose(stdout);
	system("pause");
	return 0;
}