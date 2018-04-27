
// 基数排序的MSD(Most significant digital)实现
// 最高位优先法通常是一个递归的过程
// 1.先根据最高位关键码K1排序，得到若干对象组，对象组中每个对象都有相同的关键码K1
// 2.在分别对每组中对象根据关键码K2进行排序，按K2的值的不同，在分成若干更小的子组
// 每个子组中的对象具有相同的K1和K2值
// 3.依次重复，直到对关键码Kd完成排序为止
// 4.最后，把所有子组中的对象依次连接起来，就得到一个有序的对象序列

#include <iostream>
#include <malloc.h>

using namespace std;

/**
 * 获取数x第d位上的数(0-9)
*/
int getdigit(int x, int d)
{
	//因为待排数据最大数据也只是两位数，所以在此只需要到十位就满足
	int a[] = { 1, 1, 10 };
	return ((x / a[d]) % 10);	// 确定桶号
}

/**
 * 打印数组
 * a:数组
 * n:数组长度
*/
void printArr(int a[], int n)
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
void msdardix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix] = {0}, i = 0, j = 0;

	// 分配桶的空间
	int *buckets = new int[end - begin + 1];
	memset(buckets, 0, sizeof(int) * (end - begin + 1));

	// 统计各桶需要装的元素的个数
	for (i = begin; i <= end; ++i)
		count[getdigit(arr[i], d)]++;

	// 求出桶的边界索引，count[i]的值为第i个桶的右边界索引+1
	for (i = 1; i < radix; ++i)
		count[i] += count[i - 1];

	// 这里从右向左扫描，保证排序的稳定性
	for (i = end; i >= begin; --i)
	{
		j = getdigit(arr[i], d);		// 求出关键码的第k位的数字， 例如：576的第3位是5
		buckets[count[j] - 1] = arr[i];	// 放入对应的桶中，count[j]-1是第j个桶的右边界索引
		--count[j];						// 第j个桶放下一个元素的位置(右边界索引+1)
	}

	// 此时，count[i]为第i个桶的左边界

	// 从各个桶中收集数据
	for (i = begin, j = 0; i <= end; ++i, ++j)
		arr[i] = buckets[j];

	int tmp[20] = {0};
	for (i = begin, j = 0; i <= end; ++i, ++j)
		tmp[j] = arr[i];

	free(buckets);

	// 对各个桶中数据进行再排序
	for (i = 0; i < radix - 1; ++i)
	{
		int begin_i = begin + count[i];			// 第i个桶的左边界
		int end_i = begin + count[i + 1] - 1;	// 第i个桶的右边界
		if (begin_i < end_i && d > 1)
			//对第i个桶递归调用，进行基数排序，数位降1
			msdardix_sort(arr, begin_i, end_i, d - 1);
	}
}


int main()
{
	int a[] = { 12, 14, 54, 5, 6, 3, 9, 8, 47, 89 };
	int ilen = sizeof(a) / sizeof(a[0]);

	cout << "before sort: " << endl;
	printArr(a, ilen);

	msdardix_sort(a, 0, ilen - 1, 2);

	cout << "after sort :" << endl;
	printArr(a, ilen);

	system("pause");
	return 0;
}
