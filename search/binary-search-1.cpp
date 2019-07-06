#include"stdio.h"

int count = 0;

int b_search(int array[], int len, int key)
{
	int left = 0, right = len - 1, mid = 0;
	while (left <= right) {
		mid = (left + right) / 2;
		if (key > array[mid]) {
			left = mid + 1;
		}
		else if (key < array[mid]) {
			right = mid - 1;
		}
		else {
			printf("array[%d]=%d\n", mid, key);
			return mid;
		}
		count++;
	}
	return -1;
}

int main()
{
	int data[] = { 12, 16, 19, 22, 25, 32, 39, 48, 55, 57,
				  	  58, 63, 68, 69, 70, 78, 84, 88, 90, 97 };
	int key = 25;
	int len = sizeof(data) / sizeof(int);
	int index = b_search(data, len, key);
	if (-1 != index) {
		printf("search time=%d\n",count);
	}		
	else {
		printf("no found!!\n");
	}

	return 0;
}
