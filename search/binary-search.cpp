#include"stdio.h"

#define max 20
int data[max] = { 12, 16, 19, 22, 25, 32, 39, 48, 55, 57,
				  	  58, 63, 68, 69, 70, 78, 84, 88, 90, 97 };

int count = 0;	// 查找次数

int b_search(int left, int right, int key)
{
	int mid = (left + right) / 2;
	count++;
	if(left > right) {
		return -1;
	}
	else {
		if (key < data[mid])
			return b_search(left, mid-1, key);
		else if(key > data[mid])
			return b_search(mid + 1, right, key);
		else if(key == data[mid]) {
			printf("data[%d]=%d\n", mid, key);
			return mid;
		}
	}

	return -1;
}

int main()
{
	int index = b_search(0, max-1, 25);
	if (-1 != index) {
		printf("index: %d\n", index);
		printf("search time: %d\n", count);
	}		
	else {
		printf("no found!!\n");
	}

	return 0;
}
