
// HashTable,采用数组实现

#include <stdio.h>

#define DataType int
#define M 30

typedef struct HashNode
{
	DataType data;		// 存储值
	int isNull;			// 标志该位置是否已被填充
}HashTable;

HashTable hashTable[M];


// 对hash表进行初始化
void initHashTable()
{
	int i;
	for (i = 0; i < M; ++i)
		hashTable[i].isNull = 1;		// 初始状态为空
}

// Hash函数
int getHashAddress(DataType key) { return key % M; }

// 向hash表中插入数据
int insert(DataType key)
{
	int address = getHashAddress(key);

	if (hashTable[address].isNull == 1)		// 没有发生冲突
	{
		hashTable[address].data = key;
		hashTable[address].isNull = 0;
	}
	else		// 有冲突
	{
		while (hashTable[address].isNull == 0 && address < M)
			address++;
		if (address == M)		// Hash表发生溢出
			return -1;

		hashTable[address].data = key;
		hashTable[address].isNull = 0;
	}

	return 0;
}

// 查找
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
