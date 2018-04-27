
/**
 * C����ʵ�������
*/

#include <stdio.h>
#include <stdlib.h>
#include "leftist.h"

void preorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		printf("%d ", heap->key);
		preorder_leftist(heap->left);
		preorder_leftist(heap->right);
	}
}

void inorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		inorder_leftist(heap->left);
		printf("%d ", heap->key);
		inorder_leftist(heap->right);
	}
}

void postorder_leftist(LeftistHeap heap)
{
	if (heap)
	{
		postorder_leftist(heap->left);
		postorder_leftist(heap->right);
		printf("%d ", heap->key);
	}
}

// ���������ڵ������
static void swap_leftist_node(LeftistNode* x, LeftistNode* y)
{
	LeftistNode tmp = *x;
	*x = *y;
	*y = tmp;
}

// ��ȡ��Сֵ���ɹ�����0��ʧ�ܷ���-1
int leftist_minimum(LeftistHeap heap, Type *pval)
{
	if (!heap)
		return -1;

	*pval = heap->key;
	return 0;
}

// �ϲ������x�������y�����غϲ��õ����µ����ĸ��ڵ�
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y)
{
	if (NULL == x)
		return y;
	if (NULL == y)
		return x;

	// �ϲ�x��yʱ����x��Ϊ�ϲ������ĸ��������Ǳ�֤x��key < y��key
	if (x->key > y->key)
		swap_leftist_node(x, y);

	// ��x���Һ�����y�ϲ����ϲ������ĸ���x���Һ���
	x->right = merge_leftist(x->right, y);

	// ���x������Ϊ�ջ���x�����ӵ�npl<�Һ��ӵ�npl,�򽻻�x��y
	if (x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode* tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}

	// ���úϲ��������x��npl
	if (x->right == NULL || x->left == NULL)
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

// ����ڵ㣬heapΪ����ѵĸ��ڵ㣬keyΪ����ڵ�ļ�ֵ�������µĸ��ڵ�
LeftistNode* insert_leftist(LeftistHeap heap, Type key)
{
	LeftistNode* node = (LeftistNode *)malloc(sizeof(LeftistNode));
	if (!node)
		return heap;

	node->key = key;
	node->npl = 0;
	node->left = node->right = NULL;

	return merge_leftist(heap, node);
}

// ɾ�����ڵ㣬�����µĸ��ڵ�
LeftistNode* delete_leftist(LeftistHeap heap)
{
	if (!heap)
		return NULL;

	LeftistNode *l = heap->left;
	LeftistNode *r = heap->right;

	free(heap);

	// �������������ϲ��������
	return merge_leftist(l, r);
}

// ���������
void destroy_leftist(LeftistHeap heap)
{
	if (NULL == heap)
		return ;

	if (heap->left)
		destroy_leftist(heap->left);
	if (heap->right)
		destroy_leftist(heap->right);

	free(heap);
}

/* ��ӡ�����
 * heap: ����ѵĽڵ�
 * key: �ڵ�ļ�ֵ
 * direction: 0,��ʾ�ýڵ��Ǹ��ڵ�
			  -1����ʾ�ýڵ��������ڵ������
			  1����ʾ�ýڵ��������ڵ���Һ���
*/

static void leftist_print(LeftistHeap heap, Type key, int direction)
{
	if (heap)
	{
		if (0 == direction)		// heap�Ǹ��ڵ�
			printf("%2d(%d) is root\n", heap->key, heap->npl);
		else					// heap�Ƿ�֧�ڵ�
			printf("%2d(%d) is %2d's %6s child\n", heap->key, heap->npl, key,
				direction == 1 ? "right" : "left");

		leftist_print(heap->left, heap->key, -1);
		leftist_print(heap->right, heap->key, 1);
	}
}

void print_leftist(LeftistHeap heap)
{
	if (heap)
		leftist_print(heap, heap->key, 0);
}