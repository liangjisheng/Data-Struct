#include"stdio.h"
#define max 20
int data[max]={12,16,19,22,25,
32,39,48,55,57,
58,63,68,69,70,
78,84,88,90,97};
int count=1;
//²å²¹²éÕÒ
int interpolation_search(int key)
{
	int low=0,high=max-1,middle;
	middle=low+(key-data[low])*(high-low)/(data[high]-data[low]);
	if(middle<low)middle=low;
	if(middle>high)middle=high;
	while(low<high)
	{
		if(key<data[middle])high=middle-1;
		else if(key>data[middle])low=middle+1;
		else if(key==data[middle])
		{printf("data[%d]=%d\n",middle,key);return 1;}
		if(low<high)middle=low+(key-data[low])*(high-low)/(data[high]-data[low]);
		if(middle<low)middle=low;
	    if(middle>high)middle=high;
		count++;
	}
	return 0;
}
//Ö÷³ÌÐò
int main()
{
	int key;
	printf("Please input the key:");
	scanf("%d",&key);
	if(interpolation_search(key))
		printf("search time=%d\n",count);
	else printf("no found!!\n");
	return 0;
}