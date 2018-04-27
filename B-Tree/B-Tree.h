
/***********************************************************************
 * �ļ���: B-Tree.h
 * �ļ�����: B-Tree��
 * ����: ����ʥ 20171105
 * �汾�� 1.0
***********************************************************************/

#ifndef _BMT_H_
#define _BMT_H_

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

#define M 3			// ���Ľ���
typedef int KeyType;

struct Node
{
	int keynum;				// �ڵ��йؼ��ֵĸ���
	Node *parent;			// ���ڵ�
	KeyType key[M + 1];		// �洢�ؼ��֣�����Ϊ0�ĵ�Ԫ��ʹ��
	Node *ptr[M + 1];		// �洢ָ��

	Node() : keynum(0), parent(NULL)
	{
		for (int i = 0; i <= M; ++i)
		{
			key[i] = 0;
			ptr[i] = NULL;
		}
	}
};

class BTree
{
private:
	Node *head;
	// �ڽڵ�T�в��ҹؼ���K�������ڷ������������򷵻�0(0�ŵ�Ԫδʹ��)
	int search(Node *& T, KeyType K);
	// �ڽڵ�Ĺؼ��������в���һ���ؼ���
	void insert(Node *& T, int i, KeyType K, Node* rhs);
	// �ڵ����
	bool split(Node *& T, int s, Node*& rhs, KeyType& midK);
	// �½�һ���ڵ�
	bool newroot(Node*& T, Node*& lhs, KeyType midK, Node*& rhs);
	void RotateLeft(Node* parent, int idx, Node* cur, Node* rsilb);
	void RotateRight(Node *parent, int idx, Node* cur, Node* lsilb);
	void Merge(Node* parent, int idx, Node* lsilb, Node* cur);
	void DeleteBalance(Node* curNode);
	void Delete(Node* curNode, int curIdx);
public:
	BTree();
	Node* gethead();
	bool searchKey_BTree(KeyType K, Node*& recNode, int& recIdx);
	bool insert_BTree(KeyType K);
	bool Delete_BTree(KeyType K);
	void Destroy(Node *& T);
	void WalkThrough(Node *& T);
};



#endif // _BMT_H_