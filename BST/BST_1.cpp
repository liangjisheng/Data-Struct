
// BST��������(û�п����ڴ�й¶)
#include <iostream>

using namespace std;

//#define ERROR       0  
//#define OK          1  
//#define REEOR       1  
//#define INFEASIBLE -1  
//#define OVERFLOW   -2  
//typedef int Status;

typedef struct node
{
	int key;
	struct node *lChild, *rChild;
}Node, *BST;

bool BSTInsert(Node *&p, int element)
{
	if(NULL == p)
	{
		p = new Node;
		p->key = element;
		p->lChild = p->rChild = NULL;
		return true;
	}

	// ���BST�в���������ȵ�ֵ������Լ�������Ĵ���
	//if(element == p->key)
	//	return false;

	if(element < p->key)
		return BSTInsert(p->lChild, element);
	else
		return BSTInsert(p->rChild, element);
}

void createBST(Node *&T, int a[], int n)
{
	T = NULL;
	for(int i = 0; i < n; i++)
	{
		if(!BSTInsert(T, a[i]))
			break;
	}
}

void preOrderTraverse(BST T)
{
	if(T)
	{
		cout << T->key << ' ';
		preOrderTraverse(T->lChild);
		preOrderTraverse(T->rChild);
	}
}

void inOrderTraverse(BST T)
{
	if(T)
	{
		inOrderTraverse(T->lChild);
		cout << T->key << ' ';
		inOrderTraverse(T->rChild);
	}
}

void postOrderTraverse(BST T)
{
	if(T)
	{
		postOrderTraverse(T->lChild);
		postOrderTraverse(T->rChild);
		cout << T->key << ' ';
		//printf("%d ", T->key);
	}
}

BST searchBST(BST T, int key)
{
	if(T == NULL || T->key == key)
		return T;
	else if(key < T->key)
		return searchBST(T->rChild, key);
	else
		return searchBST(T->rChild, key);
}

// ����������ڵ�ɾ��(��ʵ�ֲ�����ȷ��)
bool Delete(Node *T)
{
	Node *pNode = NULL;
	if(!T->rChild)
	{
		// �ڵ�Tû��������
		pNode = T;
		T = T->lChild;
		free(pNode);
	}
	else if(!T->lChild)
	{
		// �ڵ�Tû��������
		pNode = T;
		T = T->rChild;
		free(pNode);
	}
	else
	{
		// �ڵ�T��������������Ϊ��
		pNode = T;
		Node *pre = pNode->lChild;
		// while������preָ��ɾ���ڵ�T��ǰ���ڵ�(�������)
		while(pre->rChild)
		{
			pNode = pre;
			pre = pre->rChild;
		}

		T->key = pre->key;
		if(pNode != T)
			pNode->rChild = pre->lChild;
		else
			pNode->lChild = pre->lChild;

		free(pre);
	}

	return true;
}

bool deleteBST(BST T, int key)
{
	if(!T)
		return false;
	else if(T->key == key)
		return Delete(T);
	else if(key < T->key)
		return deleteBST(T->rChild, key);
	else
		return deleteBST(T->rChild, key);
}

// ��������
void DestroyBST(BST T)
{
	if(T)
	{
		DestroyBST(T->lChild);
		DestroyBST(T->rChild);
		delete T;
	}
}


int main()
{
	int a[] = {4, 5, 2, 1, 0, 9, 3, 7, 6, 8, 0, 8};
	int nSize = sizeof(a) / sizeof(a[0]);
	BST T = NULL;

	createBST(T, a, nSize);

	cout << "ǰ�����:" << endl;
	preOrderTraverse(T);
	cout << endl;

	cout << "�������:" << endl;
	inOrderTraverse(T);
	cout << endl;

	cout << "�������:" << endl;
	postOrderTraverse(T);
	cout << endl;

	cout << endl;
	Node *p = searchBST(T, 9);
	if(p)
		cout << "9 in the BST" << endl;
	else
		cout << "9 not in the BST" << endl;

	cout << endl;
	cout << "insert -1" << endl;
	BSTInsert(T, -1);
	inOrderTraverse(T);
	cout << endl;

	//cout << endl;
	//if(deleteBST(T, 10))
	//	cout << "delete 10 success" << endl;
	//else
	//	cout << "delete 10 failed" << endl;
	//inOrderTraverse(T);
	//cout << endl;

	//cout << endl;
	//if(deleteBST(T, 5))
	//	cout << "delete 5 success" << endl;
	//else
	//	cout << "delete 5 failed" << endl;
	//inOrderTraverse(T);
	//cout << endl;

	system("pause");
	return 0;
}

