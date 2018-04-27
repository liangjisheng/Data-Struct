
/**
 * C语言实现左倾堆
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

// 交换两个节点的内容
static void swap_leftist_node(LeftistNode* x, LeftistNode* y)
{
	LeftistNode tmp = *x;
	*x = *y;
	*y = tmp;
}

// 获取最小值，成功返回0，失败返回-1
int leftist_minimum(LeftistHeap heap, Type *pval)
{
	if (!heap)
		return -1;

	*pval = heap->key;
	return 0;
}

// 合并左倾堆x和左倾堆y，返回合并得到的新的树的根节点
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y)
{
	if (NULL == x)
		return y;
	if (NULL == y)
		return x;

	// 合并x和y时，将x作为合并后树的根，这里是保证x的key < y的key
	if (x->key > y->key)
		swap_leftist_node(x, y);

	// 将x的右孩子与y合并，合并后树的根是x的右孩子
	x->right = merge_leftist(x->right, y);

	// 如果x的左孩子为空或者x的左孩子的npl<右孩子的npl,则交换x和y
	if (x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode* tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}

	// 设置合并后的新树x的npl
	if (x->right == NULL || x->left == NULL)
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

// 插入节点，heap为左倾堆的根节点，key为插入节点的键值，返回新的根节点
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

// 删除根节点，返回新的根节点
LeftistNode* delete_leftist(LeftistHeap heap)
{
	if (!heap)
		return NULL;

	LeftistNode *l = heap->left;
	LeftistNode *r = heap->right;

	free(heap);

	// 返回左右子树合并后的新树
	return merge_leftist(l, r);
}

// 销毁左倾堆
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

/* 打印左倾堆
 * heap: 左倾堆的节点
 * key: 节点的键值
 * direction: 0,表示该节点是根节点
			  -1，表示该节点是它父节点的左孩子
			  1，表示该节点事它父节点的右孩子
*/

static void leftist_print(LeftistHeap heap, Type key, int direction)
{
	if (heap)
	{
		if (0 == direction)		// heap是根节点
			printf("%2d(%d) is root\n", heap->key, heap->npl);
		else					// heap是分支节点
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