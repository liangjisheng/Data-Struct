#include"stdio.h"
#include"math.h"
#define max 20
int data[max]={12,160,219,522,725,
732,739,748,755,757,
958,963,1068,1169,1570,
2278,5384,8888,9000,9997};
int count=1;
//找出加强型插补查找的中间值
int findrobust(int low,int high,int key)
{
	int gap,num1,num2,num3;
	gap=ceil(sqrt((float)high-(float)low+1.0));
	num1=low+gap;
	num2=high-gap;
	num3=low+(key-data[low]*(high-low))/(data[high]-data[low]);
	if(num1>=num2)
	{if(num2>=num3)return num2;    //num1>=num2>=num3
		else if(num1>num3)return num3;//num1>=num3>=num2
		else return num1;}             //num3>=num1>=num2
	else if(num2>=num1)
	{if(num1>=num3)return num1;        //num2>=num1>=num3
	else if(num2>=num3)return num3;    //num2>=num3>=num1
	else return num2;}                  //num3>=num2>=num1
	return 0;
}
//插补查找
int interpolation_search(int key)
{
	int low=0,high=max-1,middle;
	middle=findrobust(low,high,key);
	if(middle<low)middle=low;
	if(middle>high)middle=high;
	while(low<high)
	{
		if(key>data[middle])low=middle+1;
		if(key<data[middle])high=middle-1;
		else if(key==data[middle])
		{printf("data[%d]=%d\n",middle,key);return 1;}
		if(low<high)middle=findrobust(low,high,key);
		if(middle<low)middle=low;
		if(middle>high)middle=high;
		count++;
	}
	return 0;
}
//主程序
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