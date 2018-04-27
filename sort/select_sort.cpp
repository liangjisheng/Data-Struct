
// ѡ������(Selection sort)��һ�ּ�ֱ�۵������㷨
// ���Ļ���˼���ǣ�������δ������������ҵ���С(or���)Ԫ�أ�Ȼ�����ŵ����е���ʼλ��
// ���ţ��ٴ�ʣ��δ�����Ԫ���м���Ѱ����С(or���)Ԫ�أ�Ȼ��ŵ����������е�ĩβ
// �Դ����ƣ�ֱ������Ԫ�ؾ��������

#include <stdio.h>

#define LENGTH(arr) ((sizeof(arr)) / (sizeof(arr[0])))
#define SWAP(a, b) (a ^= b, b ^= a, a ^= b)

/**
 * a:�����������
 * n:����ĳ���
*/
void select_sort(int a[], int n)
{
	int i;		// ��������ĩβλ��
	int j;		// ����������ʼλ��
	int nMin;	// ����������СԪ��λ��

	for (i = 0; i < n; ++i)
	{
		nMin = i;
		// �ҳ�a[i+1]...a[n]֮�����СԪ��λ�ã�����ֵ��nMin
		for (j = i + 1; j < n; ++j)
			if (a[j] < a[nMin])
				nMin = j;

		// ��nMin != i,�򽻻�a[i]��a[nMin]
		// ����֮�󣬱�֤��a[0]...a[i]֮���Ԫ���������
		if (nMin != i)
			SWAP(a[i], a[nMin]);
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

	select_sort(a, ilen);

	printf("after sort: \n");
	for (i = 0; i < ilen; ++i)
		printf("%d ", a[i]);
	printf("\n");

	getchar();
}
