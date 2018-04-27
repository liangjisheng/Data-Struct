
/*
 * filename: bitree.h
 * author: 梁基圣
 * date: 2017/10/17
 */

#include <string.h>
#include <stdlib.h>
#include "bitree.h"

void destroy(void *data) 
{
	free(data);
	return ;
}

// 递归创建二叉树,递归退出条件为输入#符号
// 注意:只能实现插入简单的数字(0-9)
int create_tree(BiTree *tree, BiTreeNode *node)
{
	int ret = 0;
	int *int_ptr = NULL;
	char ch = '\0';

	scanf("%c", &ch);
	if(ch == '#')
		return 0;

	int_ptr = (int*)malloc(sizeof(int));
	if(!int_ptr)
		return -1;

	*int_ptr = ch - 48;

	if(!node)
	{
		bitree_init(tree, destroy);
		ret = bitree_ins_left(tree, NULL, (void*)int_ptr);
		if(ret != 0)
		{
			free(int_ptr);
			return -1;
		}
		printf("root is %d\n", *(int *)bitree_data(tree->root));
		create_tree(tree, tree->root);
	}
	else
	{
		// insert the data into left tree
		ret = bitree_ins_left(tree, node, (void *)int_ptr);
		if(ret != 0)
		{
			free(int_ptr);
			return -1;
		}
		printf("node: %d  's left node is :%d\n", *(int *)bitree_data(node),
			*(int *)bitree_data(node->left));
		ret = create_tree(tree, node->left);

		scanf("%c", &ch);
		if(ch == '#')
			return 0;

		int_ptr = (int *)malloc(sizeof(int));
		if(!int_ptr)
			return -1;

		*int_ptr = ch - 48;
		// insert the data into right tree
		ret = bitree_ins_right(tree, node, (void *)int_ptr);
		if(ret != 0)
		{
			free(int_ptr);
			return -1;
		}
		printf("node: %d  's right node is :%d\n", *(int *)bitree_data(node),
			*(int *)bitree_data(node->right));
		ret = create_tree(tree, node->right);
	}

	return 0;
}

void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
	tree->size = 0;
	tree->root = NULL;
	tree->destroy = destroy;
	return ;
}

void bitree_destroy(BiTree *tree)
{
	// remove all the nodes from the tree
	bitree_rem_left(tree, NULL);
	// clear the tree
	memset(tree, 0, sizeof(BiTree));
	return ;
}

int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	if(!node)
	{
		// 当node为NULL时,插入根节点的左边
		if(bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	}
	else
	{
		// 当node不为NULL时,插入node节点的左边
		if(bitree_left(node))
			return -1;
		position = &node->left;
	}

	// allocate memory
	new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	if(!new_node)
		return -1;

	// insert the node into the tree
	new_node->data = (void *)data;
	new_node->left = new_node->right = NULL;

	*position = new_node;
	tree->size++;

	return 0;
}

int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	if(!node)
	{
		if(bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	}
	else
	{
		if(bitree_right(node))
			return -1;
		position = &node->right;
	}

	// allocate memory
	new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode));
	if(!new_node)
		return -1;

	new_node->data = (void *)data;
	new_node->left = new_node->right = NULL;

	*position = new_node;
	tree->size++;
	return 0;
}

void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;

	// Do not allow remove from an empty tree.
	if(bitree_size(tree) == 0)
		return ;

	// NULL表示删除整个树
	if(!node)
		position = &tree->root;
	else
		// 否则删除以node节点为根的子树
		position = &node->left;

	// remove the node
	if(*position)
	{
		// 后序遍历删除节点且只能是后序遍历删除节点,因为一旦
		// 根节点删除后,那么后面没删除的节点就会造成内存泄露
		// 所以根节点是最后删除
		// 先删除*position的左子树
		bitree_rem_left(tree, *position);
		// 后删除*position的右子树
		bitree_rem_right(tree, *position);

		// 最后删除跟节点
		if(tree->destroy)
			tree->destroy((*position)->data);
		free(*position);
		*position = NULL;

		tree->size--;
	}

	return ;
}

void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;

	if(bitree_size(tree) == 0)
		return ;

	if(!node)
		position = &tree->root;
	else
		position = &node->right;

	// remove the node
	if(*position)
	{
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);

		if(tree->destroy)
			tree->destroy((*position)->data);
		free(*position);
		*position = NULL;

		tree->size--;
	}

	return ;
}

int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
	// Initialize the merged tree
	bitree_init(merge, left->destroy);

	// Insert the data for root node of the merged tree
	if(bitree_ins_left(merge, NULL, data))
	{
		bitree_destroy(merge);
		return -1;
	}

	// Merge the two binary trees into a single binary tree
	bitree_root(merge)->left = bitree_root(left);
	bitree_root(merge)->right = bitree_root(right);

	// Adjust the size of the new tree
	merge->size = merge->size + bitree_size(left) + bitree_size(right);

	// do not let the original trees access the merged nodes
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}

int preorder(const BiTreeNode *node, DoubleLink<void*> *list)
{
	if(node)
	{
		list->append_last(node->data);
		preorder(node->left, list);
		preorder(node->right, list);
	}

	return 0;
}

int inorder(const BiTreeNode *node, DoubleLink<void*> *list)
{
	if(node)
	{
		inorder(node->left, list);
		list->append_last(node->data);
		inorder(node->right, list);
	}

	return 0;
}

int postorder(const BiTreeNode *node, DoubleLink<void*> *list)
{
	if(node)
	{
		postorder(node->left, list);
		postorder(node->right, list);
		list->append_last(node->data);
	}

	return 0;
}

