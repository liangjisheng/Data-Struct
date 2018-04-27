
// 伸展树(Splay Tree)是一种二叉排序树，它能在O(log n)内完成
// 插入、查找和删除操作。它由Daniel Sleator和Robert Tarjan创造。
// 伸展树属于二叉查找树，即它具有和二叉查找树一样的性质
// 除了拥有二叉查找树的性质之外，伸展树还具有的一个特点是：
// 当某个节点被访问时，伸展树会通过旋转使该节点成为树根
// 这样做的好处是，下次要访问该节点时，能够迅速的访问到该节点

// 假设想要对一个二叉查找树执行一系列的查找操作。为了使整个查找
// 时间更小，被查频率高的那些条目就应当经常处于靠近树根的位置。
// 于是想到设计一个简单方法，在每次查找之后对树进行重构，
// 把被查找的条目搬移到离树根近一些的地方。伸展树应运而生，
// 它是一种自调整形式的二叉查找树，它会沿着从某个节点到树根之间的路径
// 通过一系列的旋转把这个节点搬移到树根去

#ifndef _SPLAY_TREE_HPP_
#define _SPLAY_TREE_HPP_

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

template <class T>
class SplayTreeNode
{
public:
	T key;                // 关键字(键值)
	SplayTreeNode *left;    // 左孩子
	SplayTreeNode *right;    // 右孩子

	SplayTreeNode():left(NULL),right(NULL) {}

	SplayTreeNode(T value, SplayTreeNode *l, SplayTreeNode *r) :
	key(value), left(l),right(r) {}
};

template<class T>
class SplayTree
{
private:
	SplayTreeNode<T> *root;
public:
	SplayTree();
	~SplayTree();

	// 前序遍历
	void preOrder();
	// 中序遍历
	void inOrder();
	// 后序遍历
	void postOrder();

	// (递归实现)查找"伸展树"中键值为key的节点
	SplayTreeNode<T>* search(T key);
	// (非递归实现)查找"伸展树"中键值为key的节点
	SplayTreeNode<T>* iterativeSearch(T key);

	T minimum();
	T maximum();

	// 旋转key对应的节点为根节点，并返回值为根节点
	// (a): 伸展树中存在键值为key的节点，将键值为key的节点旋转为根节点
	// (b): 伸展树中不存在键值为key的节点，且key < tree->key
	//	  b - 1: 若键值为key的节点的前驱节点存在的话，将键值为key的前驱节点旋转为根节点
	//    b - 2: 若键值为key的节点的前驱节点不存在的话，则意味着
	//			 key比树中任何键值都小，那么此时将最小节点将旋转为根节点
	// (c): 伸展树中不存在键值为key的节点，且key > tree->key
	//    c - 1: 键值为key的节点的后继节点存在的话，将键值为key的后继节点旋转为根节点
	//    c - 2: 键值为key的节点的后继节点不存在的话，则意味着
	//			 key比树中任何键值都大，那么此时将最大节点将旋转为根节点
	void splay(T key);

	// 插入
	void insert(T key);
	// 删除
	void remove(T key);
	// 销毁
	void destroy();
	// 打印伸展树
	void print();

private:
	void preOrder(SplayTreeNode<T>* tree) const;
	void inOrder(SplayTreeNode<T>* tree) const;
	void postOrder(SplayTreeNode<T>* tree) const;

	SplayTreeNode<T>* search(SplayTreeNode<T>* x, T key) const;
	SplayTreeNode<T>* iterativeSearch(SplayTreeNode<T>* x, T key) const;

	SplayTreeNode<T>* minimum(SplayTreeNode<T>* tree);
	SplayTreeNode<T>* maximum(SplayTreeNode<T>* tree);

	SplayTreeNode<T>* splay(SplayTreeNode<T>* tree, T key);
	SplayTreeNode<T>* insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z);
	SplayTreeNode<T>* remove(SplayTreeNode<T>* &tree, T key);
	void destroy(SplayTreeNode<T>* &tree);

	// tree: 节点,key: 节点的键值
	// direction: 0表示根节点,-1表示该节点是它的父节点的左孩子,1表示该节点是它的父节点的右孩子
	void print(SplayTreeNode<T>* tree, T key, int direction);
};

template<class T>
SplayTree<T>::SplayTree() : root(NULL) {}

template<class T>
SplayTree<T>::~SplayTree() { destroy(root); }

template<class T>
void SplayTree<T>::preOrder(SplayTreeNode<T>* tree) const
{
	if(tree)
	{
		cout << tree->key << ' ';
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void SplayTree<T>::preOrder() { preOrder(root); }

template <class T>
void SplayTree<T>::inOrder(SplayTreeNode<T>* tree) const
{
	if(tree)
	{
		inOrder(tree->left);
		cout << tree->key << " " ;
		inOrder(tree->right);
	}
}

template <class T>
void SplayTree<T>::inOrder() { inOrder(root); }

template <class T>
void SplayTree<T>::postOrder(SplayTreeNode<T>* tree) const
{
	if(tree != NULL)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout<< tree->key << " " ;
	}
}

template <class T>
void SplayTree<T>::postOrder() { postOrder(root); }

template <class T>
SplayTreeNode<T>* SplayTree<T>::search(SplayTreeNode<T>* x, T key) const
{
	if(x == NULL || x->key == key)
		return x;

	if(key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::search(T key) { return search(root, key); }

template <class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(SplayTreeNode<T>* x, T key) const
{
	while(x && x->key != key)
	{
		if(key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::iterativeSearch(T key) { return iterativeSearch(root, key); }

template <class T>
SplayTreeNode<T>* SplayTree<T>::minimum(SplayTreeNode<T>* tree)
{
	if(!tree)
		return NULL;

	while(tree->left)
		tree = tree->left;
	return tree;
}

template <class T>
T SplayTree<T>::minimum()
{
	SplayTreeNode<T> *p = minimum(root);
	if(p)
		return p->key;
	return (T)NULL;
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::maximum(SplayTreeNode<T>* tree)
{
	if(!tree)
		return NULL;

	while(tree->right)
		tree = tree->right;
	return tree;
}

template <class T>
T SplayTree<T>::maximum() 
{
	SplayTreeNode<T> *p = maximum(root);
	if(p)
		return p->key;
	return (T)NULL;
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::splay(SplayTreeNode<T>* tree, T key)
{
	SplayTreeNode<T> N, *l, *r, *c;

	if (tree == NULL) 
		return tree;

	N.left = N.right = NULL;
	l = r = &N;

	for (;;)
	{
		if (key < tree->key)
		{
			if (tree->left == NULL)
				break;
			if (key < tree->left->key)
			{
				c = tree->left;                           /* rotate right */
				tree->left = c->right;
				c->right = tree;
				tree = c;
				if (tree->left == NULL) 
					break;
			}
			r->left = tree;                               /* link right */
			r = tree;
			tree = tree->left;
		}
		else if (key > tree->key)
		{
			if (tree->right == NULL) 
				break;
			if (key > tree->right->key) 
			{
				c = tree->right;                          /* rotate left */
				tree->right = c->left;
				c->left = tree;
				tree = c;
				if (tree->right == NULL) 
					break;
			}
			l->right = tree;                              /* link left */
			l = tree;
			tree = tree->right;
		}
		else
			break;
	}

	l->right = tree->left;                                /* assemble */
	r->left = tree->right;
	tree->left = N.right;
	tree->right = N.left;

	return tree;
}

template <class T>
void SplayTree<T>::splay(T key) { root = splay(root, key); }

template <class T>
SplayTreeNode<T>* SplayTree<T>::insert(SplayTreeNode<T>* &tree, SplayTreeNode<T>* z)
{
	SplayTreeNode<T> *pre = NULL;
	SplayTreeNode<T> *cur = tree;

	while(cur)
	{
		pre = cur;
		if(z->key < cur->key)
			cur = cur->left;
		else if(z->key > cur->key)
			cur = cur->right;
		else
		{
			cout << "不允许插入相同节点(" << z->key << ")!" << endl;
			delete z;
			return tree;
		}
	}

	if(pre == NULL)
		tree = z;
	else if(z->key < pre->key)
		pre->left = z;
	else
		pre->right = z;

	return tree;
}

template <class T>
void SplayTree<T>::insert(T key)
{
	SplayTreeNode<T> *z = new SplayTreeNode<T>(key, NULL, NULL);
	if(!z)
		return ;

	root = insert(root, z);
	root = splay(root, key);
}

template <class T>
SplayTreeNode<T>* SplayTree<T>::remove(SplayTreeNode<T>* &tree, T key)
{
	SplayTreeNode<T> *x = NULL;
	if(tree == NULL)
		return NULL;

	if(search(root, key) == NULL)
		return tree;

	tree = splay(tree, key);
	if(tree->left)
	{
		// 将tree的前驱节点旋转为根节点
		x = splay(tree->left, key);
		// 删除tree节点
		x->right = tree->right;
	}
	else
		x = tree->right;

	delete tree;
	return x;
}

template <class T>
void SplayTree<T>::remove(T key) { root = remove(root, key); }

template <class T>
void SplayTree<T>::destroy(SplayTreeNode<T>* &tree)
{
	if(!tree)
		return ;

	if(tree->left)
		destroy(tree->left);
	if(tree->right)
		destroy(tree->right);
	delete tree;
}

template <class T>
void SplayTree<T>::destroy() 
{ 
	if(root)
		destroy(root);
}

template <class T>
void SplayTree<T>::print(SplayTreeNode<T>* tree, T key, int direction)
{
	if(tree)
	{
		if(0 == direction)
			cout << setw(2) << tree->key << " is root" << endl;
		else
			cout << setw(2) << tree->key << " is " << setw(2) << key << "'s "
				<< setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template <class T>
void SplayTree<T>::print()
{
	if(root)
		print(root, root->key, 0);
}

#endif // _SPLAY_TREE_HPP_