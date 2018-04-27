
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

	unsigned short Size();		// 总节点个数
	unsigned short Deep();		// 深度
	unsigned short Leaf();		// 叶子节点个数

	bool IsEmpty();

	void PreorderTraverse();		// 前序遍历
	void InorderTraverse();			// 中序遍历
	void PostorderTraverse();		// 后序遍历
	void DepthFristSearch();		// 深度优先遍历
	void BreadthFirstSearch();		// 广度优先遍历

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

// 下面的这个Remove的接口是错误的
// 函数默认是传值,指针也是一种类型(默认也是传值),所以这个里面的
// pNode是调用者传进来的一个拷贝,就和第一个参数x一样,x和pNode
// 都是一个局部变量,对pNode的操作除了delete之外都不会生效
// 删除后在遍历的时候,就会出现无效的访问数据和内存的非法访问
void BSTree::Remove(int x, Node* pNode)
{
	if(!pNode)					// 判断树是否为空
		return ;
	if(x < pNode->data)			// 查找要删除的节点
		Remove(x, pNode->lChild);
	else if(x > pNode->data)	// 查找要删除的节点
		Remove(x, pNode->rChild);
	else if(pNode->lChild && pNode->rChild)		// 被删除的节点有两个子节点
	{
		// 为了不破坏树的结构,需要找出一个节点来替换当前节点
		// 根据二叉树的特点，当前节点大于所有左子树，小于所有
		// 右子树，可以用左子树中最大的节点，或者右子树中最小
		// 的节点来替换当前节点，然后删除替换节点
		Node* pMin = pNode->rChild;
		// while循环查找当前节点右子树中最小的节点
		while(pMin->lChild)
			pMin = pMin->lChild;
		pNode->data = pMin->data;			// 替换当前节点
		Remove(pNode->data, pNode->rChild);	// 删除替换后的节点
	}
	else
	{
		// 被删除的节点只有一子节点或是叶子节点
		Node* pTmp = pNode;
		if(pNode->lChild)			// 被删除的节点之有左子节点
			pNode = pNode->lChild;
		else if(pNode->rChild)		// 被删除的节点只有右子节点
			pNode = pNode->rChild;
		else
			pNode = NULL;			// 被删除的节点是叶子节点

		delete pTmp;
		pTmp = NULL;
	}
}

// 下面的这个接口是正确的,第二个参数传都是Node*的指针类型
// 但是里面有一句话的实现是错误的Node* pCur = *pNode;
// 上面的那句话对于Node*类型来说发生了拷贝,类似于int a = b;
// ClassA A = a;
// 删除后在遍历的时候,就会出现无效的访问数据和内存的非法访问
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

