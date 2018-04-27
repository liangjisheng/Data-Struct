
// ���������ΪLSD(Least significant digital)��MSD(Most significant digital)
// LSD������ʽ����ֵ�����ұ�(��λ)��ʼ����MSD���෴������ֵ�������(��λ)��ʼ
// ע��һ�㣺LSD�Ļ�������������λ���ٵ����У����λ����Ļ���ʹ��MSD��Ч�ʻ�ȽϺ�
// MSD�ķ�ʽ��LSD�෴�����ɸ�λ��Ϊ���׿�ʼ���з��䣬���ڷ���֮�󲢲����Ϻϲ���
// һ�������У�������ÿ����Ͱ�ӡ��н�������Ͱ������ÿ��Ͱ���е���ֵ������һ��λ
// ��ֵ���䵽����Ͱ����,�ڽ��������λ���ķ�����ٺϲ��ص�һ��������

// ���λ���ȷ����ȸ������λ�ؼ�������ж������һ������
// �ڸ��ݴε�λ�ؼ������һ������Ľ��������
// �����ظ���֪���������λ�ؼ������һ��������ɣ��Ϳ��Եõ�һ�����������

#include <iostream>
#include <malloc.h>

using namespace std;

#define MAXSIZE 10000

/**
 * ��ȡ��x��dλ�ϵ���(0-9)
*/
int getdigit(int x, int d)
{
	int a[] = { 1, 1, 10, 100 };	// �����λ������������ֻҪ��λ��������
	return (x / a[d]) % 10;
}

/**
 * ��ӡ����
 * a:����
 * n:���鳤��
*/
void PrintArr(int a[], int n)
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
void lsdradix_sort(int arr[], int begin, int end, int d)
{
	const int radix = 10;
	int count[radix], i, j;

	// ����Ͱ�Ŀռ俪��
	int *buckets = new int[end - begin + 1];
	memset(buckets, 0, end - begin + 1);

	// ���շ����׼���ν����������
	for (int k = 1; k <= d; ++k)
	{
		memset(count, 0, radix * sizeof(int));
		memset(buckets, 0, (end - begin + 1) * sizeof(int));

		// ͳ�Ƹ���Ͱ����װ�����ݵĸ���
		for (i = begin; i <= end; ++i)
			count[getdigit(arr[i], k)]++;

		// count[i]��ʾ��i��Ͱ���ұ߽�����
		for (i = 1; i < radix; ++i)
			count[i] += count[i - 1];

		// ����������װ��Ͱ��(ע��װ��ʱ��ķ��似��)
		for (i = end; i >= begin; --i)	// �����������ɨ�裬��֤������ȶ���
		{
			j = getdigit(arr[i], k);		// ����ؼ���ĵ�kλ�����֣� ���磺576�ĵ�3λ��5
			buckets[count[j] - 1] = arr[i];	//�����Ӧ��Ͱ�У�count[j]-1�ǵ�j��Ͱ���ұ߽�����
			--count[j];						//��ӦͰ��װ������������һ
		}

		// ��ʱ��count[i]Ϊ��i��Ͱ����߽�
		
		// �Ӹ���Ͱ���ռ�����
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
