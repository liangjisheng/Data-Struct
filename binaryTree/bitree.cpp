
/*
 * filename: bitree.h
 * author: ����ʥ
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

// �ݹ鴴��������,�ݹ��˳�����Ϊ����#����
// ע��:ֻ��ʵ�ֲ���򵥵�����(0-9)
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
		// ��nodeΪNULLʱ,������ڵ�����
		if(bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	}
	else
	{
		// ��node��ΪNULLʱ,����node�ڵ�����
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

	// NULL��ʾɾ��������
	if(!node)
		position = &tree->root;
	else
		// ����ɾ����node�ڵ�Ϊ��������
		position = &node->left;

	// remove the node
	if(*position)
	{
		// �������ɾ���ڵ���ֻ���Ǻ������ɾ���ڵ�,��Ϊһ��
		// ���ڵ�ɾ����,��ô����ûɾ���Ľڵ�ͻ�����ڴ�й¶
		// ���Ը��ڵ������ɾ��
		// ��ɾ��*position��������
		bitree_rem_left(tree, *position);
		// ��ɾ��*position��������
		bitree_rem_right(tree, *position);

		// ���ɾ�����ڵ�
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

