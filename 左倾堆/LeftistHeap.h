
/**
 * C++左倾堆
*/

#ifndef _LEFTIST_TREE_HPP_
#define _LEFTIST_TREE_HPP_

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

template<class T>
class LeftistNode
{
public:
	T key;		// 键值
	int npl;	// 零路径长度
	LeftistNode* left;
	LeftistNode* right;

	LeftistNode(T value, LeftistNode *l, LeftistNode *r)
		: key(value), npl(0), left(l), right(r) {}
};

template<class T>
class LeftistHeap
{
private:
	LeftistNode<T> *mRoot;		// 根节点
public:
	LeftistHeap();
	~LeftistHeap();

	// 前序遍历左倾堆
	void preOrder();
	// 中序遍历
	void inOrder();
	// 后序遍历
	void postOrder();

	// 将other的左倾堆合并到this中
	void merge(LeftistHeap<T>* other);
	// 将节点(key为节点键值)插入到左倾堆中
	void insert(T key);
	// 删除节点，其实就是根节点
	void remove();

	// 销毁左倾堆
	void destroy();

	// 打印左倾堆
	void print();

private:
	// 前序遍历
	void preOrder(LeftistNode<T>* heap) const;
	// 中序遍历
	void inOrder(LeftistNode<T>* heap) const;
	// 后序遍历
	void postOrder(LeftistNode<T>* heap) const;

	// 交换节点x和节点y
	void swapNode(LeftistNode<T> *& x, LeftistNode<T> *& y);
	// 合并左倾堆x和左倾堆y
	LeftistNode<T>* merge(LeftistNode<T> *& x, LeftistNode<T> *& y);
	// 将节点z插入到左倾堆heap中
	LeftistNode<T>* insert(LeftistNode<T> *& heap, T key);
	// 删除左倾堆中的节点，返回被删除的节点
	LeftistNode<T>* remove(LeftistNode<T> *& heap);

	// 销毁
	void destroy(LeftistNode<T> *& heap);

	// 打印
	void print(LeftistNode<T>* heap, T key, int direction);
};


template<class T>
LeftistHeap<T>::LeftistHeap() : mRoot(NULL) {}

template<class T>
LeftistHeap<T>::~LeftistHeap() { destroy(mRoot); }

template<class T>
void LeftistHeap<T>::preOrder(LeftistNode<T>* heap) const
{
	if (heap)
	{
		cout << heap->key << " ";
		preOrder(heap->left);
		preOrder(heap->right);
	}
}

template<class T>
void LeftistHeap<T>::preOrder() { preOrder(mRoot); }

template<class T>
void LeftistHeap<T>::inOrder(LeftistNode<T>* heap) const
{
	if (heap)
	{
		inOrder(heap->left);
		cout << heap->key << " ";
		inOrder(heap->right);
	}
}

template<class T>
void LeftistHeap<T>::inOrder() { inOrder(mRoot); }

template<class T>
void LeftistHeap<T>::postOrder(LeftistNode<T>* heap) const
{
	if (heap)
	{
		postOrder(heap->left);
		postOrder(heap->right);
		cout << heap->key << " ";
	}
}

template<class T>
void LeftistHeap<T>::postOrder() { postOrder(mRoot); }

template<class T>
void LeftistHeap<T>::swapNode(LeftistNode<T> *& x, LeftistNode<T> *& y)
{
	LeftistNode<T>* tmp = x;
	x = y;
	y = tmp;
}

template<class T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T> *& x, LeftistNode<T> *& y)
{
	if (NULL == x)
		return y;
	if (NULL == y)
		return x;

	// 合并x和y是，将x作为合并之后树的根，这里保证x的key小于y的key
	if (x->key > y->key)
		swapNode(x, y);		// 主要是这句话交换

	// 将x的右孩子和y合并，合并后的树的根是x的右孩子
	x->right = merge(x->right, y);

	// 如果x的左孩子为空，或者x的左孩子的npl<右孩子的npl,则交换x的左右孩子
	if (x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode<T>* tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}

	// 设置合并后的新树x的npl
	if (NULL == x->right || NULL == x->left )
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

// 将other左倾堆合并到this中
template<class T>
void LeftistHeap<T>::merge(LeftistHeap<T>* other) { mRoot = merge(mRoot, other->mRoot); }

template<class T>
LeftistNode<T>* LeftistHeap<T>::insert(LeftistNode<T> *& heap, T key)
{
	LeftistNode<T>* node = new LeftistNode<T>(key, NULL, NULL);
	if (NULL == node)
	{
		cout << "ERROR: create node failed" << endl;
		return heap;
	}

	return merge(mRoot, node);
}

template<class T>
void LeftistHeap<T>::insert(T key) { mRoot = insert(mRoot, key); }

template<class T>
LeftistNode<T>* LeftistHeap<T>::remove(LeftistNode<T> *& heap)
{
	if (NULL == heap)
		return NULL;

	LeftistNode<T>* l = heap->left;
	LeftistNode<T>* r = heap->right;

	delete heap;

	// 返回左右子树合并后的新树
	return merge(l, r);
}

template<class T>
void LeftistHeap<T>::remove() { mRoot = remove(mRoot); }

template<class T>
void LeftistHeap<T>::destroy(LeftistNode<T> *& heap)
{
	if (!heap)
		return ;

	if (heap->left)
		destroy(heap->left);
	if (heap->right)
		destroy(heap->right);

	delete heap;
}

template<class T>
void LeftistHeap<T>::destroy() { destroy(mRoot); }

/*
 * key: 节点的键值
 * direction: 0，表示该节点是根节点
 *			  -1，表示该节点是它父节点的左孩子
 *			  1，表示该节点是它父节点的右孩子
*/
template<class T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction)
{
	if (heap)
	{
		if (0 == direction)		// heap是跟节点
			cout << setw(2) << heap->key << "(" << heap->npl << ") is root" << endl;
		else
			cout << setw(2) << heap->key << "(" << heap->npl << ") is " << setw(2) << key
				<< "'s " << setw(12) << ((direction == 1) ? "right child" : "left child") << endl;

		print(heap->left, heap->key, -1);
		print(heap->right, heap->key, 1);
	}
}

template<class T>
void LeftistHeap<T>::print() 
{
	if (mRoot)
		print(mRoot, mRoot->key, 0);
}

#endif // _LEFTIST_TREE_HPP_