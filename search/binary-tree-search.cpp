#include"stdio.h"
#include"stdlib.h"
#define max 10
int data[max]={15,2,13,6,17,
25,37,7,3,18};
int counter;
struct tree
{
	int key;
	struct tree *left;
	struct tree *right;
};
typedef struct tree treenode;
typedef treenode *bitree;
bitree root=NULL;
//create_bitree
void create_bitree(int *data)
{
	bitree newnode,current,father;
	int i;
	for(i=0;i<max;i++)
	{
		newnode=(bitree)malloc(sizeof(treenode));
		newnode->key=data[i];
		newnode->left=NULL;newnode->right=NULL;
		if(root==NULL)root=newnode;
		else 
		{
			current=root;
			while(current!=NULL)
			{
				father=current;
				if(current->key>data[i])current=current->left;
				else current=current->right;
			}
			if(father->key>data[i])father->left=newnode;
			else father->right=newnode;
		}
	}
}
//二叉查找
int bitree_search(int key)
{
	bitree po=root;
	counter=0;
	while(po!=NULL)
	{
		counter++;
		if(po->key>key)po=po->left;
		else if(po->key==key)return 1;
		else po=po->right;
	}
	return 0;
}
//主程序
void main()
{
	int keyvalue,i;
	printf("output the data:\n");
	for(i=0;i<max;i++)
		printf("[%d]",data[i]);
	printf("\n");
	create_bitree(data);
	while(keyvalue!=-1)
	{
		printf("Please input the keyvalue:");
		scanf("%d",&keyvalue);
		if(bitree_search(keyvalue))printf("Search time=%d\n",counter);
		else printf("No found!\n");
	}
}