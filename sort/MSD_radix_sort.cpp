
// ���������MSD(Most significant digital)ʵ��
// ���λ���ȷ�ͨ����һ���ݹ�Ĺ���
// 1.�ȸ������λ�ؼ���K1���򣬵õ����ɶ����飬��������ÿ����������ͬ�Ĺؼ���K1
// 2.�ڷֱ��ÿ���ж�����ݹؼ���K2�������򣬰�K2��ֵ�Ĳ�ͬ���ڷֳ����ɸ�С������
// ÿ�������еĶ��������ͬ��K1��K2ֵ
// 3.�����ظ���ֱ���Թؼ���Kd�������Ϊֹ
// 4.��󣬰����������еĶ������������������͵õ�һ������Ķ�������

#include <iostream>
#include <malloc.h>

using namespace std;

/**
 * ��ȡ��x��dλ�ϵ���(0-9)
*/
int getdigit(int x, int d)
{
	//��Ϊ���������������Ҳֻ����λ���������ڴ�ֻ��Ҫ��ʮλ������
	int a[] = { 1, 1, 10 };
	return ((x / a[d]) % 10);	// ȷ��Ͱ��
}

/**
 * ��ӡ����
 * a:����
 * n:���鳤��
*/
void printArr(int a[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	cout << endl;
}

/**
 * arr:�����������
 * begin:��ʼ����(һ��Ϊ0)
 * end:��������(һ��Ϊ���鳤��-1)
 * d:��������ж���λ
*/
void msdardix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix] = {0}, i = 0, j = 0;

	// ����Ͱ�Ŀռ�
	int *buckets = new int[end - begin + 1];
	memset(buckets, 0, sizeof(int) * (end - begin + 1));

	// ͳ�Ƹ�Ͱ��Ҫװ��Ԫ�صĸ���
	for (i = begin; i <= end; ++i)
		count[getdigit(arr[i], d)]++;

	// ���Ͱ�ı߽�������count[i]��ֵΪ��i��Ͱ���ұ߽�����+1
	for (i = 1; i < radix; ++i)
		count[i] += count[i - 1];

	// �����������ɨ�裬��֤������ȶ���
	for (i = end; i >= begin; --i)
	{
		j = getdigit(arr[i], d);		// ����ؼ���ĵ�kλ�����֣� ���磺576�ĵ�3λ��5
		buckets[count[j] - 1] = arr[i];	// �����Ӧ��Ͱ�У�count[j]-1�ǵ�j��Ͱ���ұ߽�����
		--count[j];						// ��j��Ͱ����һ��Ԫ�ص�λ��(�ұ߽�����+1)
	}

	// ��ʱ��count[i]Ϊ��i��Ͱ����߽�

	// �Ӹ���Ͱ���ռ�����
	for (i = begin, j = 0; i <= end; ++i, ++j)
		arr[i] = buckets[j];

	int tmp[20] = {0};
	for (i = begin, j = 0; i <= end; ++i, ++j)
		tmp[j] = arr[i];

	free(buckets);

	// �Ը���Ͱ�����ݽ���������
	for (i = 0; i < radix - 1; ++i)
	{
		int begin_i = begin + count[i];			// ��i��Ͱ����߽�
		int end_i = begin + count[i + 1] - 1;	// ��i��Ͱ���ұ߽�
		if (begin_i < end_i && d > 1)
			//�Ե�i��Ͱ�ݹ���ã����л���������λ��1
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
