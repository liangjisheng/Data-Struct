#include"stdio.h"
#include"stdlib.h"
#include"time.h"

#define size 15

void quicksort(int *list, int left, int right) {
	int l = left, r = right, t = 0;
	while (l < r) {
		while (list[l] < list[(left + right) / 2]) {
			l++;
		}
		while (list[r] > list[(left + right) / 2]) {
			r--;
		}
		if (l <= r) {
			t = list[l];
			list[l] = list[r];
			list[r] = t;
			l++;
			r--;
		}
	}

	if (left < r) {
		quicksort(list, left, r);
	}
	if (l < right) {
		quicksort(list, l, right);
	}
}

int binarysearch(int *list, int n, int data)
{
	int low = 0, high = n - 1, mid = 0;
	while (low <= high)	{
		mid = (low + high) / 2;
		if (list[mid] == data) {
			return mid;
		}
		else if (list[mid] > data) {
			high=mid-1;
		}
		else {
			low=mid+1;
		}
	}
	
	return -1;
}

void main()
{
	int list[size],i;
	srand(time(0));
	for(i=0;i<size;i++)
		list[i]=rand()%100+10;
	printf("source list:");
	for(i=0;i<size;i++)
		printf("[%d]",list[i]);
	printf("\n\n");
	printf("sorting result:");
	quicksort(list,0,size-1);
	for(i=0;i<size;i++)
		printf("[%d]",list[i]);
	printf("\n");
	int key,f;
	printf("Please input the key you find:");
	scanf("%d",&key);
	f=binarysearch(list,size,key);
	if(f<0)printf("No found the key!\n");
	else printf("find the key:list[%d]=%d\n",f,key);
}