
/************************************************************************
 * C++ʵ�ֺ����
 * author: ����ʥ
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
	RBTColor color;		// ��ɫ
	T key;				// ��ֵ
	RBTNode* left;		// ����
	RBTNode* right;		// �Һ���
	RBTNode* parent;	// ���ڵ�

	RBTNode(T value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r)
		: key(value), color(c), parent(p), left(l), right(r) {}
};

template<class T>
class RBTree
{
private:
	RBTNode<T>* root;		// ���ڵ�
public:
	RBTree();
	~RBTree();

	// ǰ�����
	void preorder();
	// �������
	void inorder();
	// �������
	void postorder();

	// (�ݹ�ʵ��)���Ҽ�ֵΪkey�Ľڵ�
	RBTNode<T>* search(T key);
	// (�ǵݹ�ʵ��)���Ҽ�ֵΪkey�Ľڵ�
	RBTNode<T>* iterativeSearch(T key);

	// ������С�ڵ�: ������С�ڵ�ļ�ֵ
	T minimum();
	// �������ڵ�: �������ڵ�ļ�ֵ
	T maximum();

	// ���ҽڵ�x�ĺ�̽ڵ�,���������м�ֵ���ڸýڵ����С�ڵ�
	RBTNode<T>* successor(RBTNode<T>* x);
	// ���ҽڵ�x��ǰ���ڵ�,���������м�ֵС�ڸýڵ�����ڵ�
	RBTNode<T>* predecessor(RBTNode<T>* x);

	// ���ڵ�(keyΪ�ڵ��ֵ)���뵽�������
	void insert(T key);

	// ɾ���ڵ�(keyΪ�ڵ�ļ�ֵ)
	void remove(T key);

	// ���ٺ����
	void destroy();

	// ��ӡ�����
	void print();

private:
	// ǰ�����
	void preorder(RBTNode<T>* tree) const;
	// �������
	void inorder(RBTNode<T>* tree) const;
	// �������
	void postorder(RBTNode<T>* tree) const;

	// (�ݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	// (�ǵݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	// ���Ҽ�ֵ��С�Ľڵ�
	RBTNode<T>* minimum(RBTNode<T>* tree);
	// ���Ҽ�ֵ���Ľڵ�
	RBTNode<T>* maximum(RBTNode<T>* tree);

	// ����
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	// ����
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	// ����
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	// ������������
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	// ɾ��
	void remove(RBTNode<T>* &root, RBTNode<T>* node);
	// ɾ����������
	void removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent);

	// ���ٺ����
	void destroy(RBTNode<T>* &tree);

	// ��ӡ�����
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

// (�ݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
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

// (�ǵݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
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


// ����x�ĺ�̽ڵ�,�����Һ�����м�ֵ���ڸýڵ����С�ڵ�
template<class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T>* x)
{
	// ���x�����Һ���,��x�ĺ�̽ڵ�Ϊ"�����Һ���Ϊ������������С�ڵ�"
	if(x->right)
		return minimum(x->right);

	// ���xû���Һ���,��x��һ�����ֿ���
	// 1.x��һ������,��x�ĺ�̽ڵ�Ϊ���ĸ��ڵ�
	// 2.x��һ���Һ���,�����x����͸��ڵ�,�Ҹø��ڵ�Ҫ��������
	//   �ҵ��������͸��ڵ����x�ĺ�̽ڵ�
	RBTNode<T>* y = x->parent;
	while(y && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

// ����x��ǰ���ڵ�,�����Һ�����м�ֵС�ڸýڵ�����ڵ�
template<class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T>* x)
{
	// ���x��������,��x��ǰ���ڵ�Ϊ"��������Ϊ�������������ڵ�"
	if(x->left)
		return maximum(x->left);

	// ���xû������,��x��һ�����ֿ���
	// 1.x��һ���Һ���,��x��ǰ���ڵ�Ϊ���ĸ��ڵ�
	// 2.x��һ������,�����x����͸��ڵ�,�Ҹø��ڵ�Ҫ�����Һ���
	//   �ҵ��ĸ��ڵ����x��ǰ���ڵ�
	RBTNode<T>* y = x->parent;
	while(y && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}


/************************************************************************
 * �Ժ�����Ľڵ�x��������
 *
 *		      px                            px
 *           /							   /
 *          x							  y
 *         / \		 --(����)-->         / \
 *        lx  y                         x   ry
 *           / \                       / \
 *          ly  ry                    lx  ly
 *
************************************************************************/
template<class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	RBTNode<T>* y = x->right;		// ����x���Һ���Ϊy

	x->right = y->left;				// y��������Ϊx���Һ���
	if(y->left)
		y->left->parent = x;		// ���y�����ӷǿ�,��x��Ϊy�����ӵĸ���

	y->parent = x->parent;			// ��x�ĸ�����Ϊy�ĸ���
	if(NULL == x->parent)
		root = y;					// ���x�ĸ��ڵ�Ϊ��,��y��Ϊ���ڵ�			
	else
	{
		if(x->parent->left == x)
			x->parent->left = y;	// ���x�������ڵ������,��y��Ϊx�ĸ��ڵ������
		else
			x->parent->right = y;	// ���x�������ڵ���Һ���,��y��Ϊx�ĸ��ڵ���Һ���
	}

	y->left = x;					// ��x��Ϊy������
	x->parent = y;					// ��x�ĸ��ڵ���Ϊy
}

/************************************************************************
 * �Ժ�����Ľڵ�y��������
 *
 *            py                         py
 *           /						    /
 *          y                          x
 *         / \     --(����)-->        / \
 *        x  ry                      lx  y
 *       / \                            / \
 *      lx  rx                         rx  ry
 *
************************************************************************/
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	RBTNode<T>* x = y->left;			// ����xΪ��ǰ�ڵ������
	
	y->left = x->right;					// ��x���Һ�����Ϊy������
	if(x->right)
		x->right->parent = y;			// ���x���Һ��ӷǿ�,��y��Ϊx���Һ��ӵĸ���

	x->parent = y->parent;				// ��y�ĸ��ڵ���Ϊx�ĸ��ڵ�
	if(NULL == y->parent)
		root = x;						// ���y�ĸ��ڵ��ǿսڵ�,��x��Ϊ���ڵ�
	else
	{
		if(y == y->parent->right)
			y->parent->right = x;		// ���y�������ڵ���Һ���,��x��Ϊy�ĸ��ڵ���Һ���
		else
			y->parent->left = x;		// ���y�������ڵ������,��x��Ϊy�ĸ��ڵ������
	}

	x->right = y;						// ��y��Ϊx���Һ���
	y->parent = x;						// ��y�ĸ��ڵ���Ϊx
}


/************************************************************************
 * �����������������,���������в���ڵ�֮��(ʧȥƽ��),�ڵ��øú���
 * Ŀ���ǽ������������һ�ź����
 * ����˵��: root���ڵ�,node����Ľڵ�
************************************************************************/
template<class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* parent;
	RBTNode<T>* gparent;

	// ������ڵ����,�Ҹ��ڵ����ɫ�Ǻ�ɫ
	while((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		// ���ڵ������Ƚڵ������
		if(parent == gparent->left)
		{
			// case1: ����ڵ��Ǻ�ɫ
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

			// case2: �����Ǻ�ɫ,�ҵ�ǰ�ڵ����Һ���
			if(parent->right == node)
			{
				RBTNode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: �����Ǻ�ɫ,�ҵ�ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		// ���ڵ������Ƚڵ���Һ���
		else
		{
			// case1: ����ڵ��Ǻ�ɫ
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

			// case2: �����Ǻ�ɫ,�ҵ�ǰ�ڵ�������
			if(parent->left == node)
			{
				RBTNode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: �����Ǻ�ɫ,�ҵ�ǰ�ڵ����Һ���
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}

	rb_set_black(root);			// �����ڵ���Ϊ��ɫ
}

// ���ڵ�node����������
template<class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* y = NULL;
	RBTNode<T>* x = root;

	// 1.�����������һ�Ŷ��������,���ڵ���ӵ������������
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

	// 2.���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3.������������Ϊһ�Ŷ��������
	insertFixUp(root, node);
}

// ���ڵ�(keyΪ�ڵ��ֵ)���뵽�������
template<class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T>* pNode = new RBTNode<T>(key, BLACK, NULL, NULL, NULL);
	if(!pNode)
		return ;

	insert(root, pNode);
}

/************************************************************************
 * �����ɾ����������,�Ӻ������ɾ���ڵ��ʧȥƽ��,�ڵ��øú���,Ŀ���ǽ�
 * �����������һ�ź����
 * ����˵��: root���ڵ�,node�������Ľڵ�
************************************************************************/
template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T>* node, RBTNode<T>* parent)
{
	RBTNode<T>* other;		// ��ʾ�ֵܽڵ�

	while((!node || rb_is_black(node)) && node != root)
	{
		// ��ǰ�ڵ��Ǹ��ڵ������
		if(parent->left == node)
		{
			other = parent->right;
			if(rb_is_red(other))
			{
				// case1: node���ֵܽڵ�other�Ǻ�ɫ
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}

			if((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node���ֵܽڵ�other�Ǻ�ɫ,��other����������Ҳ�Ǻ�ɫ
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->right || rb_is_black(other->right))
				{
					// case3: node���ֵ�other�Ǻ�ɫ��,��other�������Ǻ�ɫ,�Һ���Ϊ��ɫ
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}

				// case4: node���ֵ�other�Ǻ�ɫ��,��other���Һ����Ǻ�ɫ,����Ϊ������ɫ
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		// ��ǰ�ڵ��Ǹ��ڵ���Һ���
		else
		{
			other = parent->left;
			if(rb_is_red(other))
			{
				// case1: node���ֵ�other�Ǻ�ɫ��
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}

			if((!other->left || rb_is_black(other->left)) && 
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node���ֵ�other�Ǻ�ɫ��,��other����������Ҳ���Ǻ�ɫ��
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->left || rb_is_black(other->left))
				{
					// case3: node���ֵ�other�Ǻ�ɫ��,��other�������Ǻ�ɫ,�Һ���Ϊ��ɫ
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}

				// case4: node���ֵ�other�Ǻ�ɫ��,��other���Һ����Ǻ�ɫ,����Ϊ������ɫ
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

//ɾ���ڵ�node
template<class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* child;
	RBTNode<T>* parent;
	RBTColor color;

	// ��ɾ���ڵ�����Һ��Ӷ���Ϊ��
	if(node->left && node->right)
	{
		//��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ��
		RBTNode<T>* replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while(replace->left)
			replace = replace->left;

		// node�ڵ㲻�Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if(rb_parent(node))
		{
			if(rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			root = replace;

		// child��ȡ���ڵ���Һ���,Ҳ����Ҫ�����Ľڵ�
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ�
		child = replace->right;
		parent = rb_parent(replace);
		// ����ȡ���ڵ����ɫ
		color = rb_color(replace);

		// ��ɾ���ڵ������ĺ�̽ڵ�ĸ��ڵ�
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
	// ����ȡ���ڵ����ɫ
	color = node->color;

	if(child)
		child->parent = parent;

	// node�ڵ㲻�Ǹ��ڵ�
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
 * ��ӡ�����
 * key�ڵ��ֵ
 * direction: 0��ʾ�ýڵ��Ǹ��ڵ�,-1��ʾ�ýڵ�������,1��ʾ�ýڵ����Һ���
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