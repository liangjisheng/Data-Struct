
// 直接插入排序(Straight Inserting Sort)的基本思想是:把n个待排序的元素看成为一个有序表
// 和一个无序表，开始时有序表中只包含1个元素，无序表中包含n-1个元素，排序过程中每次从
// 无序表中取出第一个元素，将它插入到有序表中的适当位置，使之成为新的有序表，重复n-1次
// 可完成排序过程

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))

/**
 * a:待排序的数组
 * n:数组的长度
*/
void insert_sort(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; ++i)
	{
		// 为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
		for (j = i - 1; j >= 0; --j)
			if (a[j] < a[i])
				break;

		// 如果找到了一个合适的位置
		if (j != i - 1)
		{
			// 将比a[i]大的数据往后移
			int tmp = a[i];
			for (k = i - 1; k > j; --k)
				a[k + 1] = a[k];
			// 将a[i]放到正确的位置上
			a[k + 1] = tmp;
		}
	}
}


void main()
{
	int i;
	int a[] = { 20, 40, 30, 10, 60, 50 };
	int ilen = LENGTH(a);

	printf("before sort:\n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	insert_sort(a, ilen);

	printf("after sort:\n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}
