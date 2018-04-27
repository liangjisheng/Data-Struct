
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

// 交换两个节点的内容
static void swap_skewheap_node(SkewNode *x, SkewNode *y)
{
	SkewNode tmp = *x;
	*x = *y;
	*y = tmp;
}

// 最小值
int skewheap_minimum(SkewHeap heap, Type* pval)
{
	if (heap)
		return -1;

	*pval = heap->key;

	return 0;
}

// 合并斜堆x和斜堆y，返回合并得到的根节点
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y)
{
	if (NULL == x)
		return y;
	if (NULL == y)
		return x;

	//  合并x和y时，将x作为合并后的树的根，这里是保证x的key小于y的key
	if (x->key > y->key)
		swap_skewheap_node(x, y);

	// 将x的右孩子与y合并，合并后直接交换x的左右孩子
	// 而不需要像左倾堆一样考虑他们的npl
	SkewNode* tmp = merge_skewheap(x->right, y);
	x->right = x->left;
	x->left = tmp;

	return x;
}

// 插入节点,key为节点的键值，返回根节点
SkewNode* insert_skewheap(SkewHeap heap, Type key)
{
	SkewNode *node = (SkewNode *)malloc(sizeof(SkewNode));
	if (!node)
		return heap;

	node->key = key;
	node->left = node->right = NULL;

	return merge_skewheap(heap, node);
}

// 删除根节点，并返回新的根节点
SkewNode* delete_skewheap(SkewHeap heap)
{
	SkewNode *l = heap->left;
	SkewNode *r = heap->right;

	free(heap);

	// 返回左右子树合并后的新树
	return merge_skewheap(l, r);
}

// 销毁斜堆
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

// 打印斜堆，heap表示斜堆的节点，key表示节点的键值
// direction 0表示该节点是根节点，-1表示该节点是它的父节点的左孩子
// 1表示该节点是它的父节点的右孩子
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