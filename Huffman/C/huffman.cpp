
/**
 * Huffman��(C����): C����ʵ�ֵ�Huffman��
 * ����Huffman��ʱ��ʹ�õ�����С��
 */

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

// ������С��
extern void create_minheap(Type a[], int size);
// �½�һ���ڵ㣬������С������С�ڵ�����ݸ��Ƹ��ýڵ�
extern HuffmanNode* dump_from_minheap();
// ��data���뵽������У�0��ʾ�ɹ���-1��ʾʧ��
extern int dump_to_minheap(HuffmanNode *node);
// ������С��
extern void destroy_minheap();


// ǰ�����
void preorder_huffman(HuffmanTree tree)
{
	if (tree)
	{
		printf("%d ", tree->key);
		preorder_huffman(tree->left);
		preorder_huffman(tree->right);
	}
}

// �������
void inorder_huffman(HuffmanTree tree)
{
	if (tree)
	{
		inorder_huffman(tree->left);
		printf("%d ", tree->key);
		inorder_huffman(tree->right);
	}
}

// �������
void postorder_huffman(HuffmanTree tree)
{
	if (tree)
	{
		postorder_huffman(tree->left);
		postorder_huffman(tree->right);
		printf("%d ", tree->key);
	}
}

// ����Huffman���ڵ�
HuffmanNode* huffman_create_node(Type key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent)
{
	HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
	if (!node)
		return NULL;

	node->key = key;
	node->left = left;
	node->right = right;
	node->parent = parent;

	return node;
}

// ����huffman��
HuffmanNode* create_huffman(Type arr[], int size)
{
	int i;
	HuffmanNode *left, *right, *parent;

	// ���������Ӧ����С��
	create_minheap(arr, size);

	for (i = 0; i < size - 1; ++i)
	{
		left = dump_from_minheap();		// ���½ڵ�������
		right = dump_from_minheap();	// ��β����Һ���

		// �½�parent�ڵ㣬���Һ��ӷֱ���left/right
		// parent�Ĵ�С�����Һ���֮��
		parent = huffman_create_node(left->key + right->key, left, right, NULL);
		left->parent = parent;
		right->parent = parent;

		// ��parent�ڵ����ݿ�������С����
		if (dump_to_minheap(parent) != 0)
		{
			printf("����ʧ��\n��������\n");
			destroy_huffman(parent);
			parent = NULL;
			break;
		}
	}

	// ������С��
	destroy_minheap();

	return parent;
}

// ����Huffman��
void destroy_huffman(HuffmanTree tree)
{
	if (NULL == tree)
		return ;

	if (tree->left)
		destroy_huffman(tree->left);
	if (tree->right)
		destroy_huffman(tree->right);

	free(tree);
}

/*
 * ��ӡ"Huffman��"
 *
 * tree       -- Huffman���Ľڵ�
 * key        -- �ڵ�ļ�ֵ 
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */
void huffman_print(HuffmanTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree�Ǹ��ڵ�
            printf("%2d is root\n", tree->key, key);
        else                // tree�Ƿ�֧�ڵ�
            printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right" : "left");

        huffman_print(tree->left, tree->key, -1);
        huffman_print(tree->right,tree->key,  1);
    }
}

void print_huffman(HuffmanTree tree)
{
	if (tree!=NULL)
		huffman_print(tree, tree->key, 0);
}
