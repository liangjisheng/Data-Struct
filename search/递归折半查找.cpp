#include"stdio.h"
#define max 20
int data[max]={12,16,19,22,25,
32,39,48,55,57,
58,63,68,69,70,
78,84,88,90,97};
int count=1;
//递归求费式级数
int fib(int n)
{
	if(n<=1)return n;
	else return fib(n-1)+fib(n-2);
}
//费式查找法
int fibonacci_search(int n,int key)
{
	int root,distance_1,distance_2,temp;
	root=fib(n-1);
	distance_1=fib(n-2);
	distance_2=fib(n-3);
	do
	{
		if(key<data[root-1])
		{
			root=root-distance_2;
			temp=distance_1;
			distance_1=distance_2;
			distance_2=temp-distance_2;
		}
		else if(key>data[root-1])
		{
			root=root+distance_2;
			distance_1=distance_1-distance_2;
			distance_2=distance_2-distance_1;
		}
		else if(key==data[root-1])
		{printf("data[%d]=%d\n",root-1,key);return 1;}
		count++;
	}while(distance_2>=0);
	return 0;
}
//主程序
void main()
{
	int key,fina;
	printf("Please input the key:");
	scanf("%d",&key);
	fina=1;
	while(fib(fina)<=max)
		fina++;
	if(fibonacci_search(fina,key))
		printf("search time=%d\n",count);
	else printf("no found!!\n");
}