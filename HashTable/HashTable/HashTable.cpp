
#include "HashTable.h"

// 除留取余法
static int HashFunc(KeyType Key) { return Key % HASHTABLE_SIZE; }

static _ElementNode_* HashTableFind_(HashTable Hash, KeyType Key)
{
	int pos = 0, i = 0;
	HashBucket *p = NULL;

	if (NULL == Hash)
		return NULL;

	pos = HashFunc(Key);		// 求Key所对应的基桶
	p = Hash + pos;				// 指向该基桶

	// 在基桶内寻找位置
	for (i = 0; i < BUCKET_SIZE; ++i)
		if (Key == p->Data[i].Key)
			return p->Data + i;

	// 不在基桶中，到溢出桶中查找
	while (p->Bucket)
	{
		p = p->Bucket;
		for (i = 0; i < BUCKET_SIZE; ++i)
			if (Key == p->Data[i].Key)
				return p->Data + i;
	}

	// 溢出桶中也没有
	return NULL;
}

// 更新桶内一个元素，如果元素存在则用新值更新，如果元素不存在则找空位置插入
static bool UpdateBucket(HashBucket *p, KeyType Key, EleType Data)
{
	int i = 0; 
	// 遍历基桶中的每个位置，查找是否有空位，或者是否可以更新现有元素
	for (i = 0; i < BUCKET_SIZE; ++i)
	{
		//Key已存在则更新Val，相当于是对已存在元素进行修改
		if (Key == p->Data[i].Key)
		{
			p->Data[i].Val = Data;
			return true;
		}

		//Key不存在则增加元素记录，即将新元素存入哈希表
		if (INVALID_VALUE == p->Data[i].Key)
		{
			p->Data[i].Key = Key;
			p->Data[i].Val = Data;
			return true;
		}
	}

	// 当桶内元素满了，且桶内没有与Key相等的键值，则更新失败
	return false;
}

// 创建一张含有HASHTABLE_SIZE个基桶的哈希表
bool HashTableInit(HashTable *Hash)
{
	int i = 0, j = 0;
	HashBucket *p = (HashBucket *)malloc(sizeof(HashBucket) * HASHTABLE_SIZE);
	if (NULL == p)
	{
		*Hash = NULL;
		return false;
	}

	// 初始化全部基桶
	for (i = 0; i < HASHTABLE_SIZE; ++i)
	{
		// 初始化桶内每个位置
		for (j = 0; j < BUCKET_SIZE; ++j)
		{
			p[i].Data[j].Key = INVALID_VALUE;
			p[i].Data[j].Val = INVALID_VALUE;
		}
		p[i].Bucket = NULL;
	}

	*Hash = p;
	return true;
}

// 插入函数，当Key以存在时，更新元素，否则在空位置中插入元素
bool HashTableInsert(HashTable Hash, KeyType Key, EleType Data)
{
	int pos = 0, i = 0;
	HashBucket *p = NULL, *s = NULL;
	if (NULL == Hash)
		return false;

	pos = HashFunc(Key);		// Key所对应的基桶
	p = Hash + pos;				// 指向该基桶

	// 桶内元素更新,更新成功返回true
	if (true == UpdateBucket(p, Key, Data))
		return true;

	// 基桶内没有空位置，在溢出桶内寻找位置
	while (p->Bucket)
	{
		p = p->Bucket;
		// 桶内元素更新成功
		if (true == UpdateBucket(p, Key, Data))
			return true;
	}

	// 在已查找过的桶内都未能找到合适的位置，创建一个新的溢出桶来存储元素
	s = (HashBucket *)malloc(sizeof(HashBucket));
	if (NULL == s)
		return false;

	// 初始化桶
	for (i = 0; i < BUCKET_SIZE; ++i)
	{
		s->Data[i].Key = INVALID_VALUE;
		s->Data[i].Val = INVALID_VALUE;
	}
	s->Bucket = NULL;

	s->Data[0].Key = Key;		// 将Key值对存储在溢出桶首位置中
	s->Data[0].Val = Data;
	p->Bucket = s;				// 将新桶挂接上去

	return true;
}

EleType* HashTableFind(HashTable Hash, KeyType Key)
{
	_ElementNode_ *p = HashTableFind_(Hash, Key);
	if (p)
		return &(p->Val);

	return NULL;
}

bool HashTableDelete(HashTable Hash, KeyType Key)
{
	_ElementNode_ *p = HashTableFind_(Hash, Key);

	if (p)
	{
		// 查找、插入都是根据Key值来的，因此只需覆盖Key即可
		p->Key = INVALID_VALUE;
		return true;
	}
	else
		return false;
}

void HashTablePrint(HashTable Hash)
{
	if (NULL == Hash)
		return ;

	int i = 0, j = 0;
	HashBucket *p = Hash, *q = NULL;
	for (i = 0; i < HASHTABLE_SIZE; ++i)
	{
		p = Hash + i;
		// 打印基桶
		printf("BaseBucket%d: ", i);
		for (j = 0; j < BUCKET_SIZE; ++j)
			printf("(%d, %d) ", p->Data[j].Key, p->Data[j].Val);
		printf("\n");

		// 打印溢出桶
		q = p->Bucket;
		while (q)
		{
			printf("\t");
			for (j = 0; j < BUCKET_SIZE; ++j)
				printf("(%d, %d) ", q->Data[j].Key, q->Data[j].Val);
			printf("\n");
			q = q->Bucket;
		}
	}
	printf("\n");
}

void HashTableDestroy(HashTable *Hash)
{
	HashBucket *p = NULL, *q = NULL, *s = NULL;
	int i = 0;
	if (NULL == Hash)
		return ;

	p = *Hash;				// 指向首个基桶
	for (i = 0; i < HASHTABLE_SIZE; ++i)
	{
		q = p->Bucket;			// 指向某个基桶的溢出桶所构成的链表
		while (q)				// 释放溢出桶所构成的链表
		{
			s = q->Bucket;
			p->Bucket = s;
			free(q);
			q = s;
		}
		++p;
	}

	free(*Hash);				// 释放全部基桶
	*Hash = NULL;
}
