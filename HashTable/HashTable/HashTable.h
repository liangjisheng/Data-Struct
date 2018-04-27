
#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

// http://blog.csdn.net/Hello_World_LVLcoder/article/details/72774006

#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 5		// ���Ͱ�Ĵ�С���˴���ֵ��ʾ������5��Ԫ��
#define HASHTABLE_SIZE 17	// ��ϣ��Ļ�Ͱ������Ϊ��ʹ�ó��Ĺ�ϣ���������пɵõ�ֵ��
							// �ó���һֵ�ĸ�����ͬ������ʹ��������Ϊ��Ͱ����
#define INVALID_VALUE -11111	// ��Ч���

typedef int EleType;
typedef int KeyType;

struct _ElementNode_		// Ԫ�ؽڵ����ͣ���ֵ��
{
	KeyType Key;
	EleType Val;
};

typedef struct _HashBucket_
{
	_ElementNode_ Data[BUCKET_SIZE];
	struct _HashBucket_ *Bucket;		// �����ͻ�ķ�ʽ������ַ��
}HashBucket;	// Ͱ�ڵ�����

typedef HashBucket* HashTable;

bool HashTableInit(HashTable *Hash);					// ��ʼ����ϣ��
bool HashTableInsert(HashTable Hash, KeyType Key, EleType Data);	// �����ֵ��
EleType* HashTableFind(HashTable Hash, KeyType Key);	// ���ݼ�����ֵ
bool HashTableDelete(HashTable Hash, KeyType Key);		// ɾ����ֵ��
void HashTablePrint(HashTable Hash);					// ��ӡ��ϣ��
void HashTableDestroy(HashTable *Hash);					// ���ٹ�ϣ��

#endif // _HASHTABLE_H_