
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

// http://blog.csdn.net/Hello_World_LVLcoder/article/details/72774006

#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 5		// 溢出桶的大小，此处的值表示可容纳5个元素
#define HASHTABLE_SIZE 17	// 哈希表的基桶个数，为了使得出的哈希因子在所有可得的值中
							// 得出任一值的概率相同，所有使用素数作为基桶个数
#define INVALID_VALUE -11111	// 无效标记

typedef int EleType;
typedef int KeyType;

struct _ElementNode_		// 元素节点类型，键值对
{
	KeyType Key;
	EleType Val;
};

typedef struct _HashBucket_
{
	_ElementNode_ Data[BUCKET_SIZE];
	struct _HashBucket_ *Bucket;		// 解决冲突的方式是链地址法
}HashBucket;	// 桶节点类型

typedef HashBucket* HashTable;

bool HashTableInit(HashTable *Hash);					// 初始化哈希表
bool HashTableInsert(HashTable Hash, KeyType Key, EleType Data);	// 插入键值对
EleType* HashTableFind(HashTable Hash, KeyType Key);	// 根据键查找值
bool HashTableDelete(HashTable Hash, KeyType Key);		// 删除键值对
void HashTablePrint(HashTable Hash);					// 打印哈希表
void HashTableDestroy(HashTable *Hash);					// 销毁哈希表

#endif // _HASHTABLE_H_