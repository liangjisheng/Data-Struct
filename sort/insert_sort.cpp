
// ֱ�Ӳ�������(Straight Inserting Sort)�Ļ���˼����:��n���������Ԫ�ؿ���Ϊһ�������
// ��һ���������ʼʱ�������ֻ����1��Ԫ�أ�������а���n-1��Ԫ�أ����������ÿ�δ�
// �������ȡ����һ��Ԫ�أ��������뵽������е��ʵ�λ�ã�ʹ֮��Ϊ�µ�������ظ�n-1��
// ������������

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))

/**
 * a:�����������
 * n:����ĳ���
*/
void insert_sort(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; ++i)
	{
		// Ϊa[i]��ǰ���a[0...i-1]������������һ�����ʵ�λ��
		for (j = i - 1; j >= 0; --j)
			if (a[j] < a[i])
				break;

		// ����ҵ���һ�����ʵ�λ��
		if (j != i - 1)
		{
			// ����a[i]�������������
			int tmp = a[i];
			for (k = i - 1; k > j; --k)
				a[k + 1] = a[k];
			// ��a[i]�ŵ���ȷ��λ����
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
