
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode
{
	Type key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}Node, *BSTree;

// 前序遍历二叉查找树
void preorder_bstree(BSTree tree);
// 中序遍历二叉查找树
void inorder_bstree(BSTree tree);
// 后序遍历二叉查找树
void postorder_bstree(BSTree tree);

// (递归实现)查找二叉查找树中键值为key的节点
Node* bstree_search(BSTree tree, Type key);
// (非递归实现)查找二叉查找树中键值为key的节点
Node* iterative_bstree_search(BSTree tree, Type key);

// 查找最小节点:返回tree为根节点的二叉树的最小节点
Node* bstree_minimum(BSTree tree);
// 查找最大节点:返回tree为根节点的二叉树的最大节点
Node* bstree_maximum(BSTree tree);

// 找节点x的后继节点(中序遍历).即查找二叉树中数据值大于该节点的最小节点
Node* bstree_successor(Node* x);
// 找节点x的前驱节点(中序遍历).及查找二叉树中数据值小于该节点的最大节点
Node* bstree_predecessor(Node *x);

// 将节点插入到二叉树中,并返回根节点
Node* bstree_insert(BSTree tree, Type key);

// 删除节点(key为节点的值),并返回根节点
Node* bstree_delete(BSTree tree, Type key);

// 删除节点(key为节点的值),并返回根节点
Node* bstree_delete_1(BSTree tree, Type key);

// 删除节点(key为节点的值),并返回根节点
// bstree_delete_2()的实现不是正确的
Node* bstree_delete_2(BSTree tree, Type key);

// 销毁二叉树
void bstree_destroy(BSTree tree);

// 打印二叉树
// tree表示二叉树的节点,key表示节点的键值,direction表示节点的类型
// direction == 0,表示是根节点
// direction == -1,表示该节点是它的父节点的左孩子
// direction == 1,表示该节点是它的父节点的右孩子
void bstree_print(BSTree tree, Type key, int direction);

#endif // _BINARY_SEARCH_TREE_H_