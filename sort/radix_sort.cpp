
// ��������(Radix Sort)��Ͱ�������չ�����Ļ���˼���ǣ���������λ���и�ɲ�
// ͬ�����֣�Ȼ��ÿ��λ���ֱ�Ƚϡ�
// ���������ǣ������д��Ƚ���ֵͳһΪͬ������λ���ȣ���λ�϶̵���ǰ�油��
// Ȼ�󣬴����λ��ʼ�����ν���һ���������������λ����һֱ�����λ����
// ����Ժ�, ���оͱ��һ����������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH(arr) ( (sizeof(arr)) / sizeof(arr[0]) )

// ��ȡ����a�е����ֵ
int get_max(int a[], int n)
{
	int i, nMax = a[0];

	for (i = 0; i < n; ++i)
		if (a[i] > nMax)
			nMax = a[i];

	return nMax;
}

/**
 * �����鰴��ĳ��λ����������(Ͱ����)
 * a:����
 * n:���鳤��
 * exp:ָ����������a���ո�ָ����������
 * ���磺������a = { 50, 3, 542, 745, 2014, 154, 63, 616 }
 *	1.��exp=1��ʾ���ո�λ������a��������
 *  2.��exp=10��ʾ����ʮλ������a��������
 *  3.��exp=100��ʾ���հ�λ������a��������
 *  ...
*/
void count_sort(int a[], int n, int exp)
{
	int *output = NULL;		// �洢"���������ݵ���ʱ����"
	output = (int *)malloc(n * sizeof(int));
	if (NULL == output)
		return ;

	memset(output, 0, n * sizeof(int));
	int i, buckets[10] = {0};

	// �����ݳ��ֵĴ����洢��buckets[]��
	for (i = 0; i < n; ++i)
		buckets[(a[i] / exp) % 10]++;

	// ����buckets[i],Ŀ�����ø��ĺ��buckets[i]��ֵ���Ǹ�������output[]�е�λ��
	for (i = 1; i < 10; ++i)
		buckets[i] += buckets[i - 1];

	// �����ݴ洢����ʱ����output[]��
	// �����ʼ��Ϊ�˱�֤�����㷨���ȶ���
	for (i = n - 1; i >= 0; --i)
	{
		output[buckets[(a[i] / exp) % 10] - 1] = a[i];
		buckets[(a[i] / exp) % 10]--;
	}

	// ���ź��������ֵ����a[]
	for (i = 0; i < n; ++i)
		a[i] = output[i];

	free(output);
}

/**
 * ��������
 * a:����
 * n:���鳤��
*/
void radix_sort(int a[], int n)
{
	int exp;	// ָ�����������鰴��λ��������ʱ��exp = 1����ʮλ��������ʱ��exp = 10
	int nMax = get_max(a, n);

	// �Ӹ�λ��ʼ��������a��ָ����������
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
