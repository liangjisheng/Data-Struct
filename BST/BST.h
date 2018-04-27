
// 二叉查找树
#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <iomanip>

using namespace std;

template<class Comparable>
struct BiNode
{
	Comparable element;
	BiNode *left;
	BiNode *right;
	BiNode *parent;
	BiNode(const Comparable &ele, BiNode *par = NULL, BiNode *lt = NULL, BiNode *rt = NULL)
		: element(ele), parent(par), left(lt), right(rt) {}
};

template<class Comparable>	// 必须是可比较大小的数据类型
class BiTree
{
private:
	BiNode<Comparable> *root;

	void insert(const Comparable &x, BiNode<Comparable> *&T) const ;
	void insert_1(BiNode<Comparable> *&T, BiNode<Comparable> *pNode);
	void remove(Comparable &x, BiNode<Comparable> *&T) const;
	// 返回被删除的节点
	BiNode<Comparable>* remove_1(BiNode<Comparable> *&T, BiNode<Comparable> *pNode);
	BiNode<Comparable>* findMin(BiNode<Comparable> *t) const;
	BiNode<Comparable>* findMax(BiNode<Comparable> *t) const;
	bool contains(const Comparable &x, BiNode<Comparable> *t) const;	// find
	void makeEmpty(BiNode<Comparable> *&t);
	void printTree(BiNode<Comparable> *T, Comparable key, int direction) const;
	BiNode<Comparable>* clone(BiNode<Comparable> *t) const;
	BiNode<Comparable>* search(BiNode<Comparable>* x, Comparable key) const;
	BiNode<Comparable>* iterativeSearch(BiNode<Comparable>* x, Comparable key) const;

	void preOrderTraverse(BiNode<Comparable>* root) const;
	void inOrderTraverse(BiNode<Comparable>* root) const;
	void postOrderTraverse(BiNode<Comparable>* root) const;

public:
	BiTree() { root = NULL; }
	BiTree(const BiTree &rhs) { root = NULL; *this = rhs; }
	virtual ~BiTree() { makeEmpty(); }
	const Comparable& findMin() const { return findMin(root)->element; }
	const Comparable& findMax() const { return findMax(root)->element; }
	bool contains(const Comparable& x) const { return contains(x, root); }
	bool isEmpty() const { return root == NULL; }
	void printTree() const { printTree(root, root->element, 0); }
	void makeEmpty() { makeEmpty(root); }
	void insert(const Comparable &x) { insert(x, root); }
	void insert_1(const Comparable &x);
	void remove(Comparable &x) { remove(x, root); }
	void remove_1(const Comparable &x);
	const BiTree& operator = (const BiTree &rhs);
	// 重载输入输出运算符,对于普通类而言可以在类内声明,类外实现
	// 但模板类不行,只能在类内实现
	friend ostream& operator << (ostream &out, BiTree<Comparable> &T)
	{
		T.printTree();
		return out;
	}
	BiTree& operator - (BiTree &T);

	// 递归查找键值为key的节点
	BiNode<Comparable>* search(Comparable key);
	// 非递归查找键值为key的节点
	BiNode<Comparable>* iterativeSearch(Comparable key);
	// 找节点(x)的后继节点,即查找二叉树中数据值大于该节点的最小节点
	BiNode<Comparable>* successor(BiNode<Comparable>* x);
	// 找节点(x)的前驱节点,即查找二叉树中数据值小于该节点的最大节点
	BiNode<Comparable>* predecessor(BiNode<Comparable>* x);

	void preOrderTraverse() { preOrderTraverse(root); }
	void inOrderTraverse() { inOrderTraverse(root); }
	void postOrderTraverse() { postOrderTraverse(root); }
};

template<class Comparable>
void BiTree<Comparable>::insert(const Comparable &x, BiNode<Comparable> *&T) const
{
	if(T == NULL)
	{
		T = new BiNode<Comparable>(x);
		return ;
	}
	BiNode<Comparable> *cur = T, *pre = NULL;		// 非递归实现

	while(cur)
	{
		pre = cur;
		if(x < cur->element)
			cur = cur->left;
		else if(x >= cur->element)
			cur = cur->right;
	}

	cur = new BiNode<Comparable>(x);
	cur->parent = pre;
	if(pre->element > x)
		pre->left = cur;
	else
		pre->right = cur;

	/* 递归实现
	else if(x <= cur->element)
		insert(x, cur->left);
	else if(x > cur->element)
		insert(x, t->right);
	*/
}

template<class Comparable>
void BiTree<Comparable>::remove(Comparable &x, BiNode<Comparable> *&T) const
{
	if(!T)
		return ;

	BiNode<Comparable> *t = T, *tt = NULL;		// 非递归实现
	while(t)
	{
		if(x < t->element)
		{
			tt = t;
			t = t->left;
		}
		else if(x > t->element)
		{
			tt = t;
			t = t->right;
		}
		else if(t->left != NULL && t->right != NULL)
		{
			x = t->element = findMin(t->right)->element;
			tt = t;
			t = t->right;
		}
		else
		{
			BiNode<Comparable> *oldnode = t;
			t = (t->left) ? t->left : t->right;
			delete oldnode;
			break;
		}
	}

	if(tt == NULL)
	{
		T = t;
		return;
	}
	else if(tt->element > x)
	{
		tt->left = t;
		t->parent = tt;
	}
	else
	{
		tt->right = t;
		t->parent = tt;
	}
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::findMin(BiNode<Comparable> *t) const
{
	if(t == NULL)
		return NULL;
	if(t->left == NULL)
		return t;
	return findMin(t->left);
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::findMax(BiNode<Comparable> *t) const
{
	if(t == NULL)
		return NULL;
	if(t->left == NULL)
		return t;
	return findMax(t->right);
}

template<class Comparable>
bool BiTree<Comparable>::contains(const Comparable &x, BiNode<Comparable> *t) const
{
	if(t == NULL)
		return false;
	else if(x < t->element)
		return contains(x, t->left);
	else if(x > t->element)
		return contains(x, t->right);
	else
		return true;
}

template<class Comparable>
void BiTree<Comparable>::makeEmpty(BiNode<Comparable> *&t)
{
	if(t)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}

template<class Comparable>
void BiTree<Comparable>::printTree(BiNode<Comparable> *T, Comparable key, int direction) const
{
	if(T)
	{
		if(0 == direction)	// T是根节点
			cout << setw(2) << T->element << " is root" << endl;
		else
			cout << setw(2) << T->element << " is " << setw(2) << key << "'s " 
				<< setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		printTree(T->left, T->element, -1);
		printTree(T->right, T->element, 1);
	}

	//if(t)
	//{
	//	printTree(t->left);
	//	cout << t->element << ' ';
	//	printTree(t->right);
	//}
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::clone(BiNode<Comparable>* t) const
{
	if(t == NULL)
		return NULL;
	return new BiNode<Comparable>(t->element, clone(t->left), clone(t->right));
}

template<class Comparable>
const BiTree<Comparable>& BiTree<Comparable>::operator =(const BiTree<Comparable> &rhs)
{
	if(this != &rhs)
	{
		makeEmpty();
		root = clone(rhs.root);
	}

	return *this;
}

// template<class Comparable>
//ostream& operator << (ostream& out, BiTree &T)
//{
//	T.printTree();
//	return out;
//}

template<class Comparable>
BiTree<Comparable>& BiTree<Comparable>::operator-(BiTree<Comparable> &T)
{
	while(!T.isEmpty())
	{
		this->remove(T.root->element);
		T.remove(T.root->element);
	}

	return *this;
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::search(BiNode<Comparable>* x, Comparable key) const
{
	if(NULL == x || x->element == key)
		return x;

	if(key < x->element)
		return search(x->left, key);
	else
		return search(x->right, key);
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::search(Comparable key)
{
	return search(root, key);
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::iterativeSearch(BiNode<Comparable>* x, Comparable key) const
{
	while(NULL != x && x->element != key)
	{
		if(key < x->element)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::iterativeSearch(Comparable key)
{
	return iterativeSearch(root, key);
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::successor(BiNode<Comparable>* x)
{
	// 如果x存在右孩子,则x的后继节点为"以其右孩子为根的子树的最小节点"
	if(x->right)
		return findMin(x->right);

	// 如果x没有右孩子,则x有以下两种可能
	// 1:x是一个左孩子,则x的后继节点为它的父节点
	// 2:x是一个右孩子,则查找x的最低父节点,并且该父节点要有左孩子
	//   这个最低父节点就是x的后继节点
	BiNode<Comparable>* par = x->parent;
	while(par && x == par->right)
	{
		x = par;
		par = par->parent;
	}

	return par;
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::predecessor(BiNode<Comparable>* x)
{
	// 如果x存在左孩子,则x的前驱节点为以其左孩子为根的子树的最大节点
	if(x->left)
		return findMax(x->left);

	// 如果x没有左孩子,则x有以下两种可能
	// 1:x是一个右孩子,则x的前驱节点为它的父节点
	// 2:x是一个左孩子,则查找x的最低父节点,并且该父节点要具有右孩子
	//   找到的父节点就是x的前驱节点
	BiNode<Comparable>* par = x->parent;
	while(par && x == par->left)
	{
		x = par;
		par = par->parent;
	}

	return par;
}

template<class Comparable>
void BiTree<Comparable>::preOrderTraverse(BiNode<Comparable>* root) const
{
	if(root)
	{
		cout << root->element << ' ';
		preOrderTraverse(root->left);
		preOrderTraverse(root->right);
	}
}

template<class Comparable>
void BiTree<Comparable>::inOrderTraverse(BiNode<Comparable>* root) const
{
	if(root)
	{
		inOrderTraverse(root->left);
		cout << root->element << ' ';
		inOrderTraverse(root->right);
	}
}

template<class Comparable>
void BiTree<Comparable>::postOrderTraverse(BiNode<Comparable>* root) const
{
	if(root)
	{
		postOrderTraverse(root->left);
		postOrderTraverse(root->right);
		cout << root->element << ' ';
	}
}

template<class Comparable>
void BiTree<Comparable>::insert_1(const Comparable &x)
{
	BiNode<Comparable>* pNode = new BiNode<Comparable>(x);
	if(!pNode)
		return ;
	insert_1(root, pNode);
}

template<class Comparable>
void BiTree<Comparable>::insert_1(BiNode<Comparable> *&T, BiNode<Comparable> *pNode)
{
	BiNode<Comparable> *pre = NULL;
	BiNode<Comparable> *cur = T;

	while(cur)
	{
		pre = cur;
		if(pNode->element < cur->element)
			cur = cur->left;
		else
			cur = cur->right;
	}

	cur->parent = pre;
	if(pre == NULL)
		T = pNode;
	else if(pNode->element < pre->element)
		pre->left = pNode;
	else
		pre->right = pNode;
}

template<class Comparable>
void BiTree<Comparable>::remove_1(const Comparable &x)
{
	BiNode<Comparable> *pNode = NULL, *pNode1 = NULL;
	if((pNode = search(x)) != NULL)
		if((pNode1 = remove(root, pNode)) != NULL)
			delete pNode1;
}

template<class Comparable>
BiNode<Comparable>* BiTree<Comparable>::remove_1(BiNode<Comparable> *&T, BiNode<Comparable> *pNode)
{
	BiNode<Comparable> *x = NULL;
	BiNode<Comparable> *y = NULL;

	if(pNode->left == NULL || pNode->right == NULL)
		y = pNode;
	else
		y = successor(pNode);

	if(y->left)
		x = y->left;
	else
		x = y->right;

	if(x)
		x->parent = y->parent;

	if(y->parent == NULL)
		T = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if(y != pNode)
		pNode->element = y->element;

	return y;
}

#endif // _BST_H_