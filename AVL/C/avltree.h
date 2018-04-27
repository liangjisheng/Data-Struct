
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

// AVL树是根据它的发明者G.M. Adelson-Velsky和E.M. Landis命名的
// 二叉平衡树:任何节点的两个子树的高度差别都小于等于1
// avl树的查找、插入和删除在平均和最坏的情况下都是O(logn)
// http://www.cnblogs.com/skywang12345/p/3576969.html

typedef int Type;

typedef struct AVLTreeNode
{
	Type key;
	int height;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
}Node, *AVLTree;

// 获取AVL树的高度
int avltree_height(AVLTree tree);

// 前序遍历"AVL树"
void preorder_avltree(AVLTree tree);
// 中序遍历"AVL树"
void inorder_avltree(AVLTree tree);
// 后序遍历"AVL树"
void postorder_avltree(AVLTree tree);

void print_avltree(AVLTree tree, Type key, int direction);

// (递归实现)查找"AVL树x"中键值为key的节点
Node* avltree_search(AVLTree x, Type key);
// (非递归实现)查找"AVL树x"中键值为key的节点
Node* iterative_avltree_search(AVLTree x, Type key);

// 查找最小结点：返回tree为根结点的AVL树的最小结点
Node* avltree_minimum(AVLTree tree);
// 查找最大结点：返回tree为根结点的AVL树的最大结点
Node* avltree_maximum(AVLTree tree);

// 将结点插入到AVL树中，返回根节点,可以插入相同的值
Node* avltree_insert(AVLTree tree, Type key);

// 将结点插入到AVL树中，返回根节点,不可以插入相同的值
Node* avltree_insert_1(AVLTree tree, Type key);

// 删除结点(key是节点值)，返回根节点
Node* avltree_delete(AVLTree tree, Type key);

// 销毁AVL树
void destroy_avltree(AVLTree tree);

#endif // _AVL_TREE_H_