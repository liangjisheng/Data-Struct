
// 红黑树(Red-Black Tree，简称R-B Tree)，它一种特殊的二叉查找树。
// 红黑树是特殊的二叉查找树，意味着它满足二叉查找树的特征：
// 任意一个节点所包含的键值，大于等于左孩子的键值，小于等于右孩子的键值。
// 除了具备该特性之外，红黑树还包括许多额外的信息。
// 红黑树的每个节点上都有存储位表示节点的颜色，颜色是红(Red)或黑(Black)

// 红黑树的特性:
// (1)每个节点或者是黑色或者是红色
// (2)根节点是黑色
// (3)每个叶子节点是黑色.[注意: 这里的叶子节点是指为空的叶子节点]
// (4)如果一个节点是红色的,则它的子节点必须是黑色的
// (5)从一个节点到该节点的子孙节点的所有路径上包含相同数据的黑节点

// 关于5个特性中,需要注意以下两点:
// 1.特性(3)中的叶子节点,是指为空(NULL)的节点
// 2.特性(5),确保没有一条路径会比其他路径长出两倍,因而,红黑树是相对接近平衡的二叉树

#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED		0		// 红色节点
#define BLACK	1		// 黑色节点

typedef int Type;

// 红黑树的节点
typedef struct RBTreeNode
{
	unsigned char color;		// 颜色(RED或BLACK)
	Type key;					// 关键字
	struct RBTreeNode *left;	// 左孩子
	struct RBTreeNode *right;	// 右孩子
	struct RBTreeNode *parent;	// 父节点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root
{
	Node *node;
}RBRoot;


// 创建红黑树，返回红黑树的根
RBRoot* create_rbtree();

// 销毁红黑树
void destroy_rbtree(RBRoot* root);

// 将节点插入到红黑树中,成功返回0,失败返回-1
int insert_rbtree(RBRoot *root, Type key);

// 删除节点(key为节点的值)
void delete_rbtree(RBRoot *root, Type key);


// 前序遍历红黑树
void preorder_rbtree(RBRoot *root);

// 中序遍历红黑树
void inorder_rbtree(RBRoot *root);

// 后序遍历红黑树
void postorder_rbtree(RBRoot *root);


// (递归实现)查找红黑树中键值为key的节点,找到返回0,否则返回-1
int rbtree_search(RBRoot *root, Type key);

// (非递归实现)查找红黑树中键值为key的节点,找到返回0,否则返回-1
int iterative_rbtree_search(RBRoot *root, Type key);


// 返回最小节点的值(将值保存到val中).找到的话,返回0,否则返回-1
int rbtree_minimum(RBRoot *root, int *val);

// 返回最大节点的值(将值保存到val中).找到的话,返回0,否则返回-1
int rbtree_maximum(RBRoot *root, int *val);

// 打印红黑树
void print_rbtree(RBRoot *root);

#endif // _RED_BLACK_TREE_H_