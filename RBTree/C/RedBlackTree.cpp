
/***********************************************************************
 * C语言实现红黑树(Red Black Tree)
 * author： 梁基圣
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
 * 函数描述: 创建红黑树
 * 参    数: 无
 * 返 回 值: 红黑树的根
************************************************************************/
RBRoot* create_rbtree()
{
	RBRoot *root = (RBRoot*)malloc(sizeof(RBRoot));
	root->node = NULL;

	return root;
}

// 前序遍历红黑树
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

// 中序遍历红黑树
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

// 后序遍历红黑树
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
 * 函数描述: (递归实现)查找红黑树x中键值为key的节点
 * 返 回 值: 返回找到的节点
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
 * 函数描述: (非递归实现)查找红黑树x中键值为key的节点
 * 返 回 值: 返回找到的节点
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

// 返回tree为根节点的红黑树的最小节点
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

// 返回tree为根节点的红黑树的最大节点
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


// 查找x的后继节点,即红黑树中数据值大于该节点的最小节点
static Node* rbtree_successor(RBTree x)
{
	// 如果x存在右孩子,则x的后继节点为"以其右孩子为根的子树的最小节点"
	if(x->right)
		return minimum(x->right);

	// 如果x没有右孩子.则x有以下两种可能:
	// 1.x是一个左孩子,则x的后继节点为它的父节点
	// 2.x是一个右孩子,则查找x的最低父节点,并且该父节点要具有左孩子
	//   找到的这个最低父节点就是x的后继节点
	Node *y = x->parent;
	while(y && x == y->right)
	{
		x = y;
		y = y->parent;
	}

	return y;
}

// 找节点x的前驱节点,即查找红黑树中数据值小于该节点的最大节点
static Node* rbtree_predecessor(RBTree x)
{
	// 如果x存下左孩子,则x的前驱节点为"以其左孩子为根的子树的最大节点"
	if(x->left)
		return maximum(x->left);

	// 如果x没有左孩子,则x有以下两种可能
	// 1.x是一个右孩子,则x的前驱节点为它的父节点
	// 2.x是一个左孩子,则查找x的最低父节点,并且该父节点要具有右孩子
	//   找到的这个最低父节点就是x的前驱节点
	Node* y = x->parent;
	while(y && x == y->left)
	{
		x = y;
		y = y->parent;
	}

	return y;
}


/***********************************************************************
 * 对红黑树的节点x进行左旋转
 * 左旋示意图
 *              px                                    px
 *             /                                     /
 *            x                                     y
 *           / \          --(左旋)-->              / \
 *         lx   y                                 x   ry
 *             / \                               / \
 *           ly   ry                            lx  ly
 *
 *
***********************************************************************/
static void rbtree_left_rotate(RBRoot *root, Node* x)
{
	Node* y = x->right;				// 设置x的右孩子为y
	
	x->right = y->left;				// 将y的左孩子设为x的右孩子
	if(y->left)						// 如果y的左孩子非空,将x设为y的左孩子的父亲
		y->left->parent = x;

	y->parent = x->parent;			// 将x的父亲设为y的父亲

	if(NULL == x->parent)			// 如果x的父亲为空,则将y设为根节点
		root->node = y;
	else
	{
		if(x == x->parent->left)	// 如果x是它父节点的左孩子,则将y设为x的父节点的左孩子
			x->parent->left = y;
		else
			x->parent->right = y;	// 如果x是它父节点的右孩子,则将y设为x的父节点的右孩子
	}

	y->left = x;					// 将x设为y的左孩子
	x->parent = y;					// 将x的父节点设为y
}

/************************************************************************
 * 对红黑树的节点y进行右旋转
 * 右旋示意图(对节点y进行右旋)
 *               py                            py
 *              /                             /
 *             y                             x
 *            / \     --(右旋)-->           / \
 *           x   ry                        lx  y
 *          / \                               / \
 *        lx   rx                            rx  ry
 *
************************************************************************/
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
	Node* x = y->left;				// 设置x是当前节点的左孩子

	y->left = x->right;				// 将x的右孩子设置为y的左孩子
	if(x->right)					// 如果x的右孩子不为空的话,将y设置为x的右孩子的父亲
		x->right->parent = y;

	x->parent = y->parent;			// 将y的父亲设为x的父亲

	if(NULL == y->parent)
		root->node = x;
	else
	{
		if(y == y->parent->right)	// 如果y是它父节点的右孩子,则将x设为y的父节点的右孩子
			y->parent->right = x;
		else
			y->parent->left = x;	// 如果y是它父节点的左孩子,则将x设为y的父节点的左孩子
	}

	x->right = y;					// 将y设为x的右孩子
	y->parent = x;					// y的父节点设为x
}


/************************************************************************
 * 红黑树插入修正函数,在向红黑树中插入节点后(失去平衡),在调用该函数
 * 目的是将它重新塑造成一个红黑树,调整的思想就是将红色的节点移到根节点
 * 然后,将根节点设为黑色
 * 根据被插入节点的父节点的情况,可以将当节点node被着色为红色节点,并插入
 * 二叉树划分为三种情况来处理
 * 1.情况说明: 被插入的节点是根节点
 *   处理方法: 直接把此节点涂为黑色
 * 2.情况说明: 被插入的节点的父节点是黑色的
 *   处理情况: 什么也不需要做,节点被插入后,仍然是红黑树
 * 3.情况处理: 被插入节点的父节点是红色
 *   处理方法: 该情况与红黑树的特性4相冲突.在这种情况下,被插入节点是一定
 *			   非空祖父节点的(因为父节点为红色,而红色节点不能作为根节点);
 *			   进一步讲,被插入节点也一定存在叔叔节点(即使叔叔节点为空,我
 *			   们也视之存在,空节点本身就是黑色节点).依据叔叔节点的情况,将
 *			   这种情况进一步划分为3种情况(case)
 *	 case1: 当前节点的父节点是红色,且当前节点的祖父节点的另一个子节点(叔叔
 *			节点)也是红色
 *		 处理策略: (01) 将“父节点”设为黑色。
 *				   (02) 将“叔叔节点”设为黑色。
 *				   (03) 将“祖父节点”设为“红色”。
 *				   (04) 将“祖父节点”设为“当前节点”(红色节点)
 *					   即，之后继续对“当前节点”进行操作
 *	 case2: 当前节点的父节点是红色,叔叔节点是黑色,且当前节点是其父节点的右孩子
 *		 处理策略: (01)将父节点作为新的当前节点
 *				   (02)以新的当前节点为支点进行左旋
 *	 case3: 当前节点的父节点是红色,叔叔节点是黑色,且当前节点是其父节点的左孩子
 *		 处理策略: (01)将父节点设为黑色
 *				   (02)将祖父节点设为红色
 *				   (03)以祖父节点为支点进行右旋
 * 参数说明: root红黑树的根,node插入的节点
************************************************************************/
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
	Node *parent;
	Node *gparent;

	// 若父节点存在且父节点的颜色是红色
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);

		// 若父节点是祖先节点的左孩子
		if(parent == gparent->left)
		{
			// case1: 叔叔节点是红色
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

			// case2: 叔叔是黑色,且当前节点是右孩子
			if(node == parent->right)
			{
				Node *tmp;
				rbtree_left_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: 叔叔是黑色,且当前节点是左孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_right_rotate(root, gparent);
		}
		// 父节点是祖先节点的右孩子
		else
		{
			// case1: 叔叔是红色
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

			// case2: 叔叔是黑色,且当前节点是左孩子
			if(parent->left == node)
			{
				Node* tmp;
				rbtree_right_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			// case3: 叔叔是黑色,且当前节点是左孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_left_rotate(root, gparent);
		}
	}

	rb_set_black(root->node);			// 将根节点设为黑色
}

/************************************************************************
 * 函数描述: 将节点node插入到红黑树中
 * 参数说明: root红黑树的根,node插入的节点
************************************************************************/
static void rbtree_insert(RBRoot *root, Node *node)
{
	Node *y = NULL;
	Node *x = root->node;

	// 1.将红黑树当做一颗二叉查找树,将节点添加到二叉查找树中
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
		root->node = node;			// y为空,则将node设为根

	// 2.设置节点的颜色
	node->color = RED;

	// 3.将它重新修正为一颗二叉查找树
	rbtree_insert_fixup(root, node);
}


/************************************************************************
 * 函数描述: 创建节点
 * 参数说明: key:键值,parent:父节点,left:左孩子,right:右孩子
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
	p->color = RED;			// 默认为红色(此处不同)

	return p;
}

int insert_rbtree(RBRoot *root, Type key)
{	
	// 不允许插入相同键值的节点
	// (若允许插入相同键值的节点,注释掉下面的两句话)
	if(search(root->node, key) != NULL)
		return -1;

	Node* node = create_rbtree_node(key, NULL, NULL, NULL);
	if(!node)
		return -1;

	rbtree_insert(root, node);

	return 0;
}

/***********************************************************************
 * 红黑树删除修正函数在从红黑树中删除插入节点后(红黑树失去平衡),再调用该
 * 函数目的是将它冲洗塑造成一颗红黑树
 * 将红黑树当做一颗二叉查找树将节点删除后可能违反(2)、(4)、(5)三个特性
 * 为了便于分析,假设x为代替的节点(包含一个额外的黑色,x原本的颜色还存在)
 * 这样就不会违反特性(5).因为删除节点y后,x占据了原来节点的位置.既然删除
 * y(y为黑色),意味着减少一个黑色节点,那么再在该位置上增加一个黑色即可.
 * 这样,当我们假设x包含一个额外的黑色,就正好弥补了删除y所丢失的黑色节点
 * 也就不会违反特性(5),现在,x不仅包含它原来的颜色,x还包含一个额外的黑色
 * 即x的颜色属性是红+黑或者黑加黑,它违反了特性(1).
 * 现在面临的问题,由解决违反了特性(2)、(4)、(5)三个特性转换成了解决违反
 * 特性(1)、(2)、(4)三个特性.
 * rb_tree_delete_fixup的思想就是:将x所包含的额外黑色不断沿树上移(往根
 * 方向移动),直到出现下面的姿态:
 * (1): 情况说明: x是红加黑节点
 *		处理方法: 直接把x设为黑色,结束.此时红黑树性质全部恢复
 * (2): 情况说明: x是黑加黑节点,且x是根.
 *		处理方法: 什么都不做,结束.此时红黑树性质全部恢复
 * (3): 情况说明: x是黑加黑节点,且x不是根
 *		处理方法: 这种情况又可以划分为4中子情况
 *		case1: x是黑加黑节点,x的兄弟节点是红色(此时x的父节点和x的兄弟节点
 *			   的子节点都是黑节点)
 *		  处理策略: (01)将x的兄弟节点设为“黑色”
 *					(02)将x的父节点设为“红色”
 *					(03)对x的父节点进行左旋
 *					(04)左旋后，重新设置x的兄弟节点
 *		case2: x是黑+黑节点,x的兄弟节点是黑色,x的兄弟节点的两个孩子都是黑色
 *		  处理策略: (01)将x的兄弟节点设为“红色”
 *					(02)设置“x的父节点”为“新的x节点”
 *		case3: x是黑+黑节点,x的兄弟节点是黑色;x的兄弟节点的左孩子是红色,
 *			   右孩子是黑色的
 *		  处理策略：(01)将x兄弟节点的左孩子设为黑色
 *					(02)将x兄弟节点设为红色
 *					(03)对x的兄弟节点进行右旋
 *					(04)右旋后,重新设置x的兄弟节点
 *		case4: x是黑+黑节点,x的兄弟节点是黑色;x的兄弟节点的右孩子是红色的
 *			   x的兄弟节点的左孩子任意颜色
 *		  处理策略: (01)将x父节点颜色 赋值给 x的兄弟节点
 *					(02)将x父节点设为黑色
 *					(03)将x兄弟节点的右子节设为黑色
 *					(04)对x的父节点进行左旋
 *					(05)设置x为根节点
 * 参数说明: root红黑树的根,node待修正的节点(也就是上面所说的x)
 *           parent待修正节点的父节点
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
				// case1: node的兄弟other是红色的
				rb_set_black(other);
				rb_set_red(parent);
				rbtree_left_rotate(root, parent);
				other = parent->right;
			}

			if((!other->left || rb_is_black(other->left))
				&& (!other->right || rb_is_black(other->right)))
			{
				// case2: node的兄弟other是黑色的,且other的两个孩子也都是黑色的
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
					rbtree_right_rotate(root, other);
					other = parent->right;
				}

				// case3情况结束后,会变成case4的情况,所以这里直接处理,没有加else语句
				// case4: node的兄弟other是黑色的,且other的右孩子是红色的,左孩子任意颜色
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
				// case1: node的兄弟other是红色的
				rb_set_black(other);
				rb_set_red(parent);
				rbtree_right_rotate(root, parent);
				other = parent->left;
			}

			if((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// case2: node的兄弟other是黑色的,且other的两个孩子也是黑色的
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if(!other->left || rb_is_red(other->left))
				{
					// case3: node的兄弟other是黑色的,且other的左孩子是红色,右孩子为黑色
					rb_set_black(other->right);
					rb_set_red(other);
					rbtree_left_rotate(root, other);
					other = parent->left;
				}

				// case4: node的兄弟other是黑色的,且other的右孩子是红色的,左孩子任意颜色
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
 * 删除节点分两步:
 * 第一步: 将红黑树当做一颗二叉查找树,将节点删除
 *		   这和删除常规二叉查找树中删除节点的方法是一样的,分3中情况:
 *		   (1): 被删除节点没有儿子,即为叶节点，那么直接将该节点删除就行了
 *		   (2): 被删除节点只有一个儿子,那么直接删除该节点,并用该节点的
 *				唯一子节点代替它的位置
 *		   (3): 被删除的节点有两个儿子,那么先找出它的后继节点,然后把后继
 *				节点的内容复制给删除节点,之后删除后继节点,此时的后继节点
 *				就不可能有两个非空子节点.如果后继节点没有非空子节点,则按
 *				情况(1)处理,若只有一个儿子,则按情况(2)处理
 * 第二步: 通过旋转和重新着色等一系列来修正该树,使之重新成为一颗红黑树
************************************************************************/
void rbtree_delete(RBRoot *root, Node *node)
{
	Node *child;
	Node *parent;
	int color;

	// 被删除节点的左右孩子都不为空的情况
	if (node->left && node->right)
	{
		// 用被删除节点的后继节点替代被删除节点,然后将后继节点删除
		Node *replace = node;
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
			// node节点是根节点,更新根节点
			root->node = replace;

		// child是取代节点的右孩子,也是需要调整的节点
		// 取代节点肯定不存在左孩子,因为它是一个后继节点
		child = replace->right;
		parent = rb_parent(replace);
		// 保存取代节点的颜色
		color = rb_color(replace);

		// 被删除节点是它的后继节点的父节点
		if(parent == node)
			parent = replace;
		else
		{
			// child不为空
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
	// 保存取代节点的颜色
	color = node->color;

	if(child)
		child->parent = parent;

	// node不是根节点
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

// 删除键值为key的节点
void delete_rbtree(RBRoot *root, Type key)
{
	Node *z;

	if((z = search(root->node, key)) != NULL)
		rbtree_delete(root, z);
}


// 销毁红黑树
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
 * 函数描述: 打印红黑树
 * 参数描述: tree: 红黑树的节点,key节点的键值
 *			 direction: 0表示该节点是根节点,-1表示该节点是它的父节点的左孩子
						1表示该节点是它的父节点的右孩子
************************************************************************/
static void rbtree_print(RBTree tree, Type key, int direction)
{
	if(tree)
	{
		if(0 == direction)	// tree是根节点
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

