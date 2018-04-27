
/**
 * C++�����
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
	T key;		// ��ֵ
	int npl;	// ��·������
	LeftistNode* left;
	LeftistNode* right;

	LeftistNode(T value, LeftistNode *l, LeftistNode *r)
		: key(value), npl(0), left(l), right(r) {}
};

template<class T>
class LeftistHeap
{
private:
	LeftistNode<T> *mRoot;		// ���ڵ�
public:
	LeftistHeap();
	~LeftistHeap();

	// ǰ����������
	void preOrder();
	// �������
	void inOrder();
	// �������
	void postOrder();

	// ��other������Ѻϲ���this��
	void merge(LeftistHeap<T>* other);
	// ���ڵ�(keyΪ�ڵ��ֵ)���뵽�������
	void insert(T key);
	// ɾ���ڵ㣬��ʵ���Ǹ��ڵ�
	void remove();

	// ���������
	void destroy();

	// ��ӡ�����
	void print();

private:
	// ǰ�����
	void preOrder(LeftistNode<T>* heap) const;
	// �������
	void inOrder(LeftistNode<T>* heap) const;
	// �������
	void postOrder(LeftistNode<T>* heap) const;

	// �����ڵ�x�ͽڵ�y
	void swapNode(LeftistNode<T> *& x, LeftistNode<T> *& y);
	// �ϲ������x�������y
	LeftistNode<T>* merge(LeftistNode<T> *& x, LeftistNode<T> *& y);
	// ���ڵ�z���뵽�����heap��
	LeftistNode<T>* insert(LeftistNode<T> *& heap, T key);
	// ɾ��������еĽڵ㣬���ر�ɾ���Ľڵ�
	LeftistNode<T>* remove(LeftistNode<T> *& heap);

	// ����
	void destroy(LeftistNode<T> *& heap);

	// ��ӡ
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

	// �ϲ�x��y�ǣ���x��Ϊ�ϲ�֮�����ĸ������ﱣ֤x��keyС��y��key
	if (x->key > y->key)
		swapNode(x, y);		// ��Ҫ����仰����

	// ��x���Һ��Ӻ�y�ϲ����ϲ�������ĸ���x���Һ���
	x->right = merge(x->right, y);

	// ���x������Ϊ�գ�����x�����ӵ�npl<�Һ��ӵ�npl,�򽻻�x�����Һ���
	if (x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode<T>* tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}

	// ���úϲ��������x��npl
	if (NULL == x->right || NULL == x->left )
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

// ��other����Ѻϲ���this��
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

	// �������������ϲ��������
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
 * key: �ڵ�ļ�ֵ
 * direction: 0����ʾ�ýڵ��Ǹ��ڵ�
 *			  -1����ʾ�ýڵ��������ڵ������
 *			  1����ʾ�ýڵ��������ڵ���Һ���
*/
template<class T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction)
{
	if (heap)
	{
		if (0 == direction)		// heap�Ǹ��ڵ�
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