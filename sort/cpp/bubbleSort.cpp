
#include "bubbleSort.h"

// 类型的静态和动态绑定是名字与类型绑定的实际，如果所有的变量和表达式的类型
// 在编译时就固定了，则称之为静态绑定，如果所有的变量和表达式的类型直到运行时
// 才知道，则称之为动态绑定

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

// base表示数组起始地址，nmemb表示数组元素个数，size表示数组元素大小
// compare回调函数
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