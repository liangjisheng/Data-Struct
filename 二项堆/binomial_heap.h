
// http://www.cnblogs.com/skywang12345/p/3655900.html
// �������֮ǰ�Ķ���ѡ�����ѡ�б��һ����Ҳ������ʵ�����ȶ��еġ�
// ������Ƕ������ļ���
// ��������һ�ֵݹ鶨�����,��������:
// 1.������b0ֻ��һ���ڵ㣬
// 2.������bk�����Ŷ�����b(k-1)��ɣ�����һ��������һ��������������

// ���������������ʣ�
// [����һ] Bk����2k���ڵ㡣
// [���ʶ�] Bk�ĸ߶�Ϊk��
// [������] Bk�����i��ǡ����C(k,i)���ڵ㣬����i=0,1,2,...,k��
// [������] ���Ķ���Ϊk���������κ������ڵ�Ķ�����
// ע�⣺���ĸ߶Ⱥ��������ͬ�ġ��������ĸ߶ȵĸ�����㷨���ۡ���ֻ��һ���ڵ�����ĸ߶���0��
// ��"ά���ٿ�"��ֻ��һ���ڵ�����ĸ߶���1������ʹ���ˡ��㷨�����С�"���ĸ߶Ⱥ����"�ĸ���

// �����ͨ��������ʵ�����ȶ��У�������ָ�����������ʵĶ������ļ��ϣ�
// (01) ÿ�ö�������������С�����ʡ��������ڵ�Ĺؼ��� <= ���ĺ��ӵĹؼ��֡�
// (02) ���������û����ϵĶ�����������ͬ�Ķ���(��������Ϊ0)�����仰˵�����ж���k�Ķ�������0����1����

// �ϲ������Ƕ���ѵ��ص㣬����ѵ���Ӳ���Ҳ�ǻ��ںϲ�������ʵ�ֵ�,ͨ�����������ϲ����������
// 1.����������ѵĸ�����ϲ���һ�������ϲ�����������սڵ�Ķ���������������
// 2.���������еĸ��ڵ������ͬ�Ķ���������������ֱ�����и��ڵ����������ͬ

#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_

typedef int Type;

typedef struct _BinomialNode
{
	Type key;						// ��ֵ
	int degree;						// ����
	struct _BinomialNode *child;	// ����
	struct _BinomialNode *parent;	// ���ڵ�
	struct _BinomialNode *next;		// �ֵܽڵ�
}BinomialNode, *BinomialHeap;

// �½�key��Ӧ�Ľڵ㣬��������뵽�������
BinomialNode* binomial_insert(BinomialHeap heap, Type key);

// ɾ����ֵΪkey�Ľڵ㣬����ɾ����Ķ�����
BinomialNode* binomial_delete(BinomialHeap heap, Type key);

// �������heap�ļ�ֵoldkey����Ϊnewkey
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey);

// �ϲ�����ѣ���h1��h2�ϲ���һ���ѣ����غϲ���Ķ�
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2);

// �ڶ�����в��Ҽ�ֵΪkey�Ľڵ�
BinomialNode* binomial_search(BinomialHeap heap, Type key);

// ��ȡ������е���С�ڵ�
BinomialNode* binomial_minimum(BinomialHeap heap);

// ɾ����С�ڵ㣬����ɾ���ڵ��Ķ����
BinomialNode* binomial_extract_minimum(BinomialHeap heap);

// ��ӡ�����
void binomial_print(BinomialHeap heap);

#endif // _BINOMIAL_HEAP_H_
