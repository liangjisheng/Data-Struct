
/************************************************************************
 * �����(��С��)
 * author: ����ʥ
 * date: 20171112
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static int m_heap[30];			// ��С��
static int m_capacity = 30;		// �ܵ�����
static int m_size = 0;			// ʵ������(��ʼ��Ϊ0)

// ��ȡdata�ڶ�����е�����,0:�ɹ�,-1:ʧ��
int get_index(int data)
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
		if(data == m_heap[i])
			return i;

	return -1;
}

/************************************************************************
 * ��С�����µ����㷨
 * start: ���µ��ڵ����ʼλ��(һ��Ϊ0,��ʾ�ӵ�1����ʼ)
 * end: ��ֹ��Χ(һ��Ϊ���������һ��Ԫ�ص�����)
************************************************************************/
static void minheap_filterdown(int start, int end)
{
	int c = start;				// ��ǰ�ڵ��λ��
	int l = 2 * c + 1;			// ���ӵ�λ��
	int tmp = m_heap[c];		// ��ǰ�ڵ�Ĵ�С

	while(l <= end)
	{
		// l������,l + 1���Һ���
		// ���Һ�����ѡ���С��
		if(l < end && m_heap[l] > m_heap[l + 1])
			l++;

		if(tmp <= m_heap[l])
			break;
		else
		{
			m_heap[c] = m_heap[l];
			c = l;
			l = 2 * l + 1;
		}
	}

	m_heap[c] = tmp;
}

// ɾ�����¶��е�data,0:�ɹ�,-1:ʧ��
int minheap_remove(int data)
{
	int index;
	if(0 == m_size)			// ����ѿ�,����-1
		return -1;

	index = get_index(data);
	if(-1 == index)
		return -1;

	m_heap[index] = m_heap[--m_size];		// �����Ԫ���
	minheap_filterdown(index, m_size - 1);	// ��index��λ�ÿ�ʼ�������µ���Ϊ��С��

	return 0;
}

/************************************************************************
 * ��С�ѵ����ϵ����㷨(��start��ʼ����ֱ��0,������)
 * start: ���ϵ��ڵ����ʼλ��(һ��Ϊ�����е����һ��Ԫ��)
************************************************************************/
static void filter_up(int start)
{
	int c = start;				// ��ǰ�ڵ��λ��
	int p = (c - 1) / 2;		// ���ڵ��λ��
	int tmp = m_heap[c];		// ��ǰ�ڵ�Ĵ�С

	while(c > 0)
	{
		if(m_heap[p] <= tmp)
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

// ��data���뵽�������,0:�ɹ�,-1:ʧ��
int minheap_insert(int data)
{
	if(m_size == m_capacity)		// �������,����-1
		return -1;

	m_heap[m_size] = data;			// �����ݲ���ĩβ
	filter_up(m_size);				// ���ϵ�����
	m_size++;

	return 0;
}

// ��ӡ�����
void minheap_print()
{
	int i = 0;
	for (i = 0; i < m_size; ++i)
		printf("%d ", m_heap[i]);
}


void main()
{
	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	int i, len = LENGTH(a);

	printf("== �������: ");
	for (i = 0; i < len; ++i)
	{
		printf("%d ", a[i]);
		minheap_insert(a[i]);
	}

	printf("\n== ��С��: ");
	minheap_print();

	i = 15;
	minheap_insert(i);
	printf("\n== ���Ԫ��: %d", i);
	printf("\n== ��С��: ");
	minheap_print();

	i = 10;
	minheap_remove(i);
	printf("\n== ɾ��Ԫ��: %d", i);
	printf("\n== ��С��: ");
	minheap_print();
	printf("\n");

	getchar();
}

