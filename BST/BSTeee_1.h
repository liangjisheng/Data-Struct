
#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class BSTree
{
	struct Node
	{
		int data;
		struct Node* lChild;
		struct Node* rChild;
		Node(int x = 0) : data(x), lChild(NULL), rChild(NULL) {}
	};

public:
	BSTree();
	~BSTree();

	void Insert(int x);
	void Remove(int x);

	unsigned short Size();		// �ܽڵ����
	unsigned short Deep();		// ���
	unsigned short Leaf();		// Ҷ�ӽڵ����

	bool IsEmpty();

	void PreorderTraverse();		// ǰ�����
	void InorderTraverse();			// �������
	void PostorderTraverse();		// �������
	void DepthFristSearch();		// ������ȱ���
	void BreadthFirstSearch();		// ������ȱ���

private:
	void Remove(int x, Node** pNode);
	void Remove(int x, Node* pNode);

	unsigned short CountSize(Node* pNode);
	unsigned short CountDeep(Node* pNode);
	unsigned short CountLeaf(Node* pNode);

	void PreorderTraverse(Node* pNode);
	void InorderTraverse(Node* pNode);
	void PostorderTraverse(Node* pNode);
	void DepthFristSearch(Node* pNode);
	void BreadthFirstSearch(Node* pNode);

	void Free(Node* pNode);

	Node* m_root;
};

// ��������Remove�Ľӿ��Ǵ����
// ����Ĭ���Ǵ�ֵ,ָ��Ҳ��һ������(Ĭ��Ҳ�Ǵ�ֵ),������������
// pNode�ǵ����ߴ�������һ������,�ͺ͵�һ������xһ��,x��pNode
// ����һ���ֲ�����,��pNode�Ĳ�������delete֮�ⶼ������Ч
// ɾ�����ڱ�����ʱ��,�ͻ������Ч�ķ������ݺ��ڴ�ķǷ�����
void BSTree::Remove(int x, Node* pNode)
{
	if(!pNode)					// �ж����Ƿ�Ϊ��
		return ;
	if(x < pNode->data)			// ����Ҫɾ���Ľڵ�
		Remove(x, pNode->lChild);
	else if(x > pNode->data)	// ����Ҫɾ���Ľڵ�
		Remove(x, pNode->rChild);
	else if(pNode->lChild && pNode->rChild)		// ��ɾ���Ľڵ��������ӽڵ�
	{
		// Ϊ�˲��ƻ����Ľṹ,��Ҫ�ҳ�һ���ڵ����滻��ǰ�ڵ�
		// ���ݶ��������ص㣬��ǰ�ڵ����������������С������
		// �������������������������Ľڵ㣬��������������С
		// �Ľڵ����滻��ǰ�ڵ㣬Ȼ��ɾ���滻�ڵ�
		Node* pMin = pNode->rChild;
		// whileѭ�����ҵ�ǰ�ڵ�����������С�Ľڵ�
		while(pMin->lChild)
			pMin = pMin->lChild;
		pNode->data = pMin->data;			// �滻��ǰ�ڵ�
		Remove(pNode->data, pNode->rChild);	// ɾ���滻��Ľڵ�
	}
	else
	{
		// ��ɾ���Ľڵ�ֻ��һ�ӽڵ����Ҷ�ӽڵ�
		Node* pTmp = pNode;
		if(pNode->lChild)			// ��ɾ���Ľڵ�֮�����ӽڵ�
			pNode = pNode->lChild;
		else if(pNode->rChild)		// ��ɾ���Ľڵ�ֻ�����ӽڵ�
			pNode = pNode->rChild;
		else
			pNode = NULL;			// ��ɾ���Ľڵ���Ҷ�ӽڵ�

		delete pTmp;
		pTmp = NULL;
	}
}

// ���������ӿ�����ȷ��,�ڶ�������������Node*��ָ������
// ����������һ�仰��ʵ���Ǵ����Node* pCur = *pNode;
// ������Ǿ仰����Node*������˵�����˿���,������int a = b;
// ClassA A = a;
// ɾ�����ڱ�����ʱ��,�ͻ������Ч�ķ������ݺ��ڴ�ķǷ�����
//void BSTree::Remove(int x, Node** pNode)
//{
//	if (!pNode || !(*pNode))
//		return;
//
//	Node* pCur = *pNode;
//	if(x < pCur->data)
//		Remove(x, &(pCur->lChild));
//	else if(x > pCur->data)
//		Remove(x, &(pCur->rChild));
//	else if(pCur->lChild && pCur->rChild)
//	{
//		Node* pMin = pCur->rChild;
//		while(pMin->lChild)
//			pMin = pMin->lChild;
//		pCur->data = pMin->data;
//		Remove(pCur->data, &(pCur->rChild));
//	}
//	else
//	{
//		Node* pTmp = pCur;
//		if(pCur->lChild)
//			pCur = pCur->lChild;
//		else if(pCur->rChild)
//			pCur = pCur->rChild;
//		else
//			pCur = NULL;
//
//		delete pTmp;
//		pTmp = NULL;
//	}
//}

void BSTree::Remove(int x, Node** pNode)
{
	if(!pNode || !(*pNode))
		return ;

	if(x < (*pNode)->data)
		Remove(x, &((*pNode)->lChild));
	else if(x > (*pNode)->data)
		Remove(x, &((*pNode)->rChild));
	else if((*pNode)->lChild && (*pNode)->rChild)
	{
		Node* pMin = (*pNode)->rChild;
		while(pMin->lChild)
			pMin = pMin->lChild;
		(*pNode)->data = pMin->data;
		Remove((*pNode)->data, &((*pNode)->rChild));
	}
	else
	{
		Node* pTmp = *pNode;
		if((*pNode)->lChild)
			(*pNode) = (*pNode)->lChild;
		else if((*pNode)->rChild)
			(*pNode) = (*pNode)->rChild;
		else
			(*pNode) = NULL;

		delete pTmp;
		pTmp = NULL;
	}
}

unsigned short BSTree::CountSize(Node* pNode)
{
	if(!pNode)
		return 0;
	return CountSize(pNode->lChild) + CountSize(pNode->rChild) + 1;
}

unsigned short BSTree::CountDeep(Node* pNode)
{
	if(!pNode)
		return 0;
	unsigned short ldeep = CountDeep(pNode->lChild);
	unsigned short rdeep = CountDeep(pNode->rChild);
	return ldeep > rdeep ? ldeep + 1 : rdeep + 1;
}

unsigned short BSTree::CountLeaf(Node* pNode)
{
	if(!pNode)
		return 0;
	if(!pNode->lChild && !pNode->rChild)
		return 1;
	return CountLeaf(pNode->lChild) + CountLeaf(pNode->rChild);
}

void BSTree::PreorderTraverse(Node* pNode)
{
	if(pNode)
	{
		cout << pNode->data << ' ';
		PreorderTraverse(pNode->lChild);
		PreorderTraverse(pNode->rChild);
	}
}

void BSTree::InorderTraverse(Node* pNode)
{
	if(pNode)
	{
		InorderTraverse(pNode->lChild);
		cout << pNode->data << ' ';
		InorderTraverse(pNode->rChild);
	}
}

void BSTree::PostorderTraverse(Node* pNode)
{
	if(pNode)
	{
		PostorderTraverse(pNode->lChild);
		PostorderTraverse(pNode->rChild);
		cout << pNode->data << ' ';
	}
}

void BSTree::DepthFristSearch(Node* pNode)
{
	stack<Node *> pNodeStack;
	pNodeStack.push(pNode);
	Node* pTop = NULL;

	while(!pNodeStack.empty())
	{
		pTop = pNodeStack.top();
		cout << pTop->data << ' ';
		pNodeStack.pop();
		if(pTop->rChild)
			pNodeStack.push(pTop->rChild);
		if(pTop->lChild)
			pNodeStack.push(pTop->lChild);
	}
}

void BSTree::BreadthFirstSearch(Node* pNode)
{
	queue<Node *> pNodeQueue;
	pNodeQueue.push(pNode);
	Node* pFront = NULL;

	while(!pNodeQueue.empty())
	{
		pFront = pNodeQueue.front();
		pNodeQueue.pop();
		cout << pFront->data << ' ';
		if(pFront->lChild)
			pNodeQueue.push(pFront->lChild);
		if(pFront->rChild)
			pNodeQueue.push(pFront->rChild);
	}
}

void BSTree::Free(Node* pNode)
{
	if(pNode)
	{
		Free(pNode->lChild);
		Free(pNode->rChild);
		delete pNode;
		pNode = NULL;
	}
}

BSTree::BSTree() { m_root = NULL; }

BSTree::~BSTree() { Free(m_root); }

void BSTree::Insert(int x)
{
	Node* pTmp = new Node(x);
	if(!m_root)
		m_root = pTmp;
	else
	{
		Node* pre = m_root;
		Node* cur = m_root;
		while(cur)
		{
			pre = cur;
			cur = (x < cur->data) ? (cur->lChild) : (cur->rChild);
		}
		(x < pre->data) ? (pre->lChild = pTmp) : (pre->rChild = pTmp);
	}
}

void BSTree::Remove(int x)
{
	if(!m_root)
		return;
	// Remove(x, m_root);		// error
	Remove(x, &m_root);
}

unsigned short BSTree::Size() { return CountSize(m_root); }

unsigned short BSTree::Deep() { return CountDeep(m_root); }

unsigned short BSTree::Leaf() { return CountLeaf(m_root); }

bool BSTree::IsEmpty() { return m_root == NULL; }

void BSTree::PreorderTraverse()
{
	PreorderTraverse(m_root);
	cout << endl;
}

void BSTree::InorderTraverse()
{
	InorderTraverse(m_root);
	cout << endl;
}

void BSTree::PostorderTraverse()
{
	PostorderTraverse(m_root);
	cout << endl;
}

void BSTree::DepthFristSearch()
{
	DepthFristSearch(m_root);
	cout << endl;
}

void BSTree::BreadthFirstSearch()
{
	BreadthFirstSearch(m_root);
	cout << endl;
}

