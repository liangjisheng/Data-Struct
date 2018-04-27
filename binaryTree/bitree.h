
/*
 * filename: bitree.h
 * author: 梁基圣
 * date: 2017/10/17
 */

#ifndef BITREE_H_
#define BITREE_H_

#include "DoubleLink.h"

// define a binary tree node
typedef struct BiTreeNode_
{
	void *data;
	struct BiTreeNode_ *left;
	struct BiTreeNode_ *right;
}BiTreeNode;

// define a binary tree
typedef struct BiTree_
{
	int size;			// number of the elements in the tree.(二叉树中节点总数)
	BiTreeNode *root;	// root node
	int (*compare)(const void *key1, const void *key2);	// 节点数据信息的比较操作
	void (*destroy)(void *data);		// 销毁二叉树
}BiTree;

// destroy
void destroy(void *data);
// create_tree
int create_tree(BiTree *tree, BiTreeNode *node);

// 初始化二叉树,建立空的二叉树,此时它没有任何节点,这是二叉树进行后续操作的前提
void bitree_init(BiTree *tree, void(*destroy)(void* data));
// 销毁二叉树
void bitree_destroy(BiTree *tree);
// 将data中的信息插入到当前node节点的左指针域,当node为NULL时,从根节点位置插入
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);
// 将data中的信息插入到当前node节点的右指针域,当node为NULL时,从根节点位置插入
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);
// 删除以node节点为根的子树的左子树,当node == NULL时,则为删除整个二叉树
void bitree_rem_left(BiTree *tree, BiTreeNode *node);
// 删除以node节点为根的子树的右子树,当node == NULL时,则为删除整个二叉树
void bitree_rem_right(BiTree *tree, BiTreeNode *node);
// 将两个儿二叉树合并为以data域为根的新二叉树
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

// 前序遍历二叉树
int preorder(const BiTreeNode *node, DoubleLink<void*> *list);
// 中序遍历二叉树
int inorder(const BiTreeNode *node, DoubleLink<void*> *list);
// 后序遍历二叉树
int postorder(const BiTreeNode *node, DoubleLink<void*> *list);

#define bitree_size(tree) ((tree)->size)		// 获取大小
#define bitree_root(tree) ((tree)->root)		// 获取跟节点
#define bitree_is_eob(node) ((node) == NULL)	// 判断分支是否结束
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)	// 判断是否是叶子节点
#define bitree_data(node) ((node)->data)		// 获取数据域
#define bitree_left(node) ((node)->left)		// 获取左节点
#define bitree_right(node) ((node)->right)		// 获取右节点

#endif // BITREE_H_