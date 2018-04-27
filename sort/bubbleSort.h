
#ifndef _BUBBLESORT_H_
#define _BUBBLESORT_H_

#include <stddef.h>

typedef int (*COMPARE)(const void * e1, const void * e2);
void bubbleSort(void *base, size_t nmemb, size_t size, COMPARE compare);

#endif // _BUBBLESORT_H_