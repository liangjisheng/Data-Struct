
#include "HashTable.h"

// ����ȡ�෨
static int HashFunc(KeyType Key) { return Key % HASHTABLE_SIZE; }

static _ElementNode_* HashTableFind_(HashTable Hash, KeyType Key)
{
	int pos = 0, i = 0;
	HashBucket *p = NULL;

	if (NULL == Hash)
		return NULL;

	pos = HashFunc(Key);		// ��Key����Ӧ�Ļ�Ͱ
	p = Hash + pos;				// ָ��û�Ͱ

	// �ڻ�Ͱ��Ѱ��λ��
	for (i = 0; i < BUCKET_SIZE; ++i)
		if (Key == p->Data[i].Key)
			return p->Data + i;

	// ���ڻ�Ͱ�У������Ͱ�в���
	while (p->Bucket)
	{
		p = p->Bucket;
		for (i = 0; i < BUCKET_SIZE; ++i)
			if (Key == p->Data[i].Key)
				return p->Data + i;
	}

	// ���Ͱ��Ҳû��
	return NULL;
}

// ����Ͱ��һ��Ԫ�أ����Ԫ�ش���������ֵ���£����Ԫ�ز��������ҿ�λ�ò���
static bool UpdateBucket(HashBucket *p, KeyType Key, EleType Data)
{
	int i = 0; 
	// ������Ͱ�е�ÿ��λ�ã������Ƿ��п�λ�������Ƿ���Ը�������Ԫ��
	for (i = 0; i < BUCKET_SIZE; ++i)
	{
		//Key�Ѵ��������Val���൱���Ƕ��Ѵ���Ԫ�ؽ����޸�
		if (Key == p->Data[i].Key)
		{
			p->Data[i].Val = Data;
			return true;
		}

		//Key������������Ԫ�ؼ�¼��������Ԫ�ش����ϣ��
		if (INVALID_VALUE == p->Data[i].Key)
		{
			p->Data[i].Key = Key;
			p->Data[i].Val = Data;
			return true;
		}
	}

	// ��Ͱ��Ԫ�����ˣ���Ͱ��û����Key��ȵļ�ֵ�������ʧ��
	return false;
}

// ����һ�ź���HASHTABLE_SIZE����Ͱ�Ĺ�ϣ��
bool HashTableInit(HashTable *Hash)
{
	int i = 0, j = 0;
	HashBucket *p = (HashBucket *)malloc(sizeof(HashBucket) * HASHTABLE_SIZE);
	if (NULL == p)
	{
		*Hash = NULL;
		return false;
	}

	// ��ʼ��ȫ����Ͱ
	for (i = 0; i < HASHTABLE_SIZE; ++i)
	{
		// ��ʼ��Ͱ��ÿ��λ��
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

// ���뺯������Key�Դ���ʱ������Ԫ�أ������ڿ�λ���в���Ԫ��
bool HashTableInsert(HashTable Hash, KeyType Key, EleType Data)
{
	int pos = 0, i = 0;
	HashBucket *p = NULL, *s = NULL;
	if (NULL == Hash)
		return false;

	pos = HashFunc(Key);		// Key����Ӧ�Ļ�Ͱ
	p = Hash + pos;				// ָ��û�Ͱ

	// Ͱ��Ԫ�ظ���,���³ɹ�����true
	if (true == UpdateBucket(p, Key, Data))
		return true;

	// ��Ͱ��û�п�λ�ã������Ͱ��Ѱ��λ��
	while (p->Bucket)
	{
		p = p->Bucket;
		// Ͱ��Ԫ�ظ��³ɹ�
		if (true == UpdateBucket(p, Key, Data))
			return true;
	}

	// ���Ѳ��ҹ���Ͱ�ڶ�δ���ҵ����ʵ�λ�ã�����һ���µ����Ͱ���洢Ԫ��
	s = (HashBucket *)malloc(sizeof(HashBucket));
	if (NULL == s)
		return false;

	// ��ʼ��Ͱ
	for (i = 0; i < BUCKET_SIZE; ++i)
	{
		s->Data[i].Key = INVALID_VALUE;
		s->Data[i].Val = INVALID_VALUE;
	}
	s->Bucket = NULL;

	s->Data[0].Key = Key;		// ��Keyֵ�Դ洢�����Ͱ��λ����
	s->Data[0].Val = Data;
	p->Bucket = s;				// ����Ͱ�ҽ���ȥ

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
		// ���ҡ����붼�Ǹ���Keyֵ���ģ����ֻ�踲��Key����
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
		// ��ӡ��Ͱ
		printf("BaseBucket%d: ", i);
		for (j = 0; j < BUCKET_SIZE; ++j)
			printf("(%d, %d) ", p->Data[j].Key, p->Data[j].Val);
		printf("\n");

		// ��ӡ���Ͱ
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

	p = *Hash;				// ָ���׸���Ͱ
	for (i = 0; i < HASHTABLE_SIZE; ++i)
	{
		q = p->Bucket;			// ָ��ĳ����Ͱ�����Ͱ�����ɵ�����
		while (q)				// �ͷ����Ͱ�����ɵ�����
		{
			s = q->Bucket;
			p->Bucket = s;
			free(q);
			q = s;
		}
		++p;
	}

	free(*Hash);				// �ͷ�ȫ����Ͱ
	*Hash = NULL;
}
