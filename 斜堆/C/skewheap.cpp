
#include <stdio.h>
#include <stdlib.h>
#include "skewheap.h"

void preorder_skewheap(SkewHeap heap)
{
	if (heap)
	{
		printf("%d ", heap->key);
		preorder_skewheap(heap->left);
		preorder_skewheap(heap->right);
	}
}

void inorder_skewheap(SkewHeap heap)
{
	if (heap)
	{
		inorder_skewheap(heap->left);
		printf("%d ", heap->key);
		inorder_skewheap(heap->right);
	}
}

void postorder_skewheap(SkewHeap heap)
{
	if (heap)
	{
		postorder_skewheap(heap->left);
		postorder_skewheap(heap->right);
		printf("%d ", heap->key);
	}
}

// ���������ڵ������
static void swap_skewheap_node(SkewNode *x, SkewNode *y)
{
	SkewNode tmp = *x;
	*x = *y;
	*y = tmp;
}

// ��Сֵ
int skewheap_minimum(SkewHeap heap, Type* pval)
{
	if (heap)
		return -1;

	*pval = heap->key;

	return 0;
}

// �ϲ�б��x��б��y�����غϲ��õ��ĸ��ڵ�
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y)
{
	if (NULL == x)
		return y;
	if (NULL == y)
		return x;

	//  �ϲ�x��yʱ����x��Ϊ�ϲ�������ĸ��������Ǳ�֤x��keyС��y��key
	if (x->key > y->key)
		swap_skewheap_node(x, y);

	// ��x���Һ�����y�ϲ����ϲ���ֱ�ӽ���x�����Һ���
	// ������Ҫ�������һ���������ǵ�npl
	SkewNode* tmp = merge_skewheap(x->right, y);
	x->right = x->left;
	x->left = tmp;

	return x;
}

// ����ڵ�,keyΪ�ڵ�ļ�ֵ�����ظ��ڵ�
SkewNode* insert_skewheap(SkewHeap heap, Type key)
{
	SkewNode *node = (SkewNode *)malloc(sizeof(SkewNode));
	if (!node)
		return heap;

	node->key = key;
	node->left = node->right = NULL;

	return merge_skewheap(heap, node);
}

// ɾ�����ڵ㣬�������µĸ��ڵ�
SkewNode* delete_skewheap(SkewHeap heap)
{
	SkewNode *l = heap->left;
	SkewNode *r = heap->right;

	free(heap);

	// �������������ϲ��������
	return merge_skewheap(l, r);
}

// ����б��
void destroy_skewheap(SkewHeap heap)
{
	if (heap)
	{
		if (heap->left)
			destroy_skewheap(heap->left);
		if (heap->right)
			destroy_skewheap(heap->right);

		free(heap);
	}
}

// ��ӡб�ѣ�heap��ʾб�ѵĽڵ㣬key��ʾ�ڵ�ļ�ֵ
// direction 0��ʾ�ýڵ��Ǹ��ڵ㣬-1��ʾ�ýڵ������ĸ��ڵ������
// 1��ʾ�ýڵ������ĸ��ڵ���Һ���
static void skewheap_print(SkewHeap heap, Type key, int direction)
{
	if (heap)
	{
		if (0 == direction)
			printf("%2d is root\n", heap->key);
		else
			printf("%2d is %2d's %6s child\n", heap->key, key,
				(direction == 1 ? "right" : "left"));

		skewheap_print(heap->left, heap->key, -1);
		skewheap_print(heap->right, heap->key, 1);
	}
}

void print_skewheap(SkewHeap heap) { skewheap_print(heap, heap->key, 0); }