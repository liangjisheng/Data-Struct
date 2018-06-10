#include"stdio.h"
#define max 6
#define hashmax 5
int data[max]={12,160,219,522,725,9997};
int hashtab[hashmax];
int counter=1;
//hash函数之余数法
int hash_mod(int key)
{return key%hashmax;}
//collision解决之差值法
int collision_offset(int address)
{
	int offset=3;    //设置差值为3
	return (address+offset)%hashmax;
}
//建立hash表
int create_hash(int key)
{
	int hashtime,collisiontime,address,i;
	hashtime=0;collisiontime=0;
	address=hash_mod(key);
	while(hashtime<hashmax)
	{
		if(hashtab[address]==0)
		{
			hashtab[address]=key;
			printf("Key:%d=>address:%d\n",key,address);
			for(i=0;i<hashmax;i++)
				printf("[%d]",hashtab[i]);
			printf("\n");
			return 1;
		}
		else 
		{
			collisiontime++;
			printf("collision:%d=>address:%d\n",collisiontime,address);
			address=collision_offset(address);
		}
		hashtime++;
	}
	return 0;
}
//hash查找
int hash_search(int key)
{
	int address;
	counter=0;
	address=hash_mod(key);
	while(counter<hashmax)
	{
		counter++;
		if(hashtab[address]==key)return 1;
		else address=collision_offset(address);
	}
	return 0;
}
//主程序
void main()
{
	int keyvalue,index=0,i;
	printf("output the data:\n");
	for(i=0;i<max;i++)
		printf("[%d]",data[i]);
	printf("\n"),printf("\n");
	for(i=0;i<hashmax;i++)
		hashtab[i]=0;
	while(index<max)
	{
		if(create_hash(data[index]))
			printf("Hash Success!\n"),printf("\n");
		else printf("Hash Failed!\n"),printf("\n");
		index++;
	}
	printf("The final hashtab.\n");
	for(i=0;i<hashmax;i++)
		printf("[%d]",hashtab[i]);
	printf("\n");
	while(keyvalue!=-1)
	{
		printf("Please input your key value(exit for -1):");
		scanf("%d",&keyvalue);
		if(hash_search(keyvalue))
			printf("Searchtiem=%d\n",counter);
		else printf("No found!\n");
	}
}