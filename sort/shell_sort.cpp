
// ϣ������(Shell Sort)�ǲ��������һ�֣��������ֱ�Ӳ��������㷨�ĸĽ����÷����ֳ�Ϊ
// ��С����������DL.Shell��1959�������������
// ϣ������ʵ������һ�ַ�����뷽�������Ļ���˼����: ����n��������������У�ȡһ��С��n
// ������gap(gap����Ϊ����)��������Ԫ�طֳ����ɸ��������У����о���Ϊgap�ı����ļ�¼��
// ��ͬһ�����У�Ȼ��Ը����ڵ�Ԫ�ؽ���ֱ�Ӳ���������һ���������֮��ÿһ���Ԫ�ض�
// ������ġ�Ȼ���Сgap��ֵ�����ظ�ִ�������ķ���������ظ������Ĳ�������gap=1ʱ������
// ���о��������

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))

/**
 * a:�����������
 * n:����ĳ���
*/
void shell_sort1(int a[], int n)
{
	int i, j, gap;

	// gapΪ������ÿ�μ�СΪԭ����һ��
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// ��gap���飬��ÿһ�鶼ִ��ֱ�Ӳ�������
		for (i = 0; i < gap; ++i)
		{
			for (j = i + gap; j < n; j += gap)
			{
				// ���a[j] < a[j - gap],��Ѱ��a[j]λ�ã������������ݵ�λ�ö�����
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

// Ϊ�˱��ڹ۲죬��ϣ�������е�ֱ�Ӳ��������������

/**
 * a:�����������
 * n:�����ܵĳ���
 * i:�����ʼλ��
 * gap:��Ĳ���
 * ���Ǵ�i��ʼ�������gap���ȵ�����ȡ������ɵ�
*/
void group_sort(int a[], int n, int i, int gap)
{
	int j;

	for (j = i + gap; j < n; j += gap)
	{
		// ���a[j] < a[j - gap],��Ѱ��a[j]λ�ã������������ݵ�λ�ö�����
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

	// gapΪ������ÿ�μ�СΪԭ����һ��
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// ��gap���飬��ÿһ�鶼ִ��ֱ�Ӳ�������
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
