
#include "bubbleSort.h"

// ���͵ľ�̬�Ͷ�̬�������������Ͱ󶨵�ʵ�ʣ�������еı����ͱ��ʽ������
// �ڱ���ʱ�͹̶��ˣ����֮Ϊ��̬�󶨣�������еı����ͱ��ʽ������ֱ������ʱ
// ��֪�������֮Ϊ��̬��

void byte_swap(void *pData1, void *pData2, size_t stSize)
{
	unsigned char *pcData1 = (unsigned char *)pData1;
	unsigned char *pcData2 = (unsigned char *)pData2;
	unsigned char ucTemp;
	while(stSize--)
	{
		ucTemp = *pcData1;
		*pcData1 = *pcData2;
		*pcData2 = ucTemp;
		pcData1++;
		pcData2++;
	}
}

// base��ʾ������ʼ��ַ��nmemb��ʾ����Ԫ�ظ�����size��ʾ����Ԫ�ش�С
// compare�ص�����
void bubbleSort(void *base, size_t nmemb, size_t size, COMPARE compare)
{
	int hasSwap = 1;
	for(size_t i = 1; hasSwap && i < nmemb; i++)
	{
		hasSwap = 0;
		for(size_t j = 0; j < nmemb - i; j++)
		{
			void *pThis = ((unsigned char *)base) + size * j;
			void *pNext = ((unsigned char *)base) + size * (j + 1);
			if(compare(pThis, pNext) > 0)
			{
				hasSwap = 1;
				byte_swap(pThis, pNext, size);
			}
		}
	}
}