
/***********************************************************************
 * C����ʵ�ֺ����(Red Black Tree)
 * author�� ����ʥ
 * date: 20171108
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"

#define rb_parent(r)		((r)->parent)
#define rb_color(r)			((r)->color)
#define rb_is_red(r)		((r)->color == RED)
#define rb_is_black(r)		((r)->color == BLACK)
#define rb_set_black(r)		do { (r)->color = BLACK; } while(0)
#define rb_set_red(r)		do { (r)->color = RED; } while(0)
#define rb_set_parent(r, p)	do { (r)->parent = (p); } while(0)
#define rb_set_color(r, c)	do { (r)->color = (c); } while(0)


/************************************************************************
 * ��������: ���������
 * ��    ��: ��
 * �� �� ֵ: ������ĸ�
************************************************************************/
RBRoot* create_rbtree()
{
	RBRoot *root = (RBRoot*)malloc(sizeof(RBRoot));
	root->node = NULL;

	return root;
}

// ǰ����������
static void preorder(RBTree tree)
{
	if(tree)
	{
		printf("(%d ", tree->key);
		printf("%c),", tree->color ? 'B' : 'R');
		preorder(tree->left);
		preorder(tree->right);
	}
}

void preorder_rbtree(RBRoot *root)
{
	if(root)
		preorder(root->node);
}

// ������������
static void inorder(RBTree tree)
{
	if(tree)
	{
		inorder(tree->left);
		printf("(%d ", tree->key);
		printf("%c),", tree->color ? 'B' : 'R');
		inorder(tree->right);
	}
}

void inorder_rbtree(RBRoot *root)
{
	if(root)
		inorder(root->node);
}

// ������������
static void postorder(RBTree tree)
{
	if(tree)
	{
		postorder(tree->left);
		postorder(tree->right);
		printf("(%d ", tree->key);
		printf("%c),", tree->color ? 'B' : 'R');
	}
}

void postorder_rbtree(RBRoot *root)
{
	if(root)
		postorder(root->node);
}


/************************************************************************
 * ��������: (�ݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
 * �� �� ֵ: �����ҵ��Ľڵ�
************************************************************************/
static Node* search(RBTree x, Type key)
{
	if(x == NULL || x->key == key)
		return x;

	if(key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
}

int rbtree_search(RBRoot *root, Type key)
{
	if(root)
		return search(root->node, key) ? 0 : -1;

	return -1;
}

/************************************************************************
 * ��������: (�ǵݹ�ʵ��)���Һ����x�м�ֵΪkey�Ľڵ�
 * �� �� ֵ: �����ҵ��Ľڵ�
************************************************************************/
static Node* iterative_search(RBTree x, Type key)
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

int iterative_rbtree_search(RBRoot *root, Type key)
{
	if(root)
		iterative_search(root->node, key) ? 0 : -1;

	return -1;
}

// ����treeΪ���ڵ�ĺ��������С�ڵ�
static Node* minimum(RBTree tree)
{
	if(!tree)
		return NULL;

	while(tree->left)
		tree = tree->left;
	return tree;
}

int rbtree_minimum(RBRoot *root, int *val)
{
	Node *node;
	if(root)
		node = minimum(root->node);

	if(!node)
		return -1;

	*val = node->key;
	return 0;
}

// ����treeΪ���ڵ�ĺ���������ڵ�
static Node* maximum(RBTree tree)
{
	if(!tree)
		return NULL;

	while(tree->right)
		tree = tree->right;
	return tree;
}

int rbtree_maximum(RBRoot *root, int *val)
{
	Node *node;
	if(root)
		node = maximum(root->node);

	if(!node)
		return -1;

	*val = node->key;
	return 0;
}


// ����x�ĺ�̽ڵ�,�������������ֵ���ڸýڵ����С�ڵ�
static Node* rbtree_successor(RBTree x)
{
	// ���x�����Һ���,��x�ĺ�̽ڵ�Ϊ"�����Һ���Ϊ������������С�ڵ�"
	if(x->right)
		return minimum(x->right);

	// ���xû���Һ���.��x���������ֿ���:
	// 1.x��һ������,��x�ĺ�̽ڵ�Ϊ���ĸ��ڵ�
	// 2.x��һ���Һ���,�����x����͸��ڵ�,���Ҹø��ڵ�Ҫ��������
	//   �ҵ��������͸��ڵ����x�ĺ�̽ڵ�
	Node *y = x->parent;
	while(y && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

// �ҽڵ�x��ǰ���ڵ�,�����Һ����������ֵС�ڸýڵ�����ڵ�
static Node* rbtree_predecessor(RBTree x)
{
	// ���x��������,��x��ǰ���ڵ�Ϊ"��������Ϊ�������������ڵ�"
	if(x->left)
		return maximum(x->left);

	// ���xû������,��x���������ֿ���
	// 1.x��һ���Һ���,��x��ǰ���ڵ�Ϊ���ĸ��ڵ�
	// 2.x��һ������,�����x����͸��ڵ�,���Ҹø��ڵ�Ҫ�����Һ���
	//   �ҵ��������͸��ڵ����x��ǰ���ڵ�
	Node* y = x->parent;
	while(y && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}


/***********************************************************************
 * �Ժ�����Ľڵ�x��������ת
 * ����ʾ��ͼ
 *              px                                    px
 *             /                                     /
 *            x                                     y
 *           / \          --(����)-->              / \
 *         lx   y                                 x   ry
 *             / \                               / \
 *           ly   ry                            lx  ly
 *
 *
***********************************************************************/
static void rbtree_left_rotate(RBRoot *root, Node* x)
{
	Node* y = x->right;				// ����x���Һ���Ϊy
	
	x->right = y->left;				// ��y��������Ϊx���Һ���
	if(y->left)						// ���y�����ӷǿ�,��x��Ϊy�����ӵĸ���
		y->left->parent = x;

	y->parent = x->parent;			// ��x�ĸ�����Ϊy�ĸ���

	if(NULL == x->parent)			// ���x�ĸ���Ϊ��,��y��Ϊ���ڵ�
		root->node = y;
	else
	{
		if(x == x->parent->left)	// ���x�������ڵ������,��y��Ϊx�ĸ��ڵ������
			x->parent->left = y;
		else
			x->parent->right = y;	// ���x�������ڵ���Һ���,��y��Ϊx�ĸ��ڵ���Һ���
	}

	y->left = x;					// ��x��Ϊy������
	x->parent = y;					// ��x�ĸ��ڵ���Ϊy
}

/************************************************************************
 * �Ժ�����Ľڵ�y��������ת
 * ����ʾ��ͼ(�Խڵ�y��������)
 *               py                            py
 *              /                             /
 *             y                             x
 *            / \     --(����)-->           / \
 *           x   ry                        lx  y
 *          / \                               / \
 *        lx   rx                            rx  ry
 *
************************************************************************/
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
	Node* x = y->left;				// ����x�ǵ�ǰ�ڵ������

	y->left = x->right;				// ��x���Һ�������Ϊy������
	if(x->right)					// ���x���Һ��Ӳ�Ϊ�յĻ�,��y����Ϊx���Һ��ӵĸ���
		x->right->parent = y;

	x->parent = y->parent;			// ��y�ĸ�����Ϊx�ĸ���

	if(NULL == y->parent)
		root->node = x;
	else
	{
		if(y == y->parent->right)	// ���y�������ڵ���Һ���,��x��Ϊy�ĸ��ڵ���Һ���
			y->parent->right = x;
		else
			y->parent->left = x;	// ���y�������ڵ������,��x��Ϊy�ĸ��ڵ������
	}

	x->right = y;					// ��y��Ϊx���Һ���
	y->parent = x;					// y�ĸ��ڵ���Ϊx
}


/************************************************************************
 * �����������������,���������в���ڵ��(ʧȥƽ��),�ڵ��øú���
 * Ŀ���ǽ������������һ�������,������˼����ǽ���ɫ�Ľڵ��Ƶ����ڵ�
 * Ȼ��,�����ڵ���Ϊ��ɫ
 * ���ݱ�����ڵ�ĸ��ڵ�����,���Խ����ڵ�node����ɫΪ��ɫ�ڵ�,������
 * ����������Ϊ�������������
 * 1.���˵��: ������Ľڵ��Ǹ��ڵ�
 *   ������: ֱ�ӰѴ˽ڵ�ͿΪ��ɫ
 * 2.���˵��: ������Ľڵ�ĸ��ڵ��Ǻ�ɫ��
 *   �������: ʲôҲ����Ҫ��,�ڵ㱻�����,��Ȼ�Ǻ����
 * 3.�������: ������ڵ�ĸ��ڵ��Ǻ�ɫ
 *   ������: �����������������4���ͻ.�����������,������ڵ���һ��
 *			   �ǿ��游�ڵ��(��Ϊ���ڵ�Ϊ��ɫ,����ɫ�ڵ㲻����Ϊ���ڵ�);
 *			   ��һ����,������ڵ�Ҳһ����������ڵ�(��ʹ����ڵ�Ϊ��,��
 *			   ��Ҳ��֮����,�սڵ㱾����Ǻ�ɫ�ڵ�).��������ڵ�����,��
 *			   ���������һ������Ϊ3�����(case)
 *	 case1: ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ,�ҵ�ǰ�ڵ���游�ڵ����һ���ӽڵ�(����
 *			�ڵ�)Ҳ�Ǻ�ɫ
 *		 �������: (01) �������ڵ㡱��Ϊ��ɫ��
 *				   (02) ��������ڵ㡱��Ϊ��ɫ��
 *				   (03) �����游�ڵ㡱��Ϊ����ɫ����
 *				   (04) �����游�ڵ㡱��Ϊ����ǰ�ڵ㡱(��ɫ�ڵ�)
 *					   ����֮������ԡ���ǰ�ڵ㡱���в���
 *	 case2: ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ,����ڵ��Ǻ�ɫ,�ҵ�ǰ�ڵ����丸�ڵ���Һ���
 *		 �������: (01)�����ڵ���Ϊ�µĵ�ǰ�ڵ�
 *				   (02)���µĵ�ǰ�ڵ�Ϊ֧���������
 *	 case3: ��ǰ�ڵ�ĸ��ڵ��Ǻ�ɫ,����ڵ��Ǻ�ɫ,�ҵ�ǰ�ڵ����丸�ڵ������
 *		 �������: (01)�����ڵ���Ϊ��ɫ
 *				   (02)���游�ڵ���Ϊ��ɫ
 *				   (03)���游�ڵ�Ϊ֧���������
 * ����˵��: root������ĸ�,node����Ľڵ�
************************************************************************/
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
	Node *parent;
	Node *gparent;

	// �����ڵ�����Ҹ��ڵ����ɫ�Ǻ�ɫ
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		// �����ڵ������Ƚڵ������
		if(parent == gparent->left)
		{
			// case1: ����ڵ��Ǻ�ɫ
			{
				Node *uncle = gparent->right;
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
			if(node == parent->right)
			{
				Node *tmp;
				rbtree_left_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: �����Ǻ�ɫ,�ҵ�ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_right_rotate(root, gparent);
		}
		// ���ڵ������Ƚڵ���Һ���
		else
		{
			// case1: �����Ǻ�ɫ
			{
				Node *uncle = gparent->left;
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
				Node* tmp;
				rbtree_right_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: �����Ǻ�ɫ,�ҵ�ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_left_rotate(root, gparent);
		}
	}

	rb_set_black(root->node);			// �����ڵ���Ϊ��ɫ
}

/************************************************************************
 * ��������: ���ڵ�node���뵽�������
 * ����˵��: root������ĸ�,node����Ľڵ�
************************************************************************/
static void rbtree_insert(RBRoot *root, Node *node)
{
	Node *y = NULL;
	Node *x = root->node;

	// 1.�����������һ�Ŷ��������,���ڵ���ӵ������������
	while(x)
	{
		y = x;
		if(node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	rb_parent(node) = y;

	if(y)
	{
		if(node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root->node = node;			// yΪ��,��node��Ϊ��

	// 2.���ýڵ����ɫ
	node->color = RED;

	// 3.������������Ϊһ�Ŷ��������
	rbtree_insert_fixup(root, node);
}


/************************************************************************
 * ��������: �����ڵ�
 * ����˵��: key:��ֵ,parent:���ڵ�,left:����,right:�Һ���
************************************************************************/
static Node* create_rbtree_node(Type key, Node *parent, Node *left, Node* right)
{
	Node *p = (Node *)malloc(sizeof(Node));
	if(!p)
		return NULL;

	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;
	p->color = RED;			// Ĭ��Ϊ��ɫ(�˴���ͬ)

	return p;
}

int insert_rbtree(RBRoot *root, Type key)
{	
	// �����������ͬ��ֵ�Ľڵ�
	// (�����������ͬ��ֵ�Ľڵ�,ע�͵���������仰)
	if(search(root->node, key) != NULL)
		return -1;

	Node* node = create_rbtree_node(key, NULL, NULL, NULL);
	if(!node)
		return -1;

	rbtree_insert(root, node);

	return 0;
}

/***********************************************************************
 * �����ɾ�����������ڴӺ������ɾ������ڵ��(�����ʧȥƽ��),�ٵ��ø�
 * ����Ŀ���ǽ�����ϴ�����һ�ź����
 * �����������һ�Ŷ�����������ڵ�ɾ�������Υ��(2)��(4)��(5)��������
 * Ϊ�˱��ڷ���,����xΪ����Ľڵ�(����һ������ĺ�ɫ,xԭ������ɫ������)
 * �����Ͳ���Υ������(5).��Ϊɾ���ڵ�y��,xռ����ԭ���ڵ��λ��.��Ȼɾ��
 * y(yΪ��ɫ),��ζ�ż���һ����ɫ�ڵ�,��ô���ڸ�λ��������һ����ɫ����.
 * ����,�����Ǽ���x����һ������ĺ�ɫ,�������ֲ���ɾ��y����ʧ�ĺ�ɫ�ڵ�
 * Ҳ�Ͳ���Υ������(5),����,x����������ԭ������ɫ,x������һ������ĺ�ɫ
 * ��x����ɫ�����Ǻ�+�ڻ��ߺڼӺ�,��Υ��������(1).
 * �������ٵ�����,�ɽ��Υ��������(2)��(4)��(5)��������ת�����˽��Υ��
 * ����(1)��(2)��(4)��������.
 * rb_tree_delete_fixup��˼�����:��x�������Ķ����ɫ������������(����
 * �����ƶ�),ֱ�������������̬:
 * (1): ���˵��: x�Ǻ�Ӻڽڵ�
 *		������: ֱ�Ӱ�x��Ϊ��ɫ,����.��ʱ���������ȫ���ָ�
 * (2): ���˵��: x�ǺڼӺڽڵ�,��x�Ǹ�.
 *		������: ʲô������,����.��ʱ���������ȫ���ָ�
 * (3): ���˵��: x�ǺڼӺڽڵ�,��x���Ǹ�
 *		������: ��������ֿ��Ի���Ϊ4�������
 *		case1: x�ǺڼӺڽڵ�,x���ֵܽڵ��Ǻ�ɫ(��ʱx�ĸ��ڵ��x���ֵܽڵ�
 *			   ���ӽڵ㶼�Ǻڽڵ�)
 *		  �������: (01)��x���ֵܽڵ���Ϊ����ɫ��
 *					(02)��x�ĸ��ڵ���Ϊ����ɫ��
 *					(03)��x�ĸ��ڵ��������
 *					(04)��������������x���ֵܽڵ�
 *		case2: x�Ǻ�+�ڽڵ�,x���ֵܽڵ��Ǻ�ɫ,x���ֵܽڵ���������Ӷ��Ǻ�ɫ
 *		  �������: (01)��x���ֵܽڵ���Ϊ����ɫ��
 *					(02)���á�x�ĸ��ڵ㡱Ϊ���µ�x�ڵ㡱
 *		case3: x�Ǻ�+�ڽڵ�,x���ֵܽڵ��Ǻ�ɫ;x���ֵܽڵ�������Ǻ�ɫ,
 *			   �Һ����Ǻ�ɫ��
 *		  ������ԣ�(01)��x�ֵܽڵ��������Ϊ��ɫ
 *					(02)��x�ֵܽڵ���Ϊ��ɫ
 *					(03)��x���ֵܽڵ��������
 *					(04)������,��������x���ֵܽڵ�
 *		case4: x�Ǻ�+�ڽڵ�,x���ֵܽڵ��Ǻ�ɫ;x���ֵܽڵ���Һ����Ǻ�ɫ��
 *			   x���ֵܽڵ������������ɫ
 *		  �������: (01)��x���ڵ���ɫ ��ֵ�� x���ֵܽڵ�
 *					(02)��x���ڵ���Ϊ��ɫ
 *					(03)��x�ֵܽڵ�����ӽ���Ϊ��ɫ
 *					(04)��x�ĸ��ڵ��������
 *					(05)����xΪ���ڵ�
 * ����˵��: root������ĸ�,node�������Ľڵ�(Ҳ����������˵��x)
 *           parent�������ڵ�ĸ��ڵ�
***********************************************************************/
static void rb_tree_delete_fixup(RBRoot *root, Node* node, Node* parent)
{
	Node *other;

	while((!node || rb_is_black(node)) && node != root->node)
	{
		if(parent->left == node)
		{
			other = parent->right;
			if(rb_is_red(other))
			{
				// case1: node���ֵ�other�Ǻ�ɫ��
				rb_set_black(other);
				rb_set_red(parent);
				rbtree_left_rotate(root, parent);
				other = parent->right;
			}

			if((!other->left || rb_is_black(other->left))
				&& (!other->right || rb_is_black(other->right)))
			{
				// case2: node���ֵ�other�Ǻ�ɫ��,��other����������Ҳ���Ǻ�ɫ��
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
					rbtree_right_rotate(root, other);
					other = parent->right;
				}

				// case3���������,����case4�����,��������ֱ�Ӵ���,û�м�else���
				// case4: node���ֵ�other�Ǻ�ɫ��,��other���Һ����Ǻ�ɫ��,����������ɫ
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				rbtree_left_rotate(root, parent);
				node = root->node;
				break;
			}
		}
		else
		{
			other = parent->left;
			if(rb_is_red(other))
			{
				// case1: node���ֵ�other�Ǻ�ɫ��
				rb_set_black(other);
				rb_set_red(parent);
				rbtree_right_rotate(root, parent);
				other = parent->left;
			}

			if((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node���ֵ�other�Ǻ�ɫ��,��other����������Ҳ�Ǻ�ɫ��
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->left || rb_is_red(other->left))
				{
					// case3: node���ֵ�other�Ǻ�ɫ��,��other�������Ǻ�ɫ,�Һ���Ϊ��ɫ
					rb_set_black(other->right);
					rb_set_red(other);
					rbtree_left_rotate(root, other);
					other = parent->left;
				}

				// case4: node���ֵ�other�Ǻ�ɫ��,��other���Һ����Ǻ�ɫ��,����������ɫ
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rbtree_right_rotate(root, parent);
				node = root->node;
				break;
			}
		}
	}

	if (node)
		rb_set_black(node);
}

/************************************************************************
 * ɾ���ڵ������:
 * ��һ��: �����������һ�Ŷ��������,���ڵ�ɾ��
 *		   ���ɾ����������������ɾ���ڵ�ķ�����һ����,��3�����:
 *		   (1): ��ɾ���ڵ�û�ж���,��ΪҶ�ڵ㣬��ôֱ�ӽ��ýڵ�ɾ��������
 *		   (2): ��ɾ���ڵ�ֻ��һ������,��ôֱ��ɾ���ýڵ�,���øýڵ��
 *				Ψһ�ӽڵ��������λ��
 *		   (3): ��ɾ���Ľڵ�����������,��ô���ҳ����ĺ�̽ڵ�,Ȼ��Ѻ��
 *				�ڵ�����ݸ��Ƹ�ɾ���ڵ�,֮��ɾ����̽ڵ�,��ʱ�ĺ�̽ڵ�
 *				�Ͳ������������ǿ��ӽڵ�.�����̽ڵ�û�зǿ��ӽڵ�,��
 *				���(1)����,��ֻ��һ������,�����(2)����
 * �ڶ���: ͨ����ת��������ɫ��һϵ������������,ʹ֮���³�Ϊһ�ź����
************************************************************************/
void rbtree_delete(RBRoot *root, Node *node)
{
	Node *child;
	Node *parent;
	int color;

	// ��ɾ���ڵ�����Һ��Ӷ���Ϊ�յ����
	if (node->left && node->right)
	{
		// �ñ�ɾ���ڵ�ĺ�̽ڵ������ɾ���ڵ�,Ȼ�󽫺�̽ڵ�ɾ��
		Node *replace = node;
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
			// node�ڵ��Ǹ��ڵ�,���¸��ڵ�
			root->node = replace;

		// child��ȡ���ڵ���Һ���,Ҳ����Ҫ�����Ľڵ�
		// ȡ���ڵ�϶�����������,��Ϊ����һ����̽ڵ�
		child = replace->right;
		parent = rb_parent(replace);
		// ����ȡ���ڵ����ɫ
		color = rb_color(replace);

		// ��ɾ���ڵ������ĺ�̽ڵ�ĸ��ڵ�
		if(parent == node)
			parent = replace;
		else
		{
			// child��Ϊ��
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
			rb_tree_delete_fixup(root, child, parent);
		free(node);

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

	// node���Ǹ��ڵ�
	if(parent)
	{
		if(parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root->node = child;

	if(color == BLACK)
		rb_tree_delete_fixup(root, child, parent);
	free(node);
}

// ɾ����ֵΪkey�Ľڵ�
void delete_rbtree(RBRoot *root, Type key)
{
	Node *z;

	if((z = search(root->node, key)) != NULL)
		rbtree_delete(root, z);
}


// ���ٺ����
static void rbtree_destroy(RBTree tree)
{
	if(!tree)
		return;

	if(tree->left)
		rbtree_destroy(tree->left);
	if(tree->right)
		rbtree_destroy(tree->right);

	free(tree);
}

void destroy_rbtree(RBRoot* root)
{
	if(root)
		rbtree_destroy(root->node);
	free(root);
}

/************************************************************************
 * ��������: ��ӡ�����
 * ��������: tree: ������Ľڵ�,key�ڵ�ļ�ֵ
 *			 direction: 0��ʾ�ýڵ��Ǹ��ڵ�,-1��ʾ�ýڵ������ĸ��ڵ������
						1��ʾ�ýڵ������ĸ��ڵ���Һ���
************************************************************************/
static void rbtree_print(RBTree tree, Type key, int direction)
{
	if(tree)
	{
		if(0 == direction)	// tree�Ǹ��ڵ�
			printf("%2d(B) is root\n", tree->key);
		else
			printf("%2d(%c) is %2d's %6s child\n", tree->key, rb_is_red(tree) ? 'R' : 'B',
				key, direction == 1 ? "right" : "left");

		rbtree_print(tree->left, tree->key, -1);
		rbtree_print(tree->right, tree->key, 1);
	}
}

void print_rbtree(RBRoot *root)
{
	if(root && root->node)
		rbtree_print(root->node, root->node->key, 0);
}

