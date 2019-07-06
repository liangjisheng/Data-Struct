
#include "HashTable.h"
#include <stdio.h>

int main()
{
	HashTable hash = NULL;
	EleType *e = NULL;
	KeyType KeyArray[] = { 1, 18, 35, 52, 69, 86, 103, 120, 137, 171, 171, 188, 205, 222, 239, 255, 273 };
	EleType EleArray[] = { 10, 180, 350, 520, 690, 860, 1030, 1200, 1370, 1710, 0, 1880, 2050, 2220, 2390, 2550, 2730 };
	int KeySize = sizeof(KeyArray) / sizeof(KeyArray[0]);
	int EleSize = sizeof(EleArray) / sizeof(EleArray[0]);
	int i = 0;
	bool ret = true;
	KeyType key = 0;

	HashTableInit(&hash);
	HashTablePrint(hash);

	for (i = 0; i < KeySize && ret; ++i)
		ret = HashTableInsert(hash, KeyArray[i], EleArray[i]);
	HashTablePrint(hash);

	key = 156;
	e = HashTableFind(hash, key);
	if (NULL != e)
	{
		printf("值为: %d\n", *e);
		*e = 123;
		printf("修改后\n");
		e = HashTableFind(hash, key);
		if (NULL != e)
			printf("值为: %d\n", *e);
	}
	else
		printf("键%d不存在\n", key);

	key = 171;
	ret = HashTableDelete(hash, key);
	if (true == ret)
	{
		printf("键值对%d删除成功\n", key);
		e = HashTableFind(hash, key);
		if (NULL != e)
			printf("值为%d\n", *e);
		else
			printf("键%d不存在\n", key);
	}
	else
		printf("键%d不存在\n", key);

	HashTableDestroy(&hash);

	getchar();
	return 0;
}