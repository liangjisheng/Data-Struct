
// 快速排序(Quick Sort)使用分治法策略
// 它的基本思想是：选择一个基准数，通过一趟排序将要排序的数据分割成独立的两部分
// 其中一部分的所有数据都比另外一部分的所有数据都要小。然后，再按此方法对这两部
// 分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列

// 快速排序流程：
// (1) 从数列中挑出一个基准值。
// (2) 将所有比基准值小的摆放在基准前面，所有比基准值大的摆在基准的后面(相同的数可以到任一边)
// 在这个分区退出之后，该基准就处于数列的中间位置。
// (3) 递归地把"基准值前面的子数列"和"基准值后面的子数列"进行排序

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))


/**
 * a:待排序的数组
 * l:数组的左边界(例如，从其实位置开始排序,则l = 0)
 * r:数组的右边界(例如，排序截止到数组末尾，则r = a.length - 1)
*/
void quick_sort(int a[], int l, int r)
{
	if (l < r)
	{
		int i, j, x;
		i = l;
		j = r;
		x = a[i];

		while (i < j)
		{
			while (i < j && a[j] > x)
				j--;		// 从右向左找第一个小于x的数
			if (i < j)
				a[i++] = a[j];
			while (i < j && a[i] < x)
				i++;		// 从左向右找第一个大于x的数
			if (i < j)
				a[j--] = a[i];
		}
		a[i] = x;
		quick_sort(a, l, i - 1);	// 递归调用
		quick_sort(a, i + 1, r);
	}
}


void main()
{
	int i;
	int a[] = { 30, 40, 60, 10, 20, 50 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	quick_sort(a, 0, ilen - 1);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}