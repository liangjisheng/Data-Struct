
/***********************************************************************
 * 文件名: B-Tree.h
 * 文件描述: B-Tree类
 * 作者: 梁基圣 20171105
 * 版本： 1.0
***********************************************************************/

#ifndef _BMT_H_
#define _BMT_H_

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

#define M 3			// 树的阶数
typedef int KeyType;

struct Node
{
	int keynum;				// 节点中关键字的个数
	Node *parent;			// 父节点
	KeyType key[M + 1];		// 存储关键字，索引为0的单元不使用
	Node *ptr[M + 1];		// 存储指针

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
	// 在节点T中查找关键字K，若存在返回索引，否则返回0(0号单元未使用)
	int search(Node *& T, KeyType K);
	// 在节点的关键字序列中插入一个关键字
	void insert(Node *& T, int i, KeyType K, Node* rhs);
	// 节点分裂
	bool split(Node *& T, int s, Node*& rhs, KeyType& midK);
	// 新建一个节点
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