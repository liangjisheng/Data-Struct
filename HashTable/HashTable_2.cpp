
// ������������ַ������̽�ⷨ�����ͻ

#include <stdio.h>

#define MaxSize 100				// ����ϣ����
#define NULLKEY -1				// �չؼ���
#define DELKEY -2				// ��ɾ�ؼ���

typedef int KeyType;			// �ؼ�������
typedef char* InfoType;			// ������������

typedef struct 
{
	KeyType key;				// �ؼ�����
	InfoType data;				// ����������
	int count;					// ̽�������
}HashData;

typedef HashData HashTable[MaxSize];		// ��ϣ������

/*
 * p��ʾС�ڵ��ڹ�ϣ���ȵ�����
 * m:��ϣ����
*/
void InsertHT(HashTable ha, KeyType k, int m, int p)
{
	int i, adr;
	adr = k % p;

	// key����ֱ�ӷ��ڹ�ϣ����
	if (ha[adr].key == NULLKEY || ha[adr].key == DELKEY)
	{
		ha[adr].key = k;
		ha[adr].count = 1;
	}
	else
	{
		// ������ͻʱ��������̽�鷨�����ͻ
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
 * ha��ʾ��ϣ��
 * x[]��ʾ����Ĺؼ���
 * n��ʾx[]�ؼ������еĳ���
 * m��ʾ��ϣ��ĳ���
 * p��ʾС�ڵ���m������
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
 * ha��ʾ��ϣ��
 * p��ʾС�ڵ��ڹ�ϣ���ȵ�����
 * kҪ���ҵĹؼ���
 * ����ֵ: �ɹ����ع�ϣ��ַ��ʧ�ܷ���-1
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
 * ha: ��ϣ��
 * p��С�ڵ��ڹ�ϣ���ȵ�����
 * k��Ҫɾ���Ĺؼ���
 * n����ϣ����
 * ����ֵ���ɹ�����0��ʧ�ܷ���-1
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
 * mΪ��ϣ����
 * nΪ�ؼ��ָ���
*/
void DispHT(HashTable ha, int n, int m)
{
	float avg = 0;
	int i;

	printf("��ϣ���ַ: \t");
	for (i = 0; i < m; ++i)
	{
		if (ha[i].key != NULLKEY && ha[i].key != DELKEY)
			printf("%3d", i);
	}
	printf("\n");

	printf("��ϣ��ؼ���: \t");
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

	printf("��������: \t");
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
	printf("ƽ����������ASL(%d) = %g\n", n, avg);
}


int main()
{
	int x[] = { 16, 74, 60, 43, 54, 90, 46, 31, 29, 88, 77 };
	int n = sizeof(x) / sizeof(x[0]);
	// n:�ؼ��ָ���
	// m:��ϣ����
	// p:С�ڵ���m������
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
		printf("δ�ҵ�%d\n", k);

	k = 77;
	printf("ɾ���ؼ���%d\n", k);
	DeleteHT(ha, m, p, k);
	DispHT(ha, n, m);

	getchar();
	return 0;
}
