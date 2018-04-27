
// ��չ��(Splay Tree)��һ�ֶ�����������������O(log n)�����
// ���롢���Һ�ɾ������������Daniel Sleator��Robert Tarjan���졣
// ��չ�����ڶ�����������������кͶ��������һ��������
// ����ӵ�ж��������������֮�⣬��չ�������е�һ���ص��ǣ�
// ��ĳ���ڵ㱻����ʱ����չ����ͨ����תʹ�ýڵ��Ϊ����
// �������ĺô��ǣ��´�Ҫ���ʸýڵ�ʱ���ܹ�Ѹ�ٵķ��ʵ��ýڵ�

// ������Ҫ��һ�����������ִ��һϵ�еĲ��Ҳ�����Ϊ��ʹ��������
// ʱ���С������Ƶ�ʸߵ���Щ��Ŀ��Ӧ���������ڿ���������λ�á�
// �����뵽���һ���򵥷�������ÿ�β���֮����������ع���
// �ѱ����ҵ���Ŀ���Ƶ���������һЩ�ĵط�����չ��Ӧ�˶�����
// ����һ���Ե�����ʽ�Ķ�����������������Ŵ�ĳ���ڵ㵽����֮���·��
// ͨ��һϵ�е���ת������ڵ���Ƶ�����ȥ

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
	T key;                // �ؼ���(��ֵ)
	SplayTreeNode *left;    // ����
	SplayTreeNode *right;    // �Һ���

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

	// ǰ�����
	void preOrder();
	// �������
	void inOrder();
	// �������
	void postOrder();

	// (�ݹ�ʵ��)����"��չ��"�м�ֵΪkey�Ľڵ�
	SplayTreeNode<T>* search(T key);
	// (�ǵݹ�ʵ��)����"��չ��"�м�ֵΪkey�Ľڵ�
	SplayTreeNode<T>* iterativeSearch(T key);

	T minimum();
	T maximum();

	// ��תkey��Ӧ�Ľڵ�Ϊ���ڵ㣬������ֵΪ���ڵ�
	// (a): ��չ���д��ڼ�ֵΪkey�Ľڵ㣬����ֵΪkey�Ľڵ���תΪ���ڵ�
	// (b): ��չ���в����ڼ�ֵΪkey�Ľڵ㣬��key < tree->key
	//	  b - 1: ����ֵΪkey�Ľڵ��ǰ���ڵ���ڵĻ�������ֵΪkey��ǰ���ڵ���תΪ���ڵ�
	//    b - 2: ����ֵΪkey�Ľڵ��ǰ���ڵ㲻���ڵĻ�������ζ��
	//			 key�������κμ�ֵ��С����ô��ʱ����С�ڵ㽫��תΪ���ڵ�
	// (c): ��չ���в����ڼ�ֵΪkey�Ľڵ㣬��key > tree->key
	//    c - 1: ��ֵΪkey�Ľڵ�ĺ�̽ڵ���ڵĻ�������ֵΪkey�ĺ�̽ڵ���תΪ���ڵ�
	//    c - 2: ��ֵΪkey�Ľڵ�ĺ�̽ڵ㲻���ڵĻ�������ζ��
	//			 key�������κμ�ֵ������ô��ʱ�����ڵ㽫��תΪ���ڵ�
	void splay(T key);

	// ����
	void insert(T key);
	// ɾ��
	void remove(T key);
	// ����
	void destroy();
	// ��ӡ��չ��
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

	// tree: �ڵ�,key: �ڵ�ļ�ֵ
	// direction: 0��ʾ���ڵ�,-1��ʾ�ýڵ������ĸ��ڵ������,1��ʾ�ýڵ������ĸ��ڵ���Һ���
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
			cout << "�����������ͬ�ڵ�(" << z->key << ")!" << endl;
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
		// ��tree��ǰ���ڵ���תΪ���ڵ�
		x = splay(tree->left, key);
		// ɾ��tree�ڵ�
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