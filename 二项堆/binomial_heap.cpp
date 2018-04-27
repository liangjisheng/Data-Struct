
#include <stdio.h>
#include <stdlib.h>
#include "binomial_heap.h"

#define swap(a, b) (a^=b, b^=a, a^=b)

// 查找
BinomialNode* binomial_search(BinomialHeap heap, Type key)
{
	BinomialNode *child;
	BinomialNode *parent = heap;

	while (parent)
	{
		if (parent->key == key)
			return parent;
		else
		{
			if ((child = binomial_search(parent->child, key)))
				return child;
			parent = parent->next;
		}
	}

	return NULL;
}

/*
 * 获取二项堆中的最小根节点(*y)
 * heap:二项堆
 * prev_y out最小根节点y的前一个根节点
 * y out 最小根节点
*/
static void _binomial_minimum(BinomialHeap heap, BinomialNode **prev_y, BinomialNode **y)
{
	BinomialNode *x, *prev_x;	// x为遍历的当前节点
	
	if (!heap)
		return ;

	prev_x = heap;
	x = heap->next;
	*prev_y = NULL;
	*y = heap;

	while (x)
	{
		if (x->key < (*y)->key)
		{
			*y = x;
			*prev_y = prev_x;
		}
		prev_x = x;
		x = x->next;
	}
}

BinomialNode* binomial_minimum(BinomialHeap heap)
{
	BinomialNode *prev_y, *y;
	_binomial_minimum(heap, &prev_y, &y);

	return y;
}


// 合并两个二项堆，将child合并到heap
static void binomial_link(BinomialHeap child, BinomialHeap heap)
{
	child->parent = heap;
	child->next = heap->child;
	heap->child = child;
	heap->degree++;
}

// 将h1，h2中的根表合并成一个按度数递增的链表，返回合并后的根节点
static BinomialNode* binomial_merge(BinomialHeap h1, BinomialHeap h2)
{
	BinomialNode *head = NULL;
	BinomialNode **pos = &head;

	while (h1 && h2)
	{
		if (h1->degree < h2->degree)
		{
			*pos = h1;
			h1 = h1->next;
		}
		else
		{
			*pos = h2;
			h2 = h2->next;
		}
		pos = &(*pos)->next;
	}

	if (h1)
		*pos = h1;
	else
		*pos = h2;

	return head;
}

/*
 * 合并二项堆: 将h1， h2合并成一个堆，并返回合并后的堆
 * 合并是二项堆的重点，二项堆的添加操作也是基于合并操作实现的
 * 包含以下两步:
 * 1.将两个二项堆的根链表合并合并成一个链表。合并后的新链表按照节点的度数单调递增排列
 * 2.将新链表中根节点度数相同的二项树连接起来，直到所有根节点度数都不相同
 * 合并函数binomial_union(h1, h2)的作用是将h1和h2合并，并返回合并后的二项堆。
 * 在binomial_union(h1, h2)中，涉及到了两个函数binomial_merge(h1, h2)和binomial_link(child, heap)。
 * binomial_merge(h1, h2)就是我们前面所说的"两个二项堆的根链表合并成一个链表，
 * 合并后的新链表按照'节点的度数'单调递增排序"。
 * binomial_link(child, heap)则是为了合并操作的辅助函数，它的作用是将"二项堆child的根节点
 * "设为"二项堆heap的左孩子"，从而将child整合到heap中去。

 * 在binomial_union(h1, h2)中对h1和h2进行合并时；首先通过 binomial_merge(h1, h2) 将h1和h2的
 * 根链表合并成一个"按节点的度数单调递增"的链表；然后进入while循环，对合并得到的新链表进行遍历，
 * 将新链表中"根节点度数相同的二项树"连接起来，直到所有根节点度数都不相同为止。在将新联表中
 * "根节点度数相同的二项树"连接起来时，可以将被连接的情况概括为4种。
 * x是根链表的当前节点，next_x是x的下一个(兄弟)节点。
 * Case 1: x->degree != next_x->degree
 * 即，"当前节点的度数"与"下一个节点的度数"相等时。此时，不需要执行任何操作，
 * 继续查看后面的节点。
 * Case 2: x->degree == next_x->degree == next_x->next->degree
 * 即，"当前节点的度数"、"下一个节点的度数"和"下下一个节点的度数"都相等时。
 * 此时，暂时不执行任何操作，还是继续查看后面的节点。实际上，这里是将"下一个节点"
 * 和"下下一个节点"等到后面再进行整合连接。
 * Case 3: x->degree == next_x->degree != next_x->next->degree
 * && x->key <= next_x->key
 * 即，"当前节点的度数"与"下一个节点的度数"相等，并且"当前节点的键值"<="下一个节点的度数"
 * 此时，将"下一个节点(对应的二项树)"作为"当前节点(对应的二项树)的左孩子"。
 * Case 4: x->degree == next_x->degree != next_x->next->degree
 * && x->key > next_x->key
 * 即，"当前节点的度数"与"下一个节点的度数"相等，并且"当前节点的键值">"下一个节点的度数"
 * 此时，将"当前节点(对应的二项树)"作为"下一个节点(对应的二项树)的左孩子"
*/
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2)
{
	BinomialNode *heap;
	BinomialNode *prev_x, *x, *next_x;

	// 将h1，h2中的根表合并成一个按度数递增的链表heap
	heap = binomial_merge(h1, h2);
	if (!heap)
		return NULL;

	prev_x = NULL;
	x = heap;
	next_x = x->next;

	while (next_x)
	{
		if ((x->degree != next_x->degree)
			|| (next_x->next && (next_x->degree == next_x->next->degree)))
		{
			// case1: x->degree != next_x->degree
			// case2: next_x->next && (next_x->degree == next_x->next->degree)
			prev_x = x;
			x = next_x;
		}
		else if (x->key <= next_x->key)
		{
			// case 3: x->degree == next_x->degree != next_x->next->degree
			//			&& x->key <= next_x->key
			x->next = next_x->next;
			binomial_link(next_x, x);
		}
		else
		{
			// case4: x->degree == next_x->degree != next_x->next->degree
			//		&& x->key > next_x->key
			if (prev_x == NULL)
				heap = next_x;
			else
				prev_x->next = next_x;

			binomial_link(x, next_x);
			x = next_x;
		}

		next_x = x->next;
	}

	return heap;
}


// 新建二项堆节点
static BinomialNode* make_binomial_node(Type key)
{
	BinomialNode *node = (BinomialNode *)malloc(sizeof(BinomialNode));
	if (!node)
	{
		printf("malloc BinomialNode failed\n");
		return NULL;
	}

	node->key = key;
	node->degree = 0;
	node->parent = NULL;
	node->child = NULL;
	node->next = NULL;

	return node;
}

/* 新建key对应的节点，并将其插入到二项堆中
 * heap: 原始二项堆
 * key: 键值
 * 返回值: 插入key之后的二项树
*/
BinomialNode* binomial_insert(BinomialHeap heap, Type key)
{
	if (binomial_search(heap, key) != NULL)
	{
		printf("insert failed: the key(%d) is existed already!\n", key);
		return heap;
	}

	BinomialNode *node = make_binomial_node(key);
	if (!node)
		return heap;

	return binomial_union(heap, node);
}


// 反转二项堆
static BinomialNode* binomial_reverse(BinomialNode* heap)
{
	BinomialNode *next;
	BinomialNode * tail = NULL;

	if (!heap)
		return heap;

	heap->parent = NULL;
	while (heap->next)
	{
		next = heap->next;
		heap->next = tail;
		tail = heap;
		heap = next;
		heap->parent = NULL;
	}
	heap->next = tail;

	return heap;
}

// 移除最小节点，并返回移除节点后的二项堆
BinomialNode* binomial_extract_minimum(BinomialHeap heap)
{
	BinomialNode *y, *prev_y;	// y是最小节点
	if (NULL == heap)
		return heap;

	// 找到最小节点根y和它的前一个根节点prev_y
	_binomial_minimum(heap, &prev_y, &y);

	if (prev_y == NULL)		// heap的根节点就是最小根节点
		heap = heap->next;
	else					// heap的根节点不是最小节点
		prev_y->next = y->next;

	// 反转最小节点的左孩子，得到最小堆child
	// 这样，就使得最小节点所在二项树的孩子们都脱离出来成为一颗独立的二项树(不包括最小节点)
	BinomialNode* child = binomial_reverse(y->child);
	// 将删除最小节点的二项堆child和heap进行合并
	heap = binomial_union(heap, child);

	// 删除最小节点
	free(y);

	return heap;
}


/*
* 减少关键字的值，将二项堆heap中的节点node的键值减小为key
* 该节点一定位于一颗二项树中，减小二项树中某个节点的值后要保证该二项树仍然是
* 一个最小堆，因此需要不断的将该节点上调
*/
static void binomial_decrease_key(BinomialHeap heap, BinomialNode *node, Type key)
{
	if ((key >= node->key) || (binomial_search(heap, key) != NULL))
	{
		printf("decrease failed: the new key(%d) is existed already, \
			   or is no samller than current key(%d)\n", key, node->key);
		return ;
	}

	node->key = key;

	BinomialNode *child, *parent;
	child = node;
	parent = node->parent;
	while (parent && child->key < parent->key)
	{
		swap(parent->key, child->key);
		child = parent;
		parent = child->parent;
	}
}

/*
* 增减关键字：将二项堆heap中的节点node的键值增加为key
* 增加操作是将被增加的节点不断下调，保证被增加节点所在的二项树的最小堆性质
*/
static void binomial_increase_key(BinomialHeap heap, BinomialNode* node, Type key)
{
	if ((key <= node->key) || (binomial_search(heap, key) != NULL))
	{
		printf("increase failed: the new key(%d) is existed already,\
			   or is no greater than current key(%d)\n", key, node->key);
		return ;
	}

	node->key = key;

	// 向下调整，使得重新成为二项堆
	BinomialNode *cur, *child, *least;
	cur = node;
	child = cur->child;
	while (child)
	{
		if (cur->key > child->key)
		{
			// 如果当前节点大于他的左孩子，则在他的孩子中(左孩子和左孩子的兄弟节点)中，
			// 找出最小的节点，然后将最小节点的值和当前节点的值进行互换
			least = child;
			while (child->next)
			{
				if (least->key > child->next->key)
					least = child->next;
				child = child->next;
			}

			// 交换最小节点和当前节点的值
			swap(least->key, cur->key);

			// 交换数据后，再对最小节点进行调整，使得它满足最小堆的性质：父节点<=子节点
			cur = least;
			child = cur->child;
		}
		// 比较下一个孩子
		else
			child = child->next;
	}
}

// 更新二项堆heap的节点node的键值为key
static void binomial_update_key(BinomialHeap heap, BinomialNode *node, Type key)
{
	if (!node)
		return ;

	if (key < node->key)
		binomial_decrease_key(heap, node, key);
	else if (key > node->key)
		binomial_increase_key(heap, node, key);
	else
		printf("No need to update!!!\n");
}

// 将二项堆heap的键值oldkey更新为newkey
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey)
{
	BinomialNode *node = binomial_search(heap, oldkey);
	if (node)
		binomial_update_key(heap, node, newkey);
}


/*
 * 删除键值为key的节点，并返回删除节点后的二项树
 * 1.将该节点交换到它所在二项树的根节点位置。方法是，从该节点不断向上(即向树根方向)遍历
 *   不断交换父节点和子节点，知道被删除的键值到达树根位置
 * 2.将该节点所在的二项树从二项堆中删除，将该二项堆记为heap
 * 3.将该节点所在的二项树进行反转。反转的意思就是将根的所有孩子独立出来，并将这些孩子整合
 *   成二项堆，将该二项堆记为child,
 * 4.将child和heap进行合并操作
*/
BinomialNode* binomial_delete(BinomialHeap heap, Type key)
{
	BinomialNode *node;
	BinomialNode *parent, *prev, *pos;

	if (!heap)
		return heap;

	if ((node = binomial_search(heap, key)) == NULL)
		return heap;

	// 将被删除的节点的数据上移到它所在二项树的根节点
	parent = node->parent;
	while (parent)
	{
		swap(node->key, parent->key);
		node = parent;
		parent = node->parent;
	}

	// 找到node的前一个根节点(prev)(此时node已经上移到根节点了)
	prev = NULL;
	pos = heap;
	while (pos != node)
	{
		prev = pos;
		pos = pos->next;
	}

	// 移除node节点
	if (prev)
		prev->next = node->next;
	else
		// prev为NULL说明node节点为第一个根节点
		heap = node->next;

	heap = binomial_union(heap, binomial_reverse(node->child));

	free(node);

	return heap;
}

/*
 * 打印二项堆
 * node：当前节点
 * prev：当前节点的前一个节点
 * direction：1表示当前节点是一个左孩子，2表示当前节点是一个兄弟节点
*/
static void _binomial_print(BinomialNode *node, BinomialNode *prev, int direction)
{
	while (node)
	{
		if (1 == direction)
			printf("\t%2d(%d) is %2d's child\n", node->key, node->degree, prev->key);
		else
			printf("\t%2d(%d) is %2d's next\n", node->key, node->degree, prev->key);

		if (node->child)
			_binomial_print(node->child, node, 1);

		// 兄弟节点
		prev = node;
		node = node->next;
		direction = 2;
	}
}

void binomial_print(BinomialHeap heap)
{
	if (!heap)
		return ;

	BinomialNode *p = heap;
	printf("== 二项堆( ");
	while (p)
	{
		printf("B%d ", p->degree);
		p = p->next;
	}
	printf(")详细信息: \n");

	int i = 0;
	while (heap)
	{
		i++;
		printf("%d. 二项树B%d: \n", i, heap->degree);
		printf("\t%2d(%d) is root\n", heap->key, heap->degree);

		_binomial_print(heap->child, heap, 1);
		heap = heap->next;
	}
	printf("\n");
}
