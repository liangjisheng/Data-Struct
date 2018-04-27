
// Ͱ����(Bucket Sort)��ԭ��ܼ򵥣����ǽ�����ֵ�����������Ͱ����
// ��������������a�й���N��������������֪����a�����ݵķ�Χ[0, MAX)����Ͱ����ʱ
// ��������ΪMAX��Ͱ����r������Ͱ����Ԫ�ض���ʼ��Ϊ0��������ΪMAX��Ͱ�����е�ÿһ
// ����Ԫ������һ��"Ͱ"��
// ������ʱ�������������a��������a��ֵ����Ϊ"Ͱ����r"���±ꡣ��a�����ݱ���ȡʱ
// �ͽ�Ͱ��ֵ��1�����磬��ȡ������a[3]=5����r[5]��ֵ+1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

/**
 * Ͱ����
 * a: ����������
 * n: ���鳤��
 * nMax: ����a�����ֵ�ķ�Χ
*/
void bucket_sort(int a[], int n, int nMax)
{
	int i = 0, j = 0;
	int *buckets = NULL;

	if (a == NULL || n < 1 || nMax < 1)
		return ;

	// ����һ������Ϊmax������buckets�����ҽ�buckets�е��������ݶ���ʼ��Ϊ0
	if ((buckets = (int *)malloc(nMax * sizeof(int))) == NULL)
		return ;
	memset(buckets, 0, nMax * sizeof(int));

	// 1.����
	for (i = 0; i < n; ++i)
		buckets[a[i]]++;

	// 2.����
	for (i = 0, j = 0; i < nMax; ++i)
		while ((buckets[i]--) > 0)
			a[j++] = i;

	free(buckets);
}


void main()
{
	int i;
	int a[] = { 8, 2, 3, 4, 3, 6, 6, 3, 9 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	bucket_sort(a, ilen, 10);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}