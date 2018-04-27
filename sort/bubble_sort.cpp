
// ð������
#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#define  SWAP(a, b) (a ^= b, b ^= a, a ^= b)

/**
 * a:�����������
 * n:����ĳ���
*/
void bubble_sort1(int a[], int n)
{
	int i, j;
	for (i = n - 1; i > 0; --i)
	{
		// ��a[0...i]�е�������ݷ���ĩβ
		for (j = 0; j < i; ++j)
			if (a[j] > a[j + 1])
				SWAP(a[j], a[j + 1]);
	}
}

// ð������Ľ���,���һ����ǣ����һ�˱����з����˽���������Ϊtrue������Ϊfalse
// ���ĳһ��û�з���������˵�������Ѿ����
void bubble_sort2(int a[], int n)
{
	int i, j;
	int flag;		// ���

	for (i = n - 1; i > 0; --i)
	{
		flag = 0;

		for (j = 0; j < i; ++j)
		{
			if (a[j] > a[j + 1])
			{
				SWAP(a[j], a[j + 1]);
				flag = 1;		// �������������������Ϊ1
			}
		}

		if (0 == flag)			// û�з���������˵�������Ѿ�����
			break;
	}
}

void main()
{
	int i;
	int a[] = { 20, 40, 30, 10, 60, 50 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	// bubble_sort1(a, ilen);
	bubble_sort2(a, ilen);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}