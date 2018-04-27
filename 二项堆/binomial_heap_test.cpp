
#include <stdio.h>
#include "binomial_heap.h"

#define DEBUG 1

#if DEBUG
#define log(x, ...) printf(x, __VA_ARGS__)
#else
#define log(x, ...)
#endif

#define LENGTH(a) ((sizeof(a)) / (sizeof(a[0])))

// 共7个 = 1 + 2 + 4
int a[] = { 12, 7, 25, 15, 28, 33, 41 };
// 共13个 = 1 + 4 + 8
int b[] = { 18, 35, 20, 42, 9, 31, 23, 6, 48, 11, 24, 52, 13 };

// 测试二项堆的插入操作
void test_insert()
{
	int i;
	int alen = LENGTH(a);
	BinomialHeap ha = NULL;

	printf("== 二项堆(ha)中依次添加: ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = binomial_insert(ha, a[i]);
	}
	printf("\n");

	// print ha
	printf("== 二项堆(ha)的详细信息: \n");
	binomial_print(ha);
}

// 测试二项堆的合并操作
void test_union()
{
	int i;
	int alen = LENGTH(a);
	int blen = LENGTH(b);
	BinomialHeap ha = NULL, hb = NULL;

	// 二项堆ha
	printf("== 二项堆(ha)中依次添加: ");
	for (i = 0; i < alen; ++i)
	{
		printf("%d ", a[i]);
		ha = binomial_insert(ha, a[i]);
	}
	printf("\n");

	printf("== 二项堆(ha)的详细信息: \n");
	binomial_print(ha);

	// 二项堆hb
	printf("== 二项堆(hb)中依次添加: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb,b[i]);
	}
	printf("\n");

	printf("== 二项堆(hb)的详细信息: \n");
	binomial_print(hb);

	// 将二项堆hb合并到二项堆ha中
	ha = binomial_union(ha, hb);
	printf("== 合并ha和hb后的详细信息: \n");
	binomial_print(ha);
}

// 验证二项堆的删除操作
void test_delete()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// 二项堆hb
	printf("== 二项堆(hb)中依次添加: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb,b[i]);
	}
	printf("\n");

	printf("== 二项堆(hb)的详细信息: \n");
	binomial_print(hb);

	// 删除节点
	i = 20;
	hb = binomial_delete(hb, i);
	printf("== 删除节点%d后的详细信息: \n", i);
	binomial_print(hb);
}

// 验证二项堆的更新(减少)操作
void test_decrease()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// 二项堆hb
	printf("== 二项堆(hb)中依次添加: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb,b[i]);
	}
	printf("\n");

	printf("== 二项堆(hb)的详细信息: \n");
	binomial_print(hb);

	// 将节点20更新为2
	binomial_update(hb, 20, 2);
	printf("== 更新节点20->2后的详细信息: \n");
	binomial_print(hb);
}

// 测试二项堆的更新(增加)操作
void test_increase()
{
	int i;
	int blen = LENGTH(b);
	BinomialHeap hb = NULL;

	// 二项堆hb
	printf("== 二项堆(hb)中依次添加: ");
	for (i = 0; i < blen; ++i)
	{
		printf("%d ", b[i]);
		hb = binomial_insert(hb,b[i]);
	}
	printf("\n");

	printf("== 二项堆(hb)的详细信息: \n");
	binomial_print(hb);

	// 将节点6更新为60
	binomial_update(hb, 6, 60);
	printf("== 更新节点6->60后的详细信息: \n");
	binomial_print(hb);
}

void main()
{
	// test_insert();
	// test_union();
	// test_delete();
	// test_decrease();
	test_increase();

	getchar();
}

