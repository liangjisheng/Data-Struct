
#ifndef _AVL_TREE_HPP_
#define _AVL_TREE_HPP_

#include <iostream>
#include <iomanip>

using namespace std;

template<class T>
class AVLTreeNode
{
public:
	T key;
	int height;
	AVLTreeNode *left;
	AVLTreeNode *right;
	AVLTreeNode(T value, AVLTreeNode *l, AVLTreeNode *r)
		: key(value), height(0), left(l), right(r) {}
};

template<class T>
class AVLTree
{
private:
	AVLTreeNode<T> *root;	// 根节点

public:
	AVLTree();
	~AVLTree();

	// 获取树的高度
	int Height();
	// 求最大值
	int max(int a, int b);

	// 前序遍历
	void preOrder();
	// 中序遍历
	void inOrder();
	// 后序遍历
	void postOrder();

	// 递归查找键值为key的节点
	AVLTreeNode<T>* search(T key);
	// 非递归查找键值为key的节点
	AVLTreeNode<T>* iterativeSearch(T key);

	// 返回最小节点的键值
	T minimum();
	// 返回最大节点的键值
	T maximum();

	// 将节点(key为节点键值)插入到avl树中
	void insert(T key);
	// 删除节点
	void remove(T key);
	// 销毁avl树
	void destroy();
	// 打印avl树
	void print();

private:
	int Height(AVLTreeNode<T>* tree);

	void preOrder(AVLTreeNode<T>* tree) const;
	void inOrder(AVLTreeNode<T>* tree) const;
	void postOrder(AVLTreeNode<T>* tree) const;

	AVLTreeNode<T>* search(AVLTreeNode<T>* tree, T key) const;
	AVLTreeNode<T>* iterativeSearch(AVLTreeNode<T>* tree, T key) const;

	AVLTreeNode<T>* minimum(AVLTreeNode<T>* tree);
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* tree);

	// LL:左左对应的情况(左单旋转)
	AVLTreeNode<T>* leftLeftRotation(AVLTreeNode<T>* tree);
	// RR:右右对应的情况(右单旋转)
	AVLTreeNode<T>* rightRightRotation(AVLTreeNode<T>* tree);
	// LR:左右对应的情况(左双旋转)
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* tree);
	// RL:右左对应的情况(右双旋转)
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* tree);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* &tree, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* pNode);
	void destroy(AVLTreeNode<T>* &tree);
	void print(AVLTreeNode<T>* tree, T key, int direction);
};

template <class T>
AVLTree<T>::AVLTree() : root(NULL) {}

template <class T>
AVLTree<T>::~AVLTree() { destroy(root); }

template<class T>
int AVLTree<T>::Height(AVLTreeNode<T>* tree)
{
	if(tree)
		return tree->height;
	return 0;
}

template<class T>
int AVLTree<T>::Height() { return Height(root); }

template<class T>
int AVLTree<T>::max(int a, int b) { return a > b ? a : b; }

template<class T>
void AVLTree<T>::preOrder(AVLTreeNode<T>* tree) const
{
	if(tree)
	{
		cout << tree->key << ' ';
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void AVLTree<T>::preOrder() { preOrder(root); }

template<class T>
void AVLTree<T>::inOrder(AVLTreeNode<T>* tree) const
{
	if(tree)
	{
		inOrder(tree->left);
		cout << tree->key << ' ';
		inOrder(tree->right);
	}
}

template<class T>
void AVLTree<T>::inOrder() { inOrder(root); }

template<class T>
void AVLTree<T>::postOrder(AVLTreeNode<T>* tree) const
{
	if(tree)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << ' ';
	}
}

template<class T>
void AVLTree<T>::postOrder() { postOrder(root); }

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(AVLTreeNode<T>* tree, T key) const
{
	if(NULL == tree || key == tree->key)
		return tree;

	if(key < tree->key)
		search(tree->left, key);
	else
		search(tree->right, key);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::search(T key) { return search(root, key); }

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(AVLTreeNode<T>* tree, T key) const
{
	while(tree != NULL && tree->key != key)
	{
		if(key < tree->key)
			tree = tree->left;
		else
			tree = tree->right;
	}

	return tree;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::iterativeSearch(T key) { return iterativeSearch(root, key); }

template<class T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* tree)
{
	if(NULL == tree)
		return NULL;

	while(tree->left)
		tree = tree->left;
	return tree;
}

template<class T>
T AVLTree<T>::minimum()
{
	AVLTreeNode<T> *p = minimum(root);
	if(p)
		return p->key;
	return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* tree)
{
	if(NULL == tree)
		return NULL;

	while(tree->right)
		tree = tree->right;
	return tree;
}

template<class T>
T AVLTree<T>::maximum()
{
	AVLTreeNode<T> *p = maximum(root);
	if(p)
		return p->key;
	return (T)NULL;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftLeftRotation(AVLTreeNode<T>* tree)
{
	AVLTreeNode<T>* pLeft = tree->left;
	tree->left = pLeft->right;
	pLeft->right = tree;

	tree->height = max(Height(tree->left), Height(tree->right)) + 1;
	pLeft->height = max(Height(pLeft->left), tree->height) + 1;

	return pLeft;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightRightRotation(AVLTreeNode<T>* tree)
{
	AVLTreeNode<T>* pRight = tree->right;
	tree->right = pRight->left;
	pRight->left = tree;

	tree->height = max(Height(tree->left), Height(tree->right)) + 1;
	pRight->height = max(Height(pRight->right), tree->height) + 1;

	return pRight;
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* tree)
{
	tree->left = rightRightRotation(tree->left);
	return leftLeftRotation(tree);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* tree)
{
	tree->right = leftLeftRotation(tree->right);
	return rightRightRotation(tree);
}

template<class T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* &tree, T key)
{
	if(NULL == tree)
	{
		tree = new AVLTreeNode<T>(key, NULL, NULL);
		if(NULL == tree)
		{
			cout << "Error: create avltree node failed" << endl;
			return NULL;
		}
	}
	else if(key < tree->key)
	{
		tree->left = insert(tree->left, key);
		// 插入节点后,若avl树失去平衡,则调节
		if(Height(tree->left) - Height(tree->right) == 2)
		{
			if(key < tree->left->key)
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else if(key >= tree->key)
	{
		tree->right = insert(tree->right, key);
		if(Height(tree->right) - Height(tree->left) == 2)
		{
			if(key < tree->right->key)
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}

	tree->height = max(Height(tree->left), Height(tree->right)) + 1;

	return tree;
}

template<class T>
void AVLTree<T>::insert(T key) { insert(root, key); }

template<class T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* &tree, AVLTreeNode<T>* pNode)
{
	if(NULL == tree || NULL == pNode)
		return NULL;

	if(pNode->key < tree->key)
	{
		tree->left = remove(tree->left, pNode);
		if(Height(tree->right) - Height(tree->left) == 2)
		{
			AVLTreeNode<T> *r = tree->right;
			if(Height(r->left) > Height(r->right))
				tree = rightLeftRotation(tree);
			else
				tree = rightRightRotation(tree);
		}
	}
	else if(pNode->key > tree->key)
	{
		tree->right = remove(tree->right, pNode);
		if(Height(tree->left) - Height(tree->right) == 2)
		{
			AVLTreeNode<T> *l = tree->left;
			if(Height(l->left) > Height(l->right))
				tree = leftLeftRotation(tree);
			else
				tree = leftRightRotation(tree);
		}
	}
	else	// tree为要删除的节点
	{
		if(tree->left && tree->right)
		{
			if(Height(tree->left) > Height(tree->right))
			{
				AVLTreeNode<T>* pMax = maximum(tree->left);
				tree->key = pMax->key;
				tree->left = remove(tree->left, pMax);
			}
			else
			{
				AVLTreeNode<T>* pMin = minimum(tree->right);
				tree->key = pMin->key;
				tree->right = remove(tree->right, pMin);
			}
		}
		else
		{
			AVLTreeNode<T>* pTmp = tree;
			tree = (tree->left ? tree->left : tree->right);
			delete pTmp;
		}
	}

	return tree;
}

template<class T>
void AVLTree<T>::remove(T key)
{
	AVLTreeNode<T>* pNode = search(root, key);
	if(pNode)
		root = remove(root, pNode);
}

template<class T>
void AVLTree<T>::destroy(AVLTreeNode<T>* &tree)
{
	if(tree == NULL)
		return ;

	if(tree->left)
		destroy(tree->left);
	if(tree->right)
		destroy(tree->right);

	delete tree;
}

template<class T>
void AVLTree<T>::destroy() { destroy(root); }

template<class T>
void AVLTree<T>::print(AVLTreeNode<T>* tree, T key, int direction)
{
	if(tree)
	{
		if(0 == direction)		// tree是根节点
			cout << setw(2) << tree->key << " is root" << endl;
		else					// tree是分支节点
			cout<< setw(2) << tree->key << " is " << setw(2) << key << "'s "
				<< setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<class T>
void AVLTree<T>::print()
{
	if(root)
		print(root, root->key, 0);
}

#endif // _AVL_TREE_HPP_