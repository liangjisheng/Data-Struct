
// HashTable,��������ʵ��

#include <stdio.h>

#define DataType int
#define M 30

typedef struct HashNode
{
	DataType data;		// �洢ֵ
	int isNull;			// ��־��λ���Ƿ��ѱ����
}HashTable;

HashTable hashTable[M];


// ��hash����г�ʼ��
void initHashTable()
{
	int i;
	for (i = 0; i < M; ++i)
		hashTable[i].isNull = 1;		// ��ʼ״̬Ϊ��
}

// Hash����
int getHashAddress(DataType key) { return key % M; }

// ��hash���в�������
int insert(DataType key)
{
	int address = getHashAddress(key);

	if (hashTable[address].isNull == 1)		// û�з�����ͻ
	{
		hashTable[address].data = key;
		hashTable[address].isNull = 0;
	}
	else		// �г�ͻ
	{
		while (hashTable[address].isNull == 0 && address < M)
			address++;
		if (address == M)		// Hash�������
			return -1;

		hashTable[address].data = key;
		hashTable[address].isNull = 0;
	}

	return 0;
}

// ����
int find(DataType key)
{
	int address = getHashAddress(key);
	while (!(hashTable[address].isNull == 0 && hashTable[address].data == key && address < M))
		address++;
	if (address == M)
		address = -1;
	return address;
}


int main()
{
	int key[] = { 123, 456, 7000, 8, 1, 13, 11, 555, 425, 393, 212, 546, 2, 99, 196 };
	int i;
	initHashTable();
	int lenkey = sizeof(key) / sizeof(key[0]);
	for (i = 0; i < lenkey; ++i)
		insert(key[i]);

	// print hashtable
	int lenhashtable = sizeof(hashTable) / sizeof(hashTable[0]);
	for (i = 0; i < M; ++i)
	{
		if (hashTable[i].isNull == 0)
			printf("%d %d\n", hashTable[i].data, i);
	}
	printf("\n");

	for (i = 0; i < lenkey; ++i)
	{
		int address = find(key[i]);
		//if (-1 != address)
		printf("%d %d\n", key[i], address);
	}

	getchar();
	return 0;
}
