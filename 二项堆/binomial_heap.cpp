
#include <stdio.h>
#include <stdlib.h>
#include "binomial_heap.h"

#define swap(a, b) (a^=b, b^=a, a^=b)

// ����
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
 * ��ȡ������е���С���ڵ�(*y)
 * heap:�����
 * prev_y out��С���ڵ�y��ǰһ�����ڵ�
 * y out ��С���ڵ�
*/
static void _binomial_minimum(BinomialHeap heap, BinomialNode **prev_y, BinomialNode **y)
{
	BinomialNode *x, *prev_x;	// xΪ�����ĵ�ǰ�ڵ�
	
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


// �ϲ���������ѣ���child�ϲ���heap
static void binomial_link(BinomialHeap child, BinomialHeap heap)
{
	child->parent = heap;
	child->next = heap->child;
	heap->child = child;
	heap->degree++;
}

// ��h1��h2�еĸ���ϲ���һ���������������������غϲ���ĸ��ڵ�
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
 * �ϲ������: ��h1�� h2�ϲ���һ���ѣ������غϲ���Ķ�
 * �ϲ��Ƕ���ѵ��ص㣬����ѵ���Ӳ���Ҳ�ǻ��ںϲ�����ʵ�ֵ�
 * ������������:
 * 1.����������ѵĸ�����ϲ��ϲ���һ�������ϲ�����������սڵ�Ķ���������������
 * 2.���������и��ڵ������ͬ�Ķ���������������ֱ�����и��ڵ����������ͬ
 * �ϲ�����binomial_union(h1, h2)�������ǽ�h1��h2�ϲ��������غϲ���Ķ���ѡ�
 * ��binomial_union(h1, h2)�У��漰������������binomial_merge(h1, h2)��binomial_link(child, heap)��
 * binomial_merge(h1, h2)��������ǰ����˵��"��������ѵĸ�����ϲ���һ������
 * �ϲ������������'�ڵ�Ķ���'������������"��
 * binomial_link(child, heap)����Ϊ�˺ϲ������ĸ������������������ǽ�"�����child�ĸ��ڵ�
 * "��Ϊ"�����heap������"���Ӷ���child���ϵ�heap��ȥ��

 * ��binomial_union(h1, h2)�ж�h1��h2���кϲ�ʱ������ͨ�� binomial_merge(h1, h2) ��h1��h2��
 * ������ϲ���һ��"���ڵ�Ķ�����������"������Ȼ�����whileѭ�����Ժϲ��õ�����������б�����
 * ����������"���ڵ������ͬ�Ķ�����"����������ֱ�����и��ڵ����������ͬΪֹ���ڽ���������
 * "���ڵ������ͬ�Ķ�����"��������ʱ�����Խ������ӵ��������Ϊ4�֡�
 * x�Ǹ�����ĵ�ǰ�ڵ㣬next_x��x����һ��(�ֵ�)�ڵ㡣
 * Case 1: x->degree != next_x->degree
 * ����"��ǰ�ڵ�Ķ���"��"��һ���ڵ�Ķ���"���ʱ����ʱ������Ҫִ���κβ�����
 * �����鿴����Ľڵ㡣
 * Case 2: x->degree == next_x->degree == next_x->next->degree
 * ����"��ǰ�ڵ�Ķ���"��"��һ���ڵ�Ķ���"��"����һ���ڵ�Ķ���"�����ʱ��
 * ��ʱ����ʱ��ִ���κβ��������Ǽ����鿴����Ľڵ㡣ʵ���ϣ������ǽ�"��һ���ڵ�"
 * ��"����һ���ڵ�"�ȵ������ٽ����������ӡ�
 * Case 3: x->degree == next_x->degree != next_x->next->degree
 * && x->key <= next_x->key
 * ����"��ǰ�ڵ�Ķ���"��"��һ���ڵ�Ķ���"��ȣ�����"��ǰ�ڵ�ļ�ֵ"<="��һ���ڵ�Ķ���"
 * ��ʱ����"��һ���ڵ�(��Ӧ�Ķ�����)"��Ϊ"��ǰ�ڵ�(��Ӧ�Ķ�����)������"��
 * Case 4: x->degree == next_x->degree != next_x->next->degree
 * && x->key > next_x->key
 * ����"��ǰ�ڵ�Ķ���"��"��һ���ڵ�Ķ���"��ȣ�����"��ǰ�ڵ�ļ�ֵ">"��һ���ڵ�Ķ���"
 * ��ʱ����"��ǰ�ڵ�(��Ӧ�Ķ�����)"��Ϊ"��һ���ڵ�(��Ӧ�Ķ�����)������"
*/
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2)
{
	BinomialNode *heap;
	BinomialNode *prev_x, *x, *next_x;

	// ��h1��h2�еĸ���ϲ���һ������������������heap
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


// �½�����ѽڵ�
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

/* �½�key��Ӧ�Ľڵ㣬��������뵽�������
 * heap: ԭʼ�����
 * key: ��ֵ
 * ����ֵ: ����key֮��Ķ�����
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


// ��ת�����
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

// �Ƴ���С�ڵ㣬�������Ƴ��ڵ��Ķ����
BinomialNode* binomial_extract_minimum(BinomialHeap heap)
{
	BinomialNode *y, *prev_y;	// y����С�ڵ�
	if (NULL == heap)
		return heap;

	// �ҵ���С�ڵ��y������ǰһ�����ڵ�prev_y
	_binomial_minimum(heap, &prev_y, &y);

	if (prev_y == NULL)		// heap�ĸ��ڵ������С���ڵ�
		heap = heap->next;
	else					// heap�ĸ��ڵ㲻����С�ڵ�
		prev_y->next = y->next;

	// ��ת��С�ڵ�����ӣ��õ���С��child
	// ��������ʹ����С�ڵ����ڶ������ĺ����Ƕ����������Ϊһ�Ŷ����Ķ�����(��������С�ڵ�)
	BinomialNode* child = binomial_reverse(y->child);
	// ��ɾ����С�ڵ�Ķ����child��heap���кϲ�
	heap = binomial_union(heap, child);

	// ɾ����С�ڵ�
	free(y);

	return heap;
}


/*
* ���ٹؼ��ֵ�ֵ���������heap�еĽڵ�node�ļ�ֵ��СΪkey
* �ýڵ�һ��λ��һ�Ŷ������У���С��������ĳ���ڵ��ֵ��Ҫ��֤�ö�������Ȼ��
* һ����С�ѣ������Ҫ���ϵĽ��ýڵ��ϵ�
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
* �����ؼ��֣��������heap�еĽڵ�node�ļ�ֵ����Ϊkey
* ���Ӳ����ǽ������ӵĽڵ㲻���µ�����֤�����ӽڵ����ڵĶ���������С������
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

	// ���µ�����ʹ�����³�Ϊ�����
	BinomialNode *cur, *child, *least;
	cur = node;
	child = cur->child;
	while (child)
	{
		if (cur->key > child->key)
		{
			// �����ǰ�ڵ�����������ӣ��������ĺ�����(���Ӻ����ӵ��ֵܽڵ�)�У�
			// �ҳ���С�Ľڵ㣬Ȼ����С�ڵ��ֵ�͵�ǰ�ڵ��ֵ���л���
			least = child;
			while (child->next)
			{
				if (least->key > child->next->key)
					least = child->next;
				child = child->next;
			}

			// ������С�ڵ�͵�ǰ�ڵ��ֵ
			swap(least->key, cur->key);

			// �������ݺ��ٶ���С�ڵ���е�����ʹ����������С�ѵ����ʣ����ڵ�<=�ӽڵ�
			cur = least;
			child = cur->child;
		}
		// �Ƚ���һ������
		else
			child = child->next;
	}
}

// ���¶����heap�Ľڵ�node�ļ�ֵΪkey
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

// �������heap�ļ�ֵoldkey����Ϊnewkey
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey)
{
	BinomialNode *node = binomial_search(heap, oldkey);
	if (node)
		binomial_update_key(heap, node, newkey);
}


/*
 * ɾ����ֵΪkey�Ľڵ㣬������ɾ���ڵ��Ķ�����
 * 1.���ýڵ㽻���������ڶ������ĸ��ڵ�λ�á������ǣ��Ӹýڵ㲻������(������������)����
 *   ���Ͻ������ڵ���ӽڵ㣬֪����ɾ���ļ�ֵ��������λ��
 * 2.���ýڵ����ڵĶ������Ӷ������ɾ�������ö���Ѽ�Ϊheap
 * 3.���ýڵ����ڵĶ��������з�ת����ת����˼���ǽ��������к��Ӷ���������������Щ��������
 *   �ɶ���ѣ����ö���Ѽ�Ϊchild,
 * 4.��child��heap���кϲ�����
*/
BinomialNode* binomial_delete(BinomialHeap heap, Type key)
{
	BinomialNode *node;
	BinomialNode *parent, *prev, *pos;

	if (!heap)
		return heap;

	if ((node = binomial_search(heap, key)) == NULL)
		return heap;

	// ����ɾ���Ľڵ���������Ƶ������ڶ������ĸ��ڵ�
	parent = node->parent;
	while (parent)
	{
		swap(node->key, parent->key);
		node = parent;
		parent = node->parent;
	}

	// �ҵ�node��ǰһ�����ڵ�(prev)(��ʱnode�Ѿ����Ƶ����ڵ���)
	prev = NULL;
	pos = heap;
	while (pos != node)
	{
		prev = pos;
		pos = pos->next;
	}

	// �Ƴ�node�ڵ�
	if (prev)
		prev->next = node->next;
	else
		// prevΪNULL˵��node�ڵ�Ϊ��һ�����ڵ�
		heap = node->next;

	heap = binomial_union(heap, binomial_reverse(node->child));

	free(node);

	return heap;
}

/*
 * ��ӡ�����
 * node����ǰ�ڵ�
 * prev����ǰ�ڵ��ǰһ���ڵ�
 * direction��1��ʾ��ǰ�ڵ���һ�����ӣ�2��ʾ��ǰ�ڵ���һ���ֵܽڵ�
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

		// �ֵܽڵ�
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
	printf("== �����( ");
	while (p)
	{
		printf("B%d ", p->degree);
		p = p->next;
	}
	printf(")��ϸ��Ϣ: \n");

	int i = 0;
	while (heap)
	{
		i++;
		printf("%d. ������B%d: \n", i, heap->degree);
		printf("\t%2d(%d) is root\n", heap->key, heap->degree);

		_binomial_print(heap->child, heap, 1);
		heap = heap->next;
	}
	printf("\n");
}
