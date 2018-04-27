
/************************************************************************
 * http://www.cnblogs.com/skywang12345/p/3610187.html
 * 堆(heap)的定义: 这里所说的堆是数据结构中的堆,而不是内存模型中的堆.
 * 堆通常可以被看做一颗树,它满足下列性质:
 * 1.堆中任意节点的值总是不大于(不小于)其子节点的值
 * 2.堆总是一颗完全树
 * 将任意节点不大于其子节点的堆叫做最小堆或小跟堆,而将任意节点不小于其
 * 子节点的堆叫做最大堆或大根堆.常见的堆有二叉堆、左倾堆、斜堆、二项堆
 * 斐波那契堆等等

 * 二叉堆是完全二叉树或者是近似完全二叉树,
 * 二叉堆一般都是通过数组来实现.数组实现的二叉堆,父节点和子节点的位置存在
 * 一定的关系,有时候将二叉堆的第一个元素放在数组索引0的位置,有时候放在1的
 * 位置
 * 假设第一个元素在数组中的索引为0的话,则父节点和子节点的位置关系如下:
 * 索引为i的左孩子的索引是(2 * i + 1)
 * 索引为i的右孩子的索引是(2 * i + 2)
 * 索引为i的父节点的索引是floor((i - 1) / 2)
 *
 * 假设第一个元素在数组中的索引为1的话,则父节点和子节点的位置关系如下:
 * 索引为i的左孩子的索引是(2 * i)
 * 索引为i的右孩子的索引是(2 * i + 1)
 * 索引为i的父节点的索引是floor(i / 2)

 * 注意：本文二叉堆的实现是采用"二叉堆第一个元素在数组索引为0"的方式
 * 文件名: max_heap.c
 * 最大堆的实现

 * 当向最大堆中添加数据时：先将数据加入到最大堆的最后，然后尽可能把这个
 * 元素往上挪，直到挪不动为止
 * 当从最大堆中删除数据时:先删除该数据,然后用最大堆中最后一个的元素插入
 * 这个空位;接着把这个空位尽量往上挪,直到剩余的数据变成一个最大堆
 *
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

static int m_heap[30];			// 存储堆的数组
static int m_capacity = 30;		// 总的容量
static int m_size = 0;			// 实际大小(初始化为0)

// 返回data在二叉堆中的索引,存在返回索引,不存在返回-1
int get_index(int data)
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
		if(data == m_heap[i])
			return i;

	return -1;
}

/************************************************************************
 * 最大堆向下调整算法
 * start: 被下调节点的起始位置(一般为0,表示从第一个开始)
 * end: 截止范围,一般为数组中最后一个元素的索引
************************************************************************/
static void maxheap_filterdown(int start, int end)
{
	int c = start;			// 当前节点的位置
	int l = 2 * c + 1;		// 左孩子的位置
	int tmp = m_heap[c];	// 当前节点的大小

	while(l <= end)
	{
		// l是左孩子,l + 1是右孩子
		// 选择左右孩子中较大的值
		if(l < end && m_heap[l] < m_heap[l + 1])
			l++;

		if(tmp >= m_heap[l])
			break;			// 调整结束
		else
		{
			m_heap[c] = m_heap[l];
			c = l;
			l = 2 * l + 1;
		}
	}

	m_heap[c] = tmp;
}

// 删除最大堆中的data,0:成功,1:失败
int maxheap_remove(int data)
{
	int index;
	if(0 == m_size)				// 堆以空,返回-1
		return -1;

	index = get_index(data);	// 获取data在数组中的索引
	if(-1 == index)
		return -1;

	m_heap[index] = m_heap[--m_size];		// 用最后的元素填补删除的元素
	maxheap_filterdown(index, m_size - 1);	// 从index位置开始自上向下调整为最大堆

	return 0;
}

/************************************************************************
 * 最大堆的向上调整算法(从start开始向上直到0)
 * start: 被上调节点的起始位置(一般为数组中最后一个元素的索引)
************************************************************************/
static void maxheap_filterup(int start)
{
	int c = start;				// 当前节点的位置
	int p = (c - 1) / 2;		// 父节点的位置
	int tmp = m_heap[c];		// 当前节点的大小

	while(c > 0)
	{
		if(m_heap[p] >= tmp)
			break;
		else
		{
			m_heap[c] = m_heap[p];
			c = p;
			p = (p - 1) / 2;
		}
	}

	m_heap[c] = tmp;
}

// 将data插入到二叉堆中,0:成功,-1:失败
int maxheap_insert(int data)
{
	if(m_size == m_capacity)			// 如果堆已满,返回-1
		return -1;

	m_heap[m_size] = data;				// 将数据插在末尾
	maxheap_filterup(m_size);			// 向上调整堆
	m_size++;

	return 0;
}

// 打印二叉堆
void maxheap_print()
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
		printf("%d ", m_heap[i]);
}


void main()
{
	int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	int i, len = LENGTH(a);

	printf("== 依次添加: ");
	for (i = 0; i < len; ++i)
	{
		printf("%d ", a[i]);
		maxheap_insert(a[i]);
	}
	printf("\n");

	printf("== 最大堆: ");
	maxheap_print();
	printf("\n");

	i = 85;
	maxheap_insert(i);
	printf("== 添加元素: %d", i);
	printf("== 最大堆: ");
	maxheap_print();
	printf("\n");

	i = 90;
	maxheap_remove(i);
	printf("== 删除元素: %d", i);
	printf("== 最大堆: ");
	maxheap_print();
	printf("\n");

	getchar();
}

