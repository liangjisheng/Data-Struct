
// http://www.cnblogs.com/skywang12345/p/3602369.html
// ���������������кϲ���һ���������У����ǳ�֮Ϊ"�鲢"
// �鲢�������"��������"��"��������"2�ַ�ʽ
// 1. �������ϵĹ鲢���򣺽�����������зֳ����ɸ�����Ϊ1�������У�Ȼ����Щ����
// �����ϲ����õ����ɸ�����Ϊ2���������У��ٽ���Щ���������ϲ����õ����ɸ�����Ϊ4
// ���������У��ٽ����������ϲ���ֱ�Ӻϲ���һ������Ϊֹ�������͵õ���������Ҫ��������
// 2. �������µĹ鲢��������"��������"���������Ƿ�����ġ�����������3����
// �� �ֽ� -- ����ǰ����һ��Ϊ����������ѵ� mid = (low + high)/2; 
// �� ��� -- �ݹ�ض�����������a[low...mid] �� a[mid+1...high]���й鲢����
//    �ݹ���ս������������䳤��Ϊ1��
// �� �ϲ� -- �������������������a[low...mid]�� a[mid+1...high]�鲢Ϊһ�������
//    ����a[low...high]

#include <stdio.h>
#include <stdlib.h>

#define LENGTH(arr) ( (sizeof(arr)) / (sizeof(arr[0])) )

/**
 * ��һ������������������������ϲ���һ��
 * a���������������������ʼ��ַ
 * start:��һ�������������ʼ��ַ
 * mid����һ����������Ľ�����ַ��Ҳ�ǵڶ��������������ʼ��ַ
 * end���ڶ�����������Ľ�����ַ
*/
void merge(int a[], int start, int mid, int end)
{
	// tmp�Ǵ洢���������������ʱ����
	int *tmp = (int *)malloc((end - start + 1) * sizeof(int));
	int i = start;		// ��һ���������������
	int j = mid + 1;	// �ڶ����������������
	int k = 0;			// ��ʱ���������

	while (i <= mid && j <= end)
	{
		if (a[i] <= a[j])
			tmp[k++] = a[i++];
		else
			tmp[k++] = a[j++];
	}

	while (i <= mid)
		tmp[k++] = a[i++];

	while (j <= end)
		tmp[k++] = a[j++];

	// ��������Ԫ�أ�ȫ�����ϵ�����a��
	for (i = 0; i < k; ++i)
		a[start + i] = tmp[i];

	free(tmp);
}

/**
 * �鲢����(���ϵ���)
 * a�������������
 * start:�������ʼ��ַ
 * end:����Ľ�����ַ
*/
void merge_sort_up2down(int a[], int start, int end)
{
	if (a == NULL || start >= end)
		return ;

	int mid = (end + start) / 2;
	merge_sort_up2down(a, start, mid);		// �ݹ�����a[start...mid]
	merge_sort_up2down(a, mid + 1, end);	// �ݹ�����a[mid+1...end]

	// a[start...mid] �� a[mid...end]����������ռ䣬
	// �����������һ������ռ�a[start...end]
	merge(a, start, mid, end);
}

/**
 * ������a�����ɴκϲ�������a���ܳ���Ϊlen��������Ϊ���ɸ�����Ϊgap��������
 * ��ÿ�������ڵ���������кϲ�����
 * a:�����������
 * len:����ĳ���
 * gap:������ĳ���
*/
void merge_group(int a[], int len, int gap)
{
	int i;
	int twolen = 2 * gap;

	// ��2�����ڵ���������кϲ�����
	for (i = 0; i + 2 * gap - 1 < len; i += (2 * gap))
		merge(a, i, i + gap - 1, i + 2 * gap - 1);

	// �� i+gap-1 < len-1����ʣ��һ��������û�����
	// ����������ϲ����������������
	if (i + gap - 1 < len - 1)
		merge(a, i, i + gap - 1, len - 1);
}

/**
 * �鲢����(��������)
 * a:�����������
 * len:����ĳ���
*/
void merge_sort_down2up(int a[], int len)
{
	int n;
	if (a == NULL && len <= 0)
		return ;

	for (n = 1; n < len; n *= 2)
		merge_group(a, len, n);
}


void main()
{
	int i;
	int a[] = { 80, 30, 60, 40, 20, 10, 50, 70 };
	int ilen = LENGTH(a);

	printf("before sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	// merge_sort_up2down(a, 0, ilen - 1);		// �鲢����(��������)
	merge_sort_down2up(a, ilen);				// �鲢����(��������)

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}