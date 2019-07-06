
// 基数排序(Radix Sort)是桶排序的扩展，它的基本思想是：将整数按位数切割成不
// 同的数字，然后按每个位数分别比较。
// 具体做法是：将所有待比较数值统一为同样的数位长度，数位较短的数前面补零
// 然后，从最低位开始，依次进行一次排序。这样从最低位排序一直到最高位排序
// 完成以后, 数列就变成一个有序序列

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(arr) ( (sizeof(arr)) / sizeof(arr[0]) )

// 获取数组a中的最大值
int get_max(int a[], int n)
{
	int i, nMax = a[0];

	for (i = 0; i < n; ++i)
		if (a[i] > nMax)
			nMax = a[i];

	return nMax;
}

/**
 * 对数组按照某个位数进行排序(桶排序)
 * a:数组
 * n:数组长度
 * exp:指数，对数组a按照该指数进行排序
 * 例如：对数组a = { 50, 3, 542, 745, 2014, 154, 63, 616 }
 *	1.当exp=1表示按照个位对数组a进行排序
 *  2.当exp=10表示按照十位对数组a进行排序
 *  3.当exp=100表示按照百位对数组a进行排序
 *  ...
*/
void count_sort(int a[], int n, int exp)
{
	int *output = NULL;		// 存储"被排序数据的临时数组"
	output = (int *)malloc(n * sizeof(int));
	if (NULL == output)
		return ;

	memset(output, 0, n * sizeof(int));
	int i, buckets[10] = {0};

	// 将数据出现的次数存储在buckets[]中
	for (i = 0; i < n; ++i)
		buckets[(a[i] / exp) % 10]++;

	// 更改buckets[i],目的是让更改后的buckets[i]的值，是该数据在output[]中的位置
	for (i = 1; i < 10; ++i)
		buckets[i] += buckets[i - 1];

	// 将数据存储到临时数组output[]中
	// 从最后开始是为了保证排序算法的稳定性
	for (i = n - 1; i >= 0; --i)
	{
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		buckets[(a[i] / exp) % 10]--;
	}

	// 将排好序的数据值赋给a[]
	for (i = 0; i < n; ++i)
		a[i] = output[i];

	free(output);
}

/**
 * 基数排序
 * a:数组
 * n:数组长度
*/
void radix_sort(int a[], int n)
{
	int exp;	// 指数，当对数组按个位进行排序时，exp = 1；按十位进行排序时，exp = 10
	int nMax = get_max(a, n);

	// 从个位开始，对数组a按指数进行排序
	for (exp = 1; nMax / exp > 0; exp *= 10)
		count_sort(a, n, exp);
}


void main()
{
	int i;
	int a[] = { 53, 3, 542, 748, 14, 214, 154, 63, 616 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	radix_sort(a, ilen);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}
