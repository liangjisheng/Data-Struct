
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

unsigned char *g_bitmap = NULL;
int g_size = 0;
int g_base = 0;


/**
 * ��ʼ��bitmap
 * nSize:bitmap�Ĵ�С����bitλ�ĸ���
 * start:��ʼֵ
 * ����ֵ: -1��ʾʧ�ܣ�0��ʾ�ɹ�
*/
int bitmap_init(int nSize, int start)
{
	g_bitmap = (unsigned char *)malloc((nSize / 8 + 1) * sizeof(unsigned char));
	if (NULL == g_bitmap)
		return -1;

	g_base = start;
	g_size = nSize / 8 + 1;
	memset(g_bitmap, 0, g_size);
	return 0;
}

/**
 * ��index��Ӧ��λ��Ϊ1
 * index:Ҫ���õ�ֵ
 * ����ֵ: -1��ʾʧ�ܣ�0��ʾ�ɹ�
*/
int bitmap_set(int index)
{
	int quo = (index - g_base) / 8;
	int remainder = (index - g_base) % 8;
	unsigned char x = (0x1 << remainder);

	if (quo > g_size)
		return -1;
	g_bitmap[quo] |= x;
	return 0;
}

/**
 * ��ȡbitmap��iλ��ֵ
 * ����ֵ��-1��ʾʧ�ܣ����򷵻ض�Ӧλ��ֵ
*/
int bitmap_get(int i)
{
	int quo = i / 8;
	int remainder = i % 8;
	unsigned char x = 0x1 << remainder;
	unsigned char res;
	if (quo > g_size)
		return -1;
	res = g_bitmap[quo] & x;
	return res > 0 ? 1 : 0;
}

/**
 * ����indexλ��Ӧ��ֵ
*/
int bitmap_data(int index) { return index + g_base; }

void bitmap_free() { free(g_bitmap); }
