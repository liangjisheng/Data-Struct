
// 选择排序(Selection sort)是一种简单直观的排序算法
// 它的基本思想是：首先在未排序的数列中找到最小(or最大)元素，然后将其存放到数列的起始位置
// 接着，再从剩余未排序的元素中继续寻找最小(or最大)元素，然后放到已排序序列的末尾
// 以此类推，直到所有元素均排序完毕

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#define SWAP(a, b) (a ^= b, b ^= a, a ^= b)

/**
 * a:待排序的数组
 * n:数组的长度
*/
void select_sort(int a[], int n)
{
	int i;		// 有序区的末尾位置
	int j;		// 无序区的起始位置
	int nMin;	// 无序区中最小元素位置

	for (i = 0; i < n; ++i)
	{
		nMin = i;
		// 找出a[i+1]...a[n]之间的最小元素位置，并赋值给nMin
		for (j = i + 1; j < n; ++j)
			if (a[j] < a[nMin])
				nMin = j;

		// 若nMin != i,则交换a[i]和a[nMin]
		// 交换之后，保证了a[0]...a[i]之间的元素是有序的
		if (nMin != i)
			SWAP(a[i], a[nMin]);
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

	select_sort(a, ilen);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}
