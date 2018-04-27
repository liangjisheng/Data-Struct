
#include <stdio.h>
#include "bitmap.h"

void main()
{
	int a[] = { 5,8,7,6,3,1,10,78,56,34,23,12,43,54,65,76,87,98,89,100 };
	int i = 0;
	int ilen = sizeof(a) / sizeof(a[0]);
	int nBitlen = ((100 / 8) + 1) * 8;
	bitmap_init(100, 0);

	for (i = 0; i < ilen; ++i)
		bitmap_set(a[i]);
	for (i = 0; i < nBitlen; ++i)
	{
		if (bitmap_get(i) > 0)
			printf("%d ", bitmap_data(i));
	}
	printf("\n");
	bitmap_free();

	getchar();
}