
// 希尔排序(Shell Sort)是插入排序的一种，它是针对直接插入排序算法的改进，该方法又称为
// 缩小增量排序，因DL.Shell于1959年提出而得名。
// 希尔排序实质上是一种分组插入方法。它的基本思想是: 对于n个待待排序的数列，取一个小于n
// 的整数gap(gap被称为步长)将待排序元素分成若干个组子序列，所有距离为gap的倍数的记录放
// 在同一个组中；然后对各组内的元素进行直接插入排序。这一趟排序完成之后，每一组的元素都
// 是有序的。然后减小gap的值，并重复执行上述的分组和排序。重复这样的操作，当gap=1时，整个
// 数列就是有序的

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))

/**
 * a:待排序的数组
 * n:数组的长度
*/
void shell_sort1(int a[], int n)
{
	int i, j, gap;

	// gap为步长，每次减小为原来的一半
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// 共gap个组，对每一组都执行直接插入排序
		for (i = 0; i < gap; ++i)
		{
			for (j = i + gap; j < n; j += gap)
			{
				// 如果a[j] < a[j - gap],则寻找a[j]位置，并将后面数据的位置都后移
				if (a[j] < a[j - gap])
				{
					int tmp = a[j];
					int k = j - gap;
					while (k >= 0 && a[k] > tmp)
					{
						a[k + gap] = a[k];
						k -= gap;
					}
					a[k + gap] = tmp;
				}
			}
		}
	}
}

// 为了便于观察，将希尔排序中的直接插入排序独立出来

/**
 * a:待排序的数组
 * n:数组总的长度
 * i:组的起始位置
 * gap:组的步长
 * 组是从i开始，将相隔gap长度的数都取出所组成的
*/
void group_sort(int a[], int n, int i, int gap)
{
	int j;

	for (j = i + gap; j < n; j += gap)
	{
		// 如果a[j] < a[j - gap],则寻找a[j]位置，并将后面数据的位置都后移
		if (a[j] < a[j - gap])
		{
			int tmp = a[j];
			int k = j - gap;
			while (k >= 0 && a[k] > tmp)
			{
				a[k + gap] = a[k];
				k -= gap;
			}
			a[k + gap] = tmp;
		}
	}
}

void shell_sort2(int a[], int n)
{
	int i, gap;

	// gap为步长，每次减小为原来的一半
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// 共gap个组，对每一组都执行直接插入排序
		for (i = 0; i < gap; ++i)
			group_sort(a, n, i, gap);
	}
}


void main()
{
	int i; 
	int a[] = { 80, 30, 60, 40, 20, 10, 50, 70 };
	int ilen = LENGTH(a);

	printf("before sort:\n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	// shell_sort1(a, ilen);
	shell_sort2(a, ilen);

	printf("after sort:\n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}
