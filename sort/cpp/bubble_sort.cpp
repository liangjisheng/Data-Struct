
// 冒泡排序
#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#define  SWAP(a, b) (a ^= b, b ^= a, a ^= b)

/**
 * a:待排序的数组
 * n:数组的长度
*/
void bubble_sort1(int a[], int n)
{
	int i, j;
	for (i = n - 1; i > 0; --i)
	{
		// 将a[0...i]中的最大数据放在末尾
		for (j = 0; j < i; ++j)
			if (a[j] > a[j + 1])
				SWAP(a[j], a[j + 1]);
	}
}

// 冒泡排序改进版,添加一个标记，如果一趟遍历中发生了交换，则标记为true，否则为false
// 如果某一趟没有发生交换，说明排序已经完成
void bubble_sort2(int a[], int n)
{
	int i, j;
	int flag;		// 标记

	for (i = n - 1; i > 0; --i)
	{
		flag = 0;

		for (j = 0; j < i; ++j)
		{
			if (a[j] > a[j + 1])
			{
				SWAP(a[j], a[j + 1]);
				flag = 1;		// 如果发生交换，则设标记为1
			}
		}

		if (0 == flag)			// 没有发生交换，说明数列已经有序
			break;
	}
}

void main()
{
	int i;
	int a[] = { 20, 40, 30, 10, 60, 50 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	// bubble_sort1(a, ilen);
	bubble_sort2(a, ilen);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}