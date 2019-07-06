
// 基数排序分为LSD(Least significant digital)或MSD(Most significant digital)
// LSD的排序方式由数值的最右边(低位)开始，而MSD则相反，由数值的最左边(高位)开始
// 注意一点：LSD的基数排序适用于位数少的数列，如果位数多的话，使用MSD的效率会比较好
// MSD的方式与LSD相反，是由高位数为基底开始进行分配，但在分配之后并不马上合并回
// 一个数组中，而是在每个“桶子”中建立“子桶”，将每个桶子中的数值按照下一数位
// 的值分配到“子桶”中,在进行完最低位数的分配后再合并回单一的数组中

// 最低位优先法首先根据最低位关键码对所有对象进行一趟排序
// 在根据次低位关键码对上一趟排序的结果再排序
// 依次重复，知道依据最高位关键码最后一趟排序完成，就可以得到一个有序的序列

#include <iostream>
#include <malloc.h>

using namespace std;

#define MAXSIZE 10000

/**
 * 获取数x第d位上的数(0-9)
*/
int getdigit(int x, int d)
{
	int a[] = { 1, 1, 10, 100 };	// 最大三位数，所以这里只要百位就满足了
	return (x / a[d]) % 10;
}

/**
 * 打印数组
 * a:数组
 * n:数组长度
*/
void PrintArr(int a[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
}

/**
 * arr:待排序的数组
 * begin:开始索引(一般为0)
 * end:结束索引(一般为数组长度-1)
 * d:最大数共有多少位
*/
void lsdradix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix], i, j;

	// 所有桶的空间开辟
	int *buckets = new int[end - begin + 1];
	memset(buckets, 0, end - begin + 1);

	// 按照分配标准依次进行排序过程
	for (int k = 1; k <= d; ++k)
	{
		memset(count, 0, radix * sizeof(int));
		memset(buckets, 0, (end - begin + 1) * sizeof(int));

		// 统计各个桶中所装的数据的个数
		for (i = begin; i <= end; ++i)
			count[getdigit(arr[i], k)]++;

		// count[i]表示第i个桶的右边界索引
		for (i = 1; i < radix; ++i)
			count[i] += count[i - 1];

		// 把数据依次装入桶中(注意装入时候的分配技巧)
		for (i = end; i >= begin; --i)	// 这里从右向左扫描，保证排序的稳定性
		{
			j = getdigit(arr[i], k);		// 求出关键码的第k位的数字， 例如：576的第3位是5
			buckets[count[j] - 1] = arr[i];	//放入对应的桶中，count[j]-1是第j个桶的右边界索引
			--count[j];						//对应桶的装入数据索引减一
		}

		// 此时，count[i]为第i个桶的左边界
		
		// 从各个桶中收集数据
		for (i = begin, j = 0; i <= end; ++i, ++j)
			arr[i] = buckets[j];
	}

	free(buckets);
}


int main()
{
	int arr[] = { 20, 80, 90, 589, 998, 965, 852, 123, 456, 789 };
	int ilen = sizeof(arr) / sizeof(arr[0]);

	cout << "before sort: " << endl;
	PrintArr(arr, ilen);

	lsdradix_sort(arr, 0, ilen - 1, 3);

	cout << "after sort: " << endl;
	PrintArr(arr, ilen);

	system("pause");
	return 0;
}
