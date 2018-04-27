
// 除留余数法定址，线性探测法解决冲突

#include <stdio.h>

#define MaxSize 100				// 最大哈希表长度
#define NULLKEY -1				// 空关键字
#define DELKEY -2				// 被删关键字

typedef int KeyType;			// 关键字类型
typedef char* InfoType;			// 其他数据类型

typedef struct 
{
	KeyType key;				// 关键字域
	InfoType data;				// 其他数据域
	int count;					// 探查次数域
}HashData;

typedef HashData HashTable[MaxSize];		// 哈希表类型

/*
 * p表示小于等于哈希表长度的质数
 * m:哈希表长度
*/
void InsertHT(HashTable ha, KeyType k, int m, int p)
{
	int i, adr;
	adr = k % p;

	// key可以直接放在哈希表中
	if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
	{
		ha[adr].key = k;
		ha[adr].count = 1;
	}
	else
	{
		// 发生冲突时采用线性探查法解决冲突
		i = 1;
		do {
			adr = (adr + 1) % m;
			i++;
		}while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY);

		ha[adr].key = k;
		ha[adr].count = i;
	}
}

/*
 * ha表示哈希表
 * x[]表示插入的关键字
 * n表示x[]关键字序列的长度
 * m表示哈希表的长度
 * p表示小于等于m的质数
*/
void CreateHT(HashTable ha, KeyType x[], int n, int m, int p)
{
	int i, n1 = 0;
	for (i = 0; i < m; ++i)
	{
		ha[i].key = NULLKEY;
		ha[i].count = 0;
	}

	for (i = 0; i < n; ++i)
		InsertHT(ha, x[i], m, p);
}

/*
 * ha表示哈希表
 * p表示小于等于哈希表长度的质数
 * k要查找的关键字
 * 返回值: 成功返回哈希地址，失败返回-1
*/
int SearchHT(HashTable ha, int m, int p, KeyType k)
{
	int i = 0, adr;
	adr = k % p;

	while (ha[adr].key != NULLKEY && ha[adr].key != k)
	{
		i++;
		adr = (adr + 1) % m;
	}

	if (ha[adr].key == k)
		return adr;
	else
		return -1;
}

/*
 * ha: 哈希表
 * p：小于等于哈希表长度的质数
 * k：要删除的关键字
 * n：哈希表长度
 * 返回值：成功返回0，失败返回-1
*/
int DeleteHT(HashTable ha, int m, int p, int k)
{
	int adr = SearchHT(ha, m, p, k);
	if (-1 != adr)
	{
		ha[adr].key = DELKEY;
		return 0;
	}
	else
		return -1;
}

/*
 * print hash table
 * m为哈希表长度
 * n为关键字个数
*/
void DispHT(HashTable ha, int n, int m)
{
	float avg = 0;
	int i;

	printf("哈希表地址: \t");
	for (i = 0; i < m; ++i)
	{
		if (ha[i].key != NULLKEY && ha[i].key != DELKEY)
			printf("%3d", i);
	}
	printf("\n");

	printf("哈希表关键字: \t");
	for (i = 0; i < m; ++i)
	{
		//if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
		//	printf("   ");
		//else
		//	printf("%3d", ha[i].key);
		if (ha[i].key != NULLKEY && ha[i].key != DELKEY)
			printf("%3d", ha[i].key);
	}
	printf("\n");

	printf("搜索次数: \t");
	for (i = 0; i < m; ++i)
	{
		//if (ha[i].key == NULLKEY || ha[i].key == DELKEY)
		//	printf("   ");
		//else
		//	printf("%3d", ha[i].count);
		if (ha[i].key != NULLKEY && ha[i].key != DELKEY)
			printf("%3d", ha[i].count);
	}
	printf("\n");

	for (i = 0; i < m; ++i)
		if (ha[i].key != NULLKEY && ha[i].key != DELKEY)
			avg = avg + ha[i].count;
	avg = avg / n;
	printf("平均搜索长度ASL(%d) = %g\n", n, avg);
}


int main()
{
	int x[] = { 16, 74, 60, 43, 54, 90, 46, 31, 29, 88, 77 };
	int n = sizeof(x) / sizeof(x[0]);
	// n:关键字个数
	// m:哈希表长度
	// p:小于等于m的质数
	int m = 13, p = 11, i, k = 54;

	HashTable ha;
	CreateHT(ha, x, n, m, p);

	//int len = sizeof(ha) / sizeof(ha[0]);
	//for (i = 0; i < len; ++i)
	//	printf("%d ", ha[i].key);

	printf("\n");
	DispHT(ha, n, m);

	i = SearchHT(ha, m, p, k);
	if (-1 != i)
		printf("ha[%d].kye = %d\n", i, k);
	else
		printf("未找到%d\n", k);

	k = 77;
	printf("删除关键字%d\n", k);
	DeleteHT(ha, m, p, k);
	DispHT(ha, n, m);

	getchar();
	return 0;
}
