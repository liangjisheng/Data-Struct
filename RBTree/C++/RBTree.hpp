
/************************************************************************
 * C++实现红黑树
 * author: 梁基圣
 * date: 20171109
************************************************************************/

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::setw;

enum RBTColor { RED, BLACK };

#define rb_parent(r)			((r)->parent)
#define rb_color(r)				((r)->color)
#define rb_is_red(r)			((r)->color == RED)
#define rb_is_black(r)			((r)->color == BLACK)
#define rb_set_red(r)			do { (r)->color = RED; } while(0)
#define rb_set_black(r)			do { (r)->color = BLACK; } while(0)
#define rb_set_parent(r, p)		do { (r)->parent = (p); } while(0)
#define rb_set_color(r, c)		do { (r)->color = (c); } while(0)

template<class T>
class RBTNode
{
public:
	RBTColor color;		// 颜色
	T key;				// 键值
	RBTNode* left;		// 左孩子
	RBTNode* right;		// 右孩子
	RBTNode* parent;	// 父节点

	RBTNode(T value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r)
		: key(value), color(c), parent(p), left(l), right(r) {}
};

template<class T>
class RBTree
{
private:
	RBTNode<T>* root;		// 根节点
public:
	RBTree();
	~RBTree();

	// 前序遍历
	void preorder();
	// 中序遍历
	void inorder();
	// 后序遍历
	void postorder();

	// (递归实现)查找键值为key的节点
	RBTNode<T>* search(T key);
	// (非递归实现)查找键值为key的节点
	RBTNode<T>* iterativeSearch(T key);

	// 查找最小节点: 返回最小节点的键值
	T minimum();
	// 查找最大节点: 返回最大节点的键值
	T maximum();

	// 查找节点x的后继节点,即查找树中键值大于该节点的最小节点
	RBTNode<T>* successor(RBTNode<T>* x);
	// 查找节点x的前驱节点,即查找树中键值小于该节点的最大节点
	RBTNode<T>* predecessor(RBTNode<T>* x);

	// 将节点(key为节点键值)插入到红黑树中
	void insert(T key);

	// 删除节点(key为节点的键值)
	void remove(T key);

	// 销毁红黑树
	void destroy();

	// 打印红黑树
	void print();

private:
	// 前序遍历
	void preorder(RBTNode<T>* tree) const;
	// 中序遍历
	void inorder(RBTNode<T>* tree) const;
	// 后序遍历
	void postorder(RBTNode<T>* tree) const;

	// (递归实现)查找红黑树x中键值为key的节点
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	// (非递归实现)查找红黑树x中键值为key的节点
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	// 查找键值最小的节点
	RBTNode<T>* minimum(RBTNode<T>* tree);
	// 查找键值最大的节点
	RBTNode<T>* maximum(RBTNode<T>* tree);

	// 左旋
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	// 右旋
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	// 插入
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	// 插入修正函数
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	// 删除
	void remove(RBTNode<T>* &root, RBTNode<T>* node);
	// 删除修正函数
	void removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent);

	// 销毁红黑树
	void destroy(RBTNode<T>* &tree);

	// 打印红黑树
	void print(RBTNode<T>* tree, T key, int direction);
};


template<class T>
RBTree<T>::RBTree() : root(NULL) {}

template<class T>
RBTree<T>::~RBTree() { destroy(); }

template<class T>
void RBTree<T>::preorder(RBTNode<T>* tree) const
{
	if(tree)
	{
		cout << "(" << tree->key << "," << tree->color << ")";
		preorder(tree->left);
		preorder(tree->right);
	}
}

template<class T>
void RBTree<T>::preorder() { preorder(root); }

template<class T>
void RBTree<T>::inorder(RBTNode<T>* tree) const
{
	if(tree)
	{
		inorder(tree->left);
		cout << "(" << tree->key << "," << tree->color << ")";
		inorder(tree->right);
	}
}

template<class T>
void RBTree<T>::inorder() { inorder(root); }

template<class T>
void RBTree<T>::postorder(RBTNode<T>* tree) const
{
	if(tree)
	{
		postorder(tree->left);
		postorder(tree->right);
		cout << "(" << tree->key << "," << tree->color << ")";
	}
}

template<class T>
void RBTree<T>::postorder() { postorder(root); }

// (递归实现)查找红黑树x中键值为key的节点
template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
	if(x == NULL || x->key == key)
		return x;

	if(key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);

}

template<class T>
RBTNode<T>* RBTree<T>::search(T key) { return search(root, key); }

// (非递归实现)查找红黑树x中键值为key的节点
template<class T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const
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

template<class T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key) { return iterativeSearch(root, key); }


template<class T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
	if(!tree)
		return NULL;

	while(tree->left)
		tree = tree->left;

	return tree;
}

template<class T>
T RBTree<T>::minimum()
{
	RBTNode<T>* pNode = minimum(root);
	if(pNode)
		return pNode->key;

	return (T)NULL;
}

template<class T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
	if(!tree)
		return NULL;

	while(tree->right)
		tree = tree->right;

	return tree;
}

template<class T>
T RBTree<T>::maximum()
{
	RBTNode<T>* pNode = maximum(root);
	if(pNode)
		return pNode->key;

	return (T)NULL;
}


// 查找x的后继节点,即查找红黑树中键值大于该节点的最小节点
template<class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T>* x)
{
	// 如果x存在右孩子,则x的后继节点为"以其右孩子为根的子树的最小节点"
	if(x->right)
		return minimum(x->right);

	// 如果x没有右孩子,则x有一下两种可能
	// 1.x是一个左孩子,在x的后继节点为它的父节点
	// 2.x是一个右孩子,则查找x的最低父节点,且该父节点要具有左孩子
	//   找到的这个最低父节点就是x的后继节点
	RBTNode<T>* y = x->parent;
	while(y && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

// 查找x的前驱节点,即查找红黑树中键值小于该节点的最大节点
template<class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T>* x)
{
	// 如果x存在左孩子,则x的前驱节点为"以其左孩子为根的子树的最大节点"
	if(x->left)
		return maximum(x->left);

	// 如果x没有左孩子,则x有一下两种可能
	// 1.x是一个右孩子,则x的前驱节点为它的父节点
	// 2.x是一个左孩子,则查找x的最低父节点,且该父节点要具有右孩子
	//   找到的父节点就是x的前驱节点
	RBTNode<T>* y = x->parent;
	while(y && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}


/************************************************************************
 * 对红黑树的节点x进行左旋
 *
 *		      px                            px
 *           /							   /
 *          x							  y
 *         / \		 --(左旋)-->         / \
 *        lx  y                         x   ry
 *           / \                       / \
 *          ly  ry                    lx  ly
 *
************************************************************************/
template<class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	RBTNode<T>* y = x->right;		// 设置x的右孩子为y

	x->right = y->left;				// y的左孩子设为x的右孩子
	if(y->left)
		y->left->parent = x;		// 如果y的左孩子非空,则将x设为y的左孩子的父亲

	y->parent = x->parent;			// 将x的父亲设为y的父亲
	if(NULL == x->parent)
		root = y;					// 如果x的父节点为空,则将y设为根节点			
	else
	{
		if(x->parent->left == x)
			x->parent->left = y;	// 如果x是它父节点的左孩子,则将y设为x的父节点的左孩子
		else
			x->parent->right = y;	// 如果x是它父节点的右孩子,则将y设为x的父节点的右孩子
	}

	y->left = x;					// 将x设为y的左孩子
	x->parent = y;					// 将x的父节点设为y
}

/************************************************************************
 * 对红黑树的节点y进行右旋
 *
 *            py                         py
 *           /						    /
 *          y                          x
 *         / \     --(右旋)-->        / \
 *        x  ry                      lx  y
 *       / \                            / \
 *      lx  rx                         rx  ry
 *
************************************************************************/
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	RBTNode<T>* x = y->left;			// 设置x为当前节点的左孩子
	
	y->left = x->right;					// 将x的右孩子设为y的左孩子
	if(x->right)
		x->right->parent = y;			// 如果x的右孩子非空,将y设为x的右孩子的父亲

	x->parent = y->parent;				// 将y的父节点设为x的父节点
	if(NULL == y->parent)
		root = x;						// 如果y的父节点是空节点,则将x设为根节点
	else
	{
		if(y == y->parent->right)
			y->parent->right = x;		// 如果y是它父节点的右孩子,则将x设为y的父节点的右孩子
		else
			y->parent->left = x;		// 如果y是它父节点的左孩子,则将x设为y的父节点的左孩子
	}

	x->right = y;						// 将y设为x的右孩子
	y->parent = x;						// 将y的父节点设为x
}


/************************************************************************
 * 红黑树插入修正函数,在向红黑树中插入节点之后(失去平衡),在调用该函数
 * 目的是将它重新塑造成一颗红黑树
 * 参数说明: root根节点,node插入的节点
************************************************************************/
template<class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* parent;
	RBTNode<T>* gparent;

	// 如果父节点存在,且父节点的颜色是红色
	while((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		// 父节点是祖先节点的左孩子
		if(parent == gparent->left)
		{
			// case1: 叔叔节点是红色
			{
				RBTNode<T>* uncle = gparent->right;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// case2: 叔叔是黑色,且当前节点是右孩子
			if(parent->right == node)
			{
				RBTNode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: 叔叔是黑色,且当前节点是左孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		// 父节点是祖先节点的右孩子
		else
		{
			// case1: 叔叔节点是红色
			{
				RBTNode<T>* uncle = gparent->left;
				if(uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// case2: 叔叔是黑色,且当前节点是左孩子
			if(parent->left == node)
			{
				RBTNode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: 叔叔是黑色,且当前节点是右孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	rb_set_black(root);			// 将根节点设为黑色
}

// 将节点node插入红黑树中
template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* y = NULL;
	RBTNode<T>* x = root;

	// 1.将红黑树当做一颗二叉查找树,将节点添加到二叉查找树中
	while(x)
	{
		y = x;
		if(node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if(y)
	{
		if(node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2.设置节点的颜色为红色
	node->color = RED;

	// 3.将它重新修正为一颗二叉查找树
	insertFixUp(root, node);
}

// 将节点(key为节点键值)插入到红黑树中
template<class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T>* pNode = new RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	if(!pNode)
		return ;

	insert(root, pNode);
}

/************************************************************************
 * 红黑树删除修正函数,从红黑树中删除节点后失去平衡,在调用该函数,目的是将
 * 它重新塑造成一颗红黑树
 * 参数说明: root根节点,node待修正的节点
************************************************************************/
template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent)
{
	RBTNode<T>* other;		// 表示兄弟节点

	while((!node || rb_is_black(node)) && node != root)
	{
		// 当前节点是父节点的左孩子
		if(parent->left == node)
		{
			other = parent->right;
			if(rb_is_red(other))
			{
				// case1: node的兄弟节点other是红色
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}

			if((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node的兄弟节点other是黑色,且other的两个孩子也是黑色
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->right || rb_is_black(other->right))
				{
					// case3: node的兄弟other是黑色的,且other的左孩子是红色,右孩子为黑色
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}

				// case4: node的兄弟other是黑色的,且other的右孩子是红色,左孩子为任意颜色
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		// 当前节点是父节点的右孩子
		else
		{
			other = parent->left;
			if(rb_is_red(other))
			{
				// case1: node的兄弟other是红色的
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}

			if((!other->left || rb_is_black(other->left)) && 
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node的兄弟other是黑色的,且other的两个孩子也都是黑色的
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->left || rb_is_black(other->left))
				{
					// case3: node的兄弟other是黑色的,且other的左孩子是红色,右孩子为黑色
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}

				// case4: node的兄弟other是黑色的,且other的右孩子是红色,左孩子为任意颜色
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if(node)
		rb_set_black(node);
}

//删除节点node
template<class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* child;
	RBTNode<T>* parent;
	RBTColor color;

	// 被删除节点的左右孩子都不为空
	if(node->left && node->right)
	{
		//被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉
		RBTNode<T>* replace = node;

		// 获取后继节点
		replace = replace->right;
		while(replace->left)
			replace = replace->left;

		// node节点不是根节点(只有根节点不存在父节点)
		if(rb_parent(node))
		{
			if(rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			root = replace;

		// child是取代节点的右孩子,也是需要调整的节点
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点
		child = replace->right;
		parent = rb_parent(replace);
		// 保存取代节点的颜色
		color = rb_color(replace);

		// 被删除节点是它的后继节点的父节点
		if(parent == node)
			parent = replace;
		else
		{
			if(child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if(color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return ;
	}

	if(node->left)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// 保存取代节点的颜色
	color = node->color;

	if(child)
		child->parent = parent;

	// node节点不是跟节点
	if(parent)
	{
		if(parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if(color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
}

template<class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T>* node = search(root, key);
	if(node)
		remove(root, node);
}

template<class T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
	if(!tree)
		return ;

	if(tree->left)
		return destroy(tree->left);
	if(tree->right)
		return destroy(tree->right);

	delete tree;
	tree = NULL;
}

template<class T>
void RBTree<T>::destroy() { destroy(root); }

/************************************************************************
 * 打印红黑树
 * key节点键值
 * direction: 0表示该节点是根节点,-1表示该节点是左孩子,1表示该节点是右孩子
************************************************************************/
template<class T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
	if(tree)
	{
		if(0 == direction)
			cout << setw(2) << tree->key << "(B) is root" << endl;
		else
			cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") << " is "
				<< setw(2) << key << "'s" <<  setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<class T>
void RBTree<T>::print()
{
	if(root)
		print(root, root->key, 0);
}


#endif // _RED_BLACK_TREE_HPP_