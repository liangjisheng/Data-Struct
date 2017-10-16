
/**
 * C ����: ��������ʵ�ֵ�ջ��ֻ�ܴ洢int���ݡ�
 *
 * @author liangjisheng
 * @date 2017/10/09
*/

#include <stdio.h>
#include <malloc.h>

struct node
{
	int val;
	struct node* next;
};

static struct node *phead = NULL;

// �����ڵ�,valΪ�ڵ�ֵ
static struct node* create_node(int val) 
{
	struct node *pnode=NULL;
	pnode = (struct node*)malloc(sizeof(struct node));
	if (!pnode)
		return NULL;
	pnode->val = val;
	pnode->next = NULL;
	
	return pnode;
}

// ���ٵ�����
static int destroy_single_link()
{
	struct node *pnode = NULL;

	while(phead != NULL)
	{
		pnode = phead;
		phead = phead->next;
		free(pnode);
	}

	return 0;
}

// ��val���뵽����ı�ͷλ��
static struct node* push(int val)
{
	struct node *pnode = NULL;
	pnode = create_node(val);
	pnode->next = phead;
	phead = pnode;

	return phead;
}

// ɾ������ı�ͷ
static int pop()
{
	if(!phead)
	{
		printf("remove failed! link is empty!");
		return -1;
	}

	int ret;
	struct node *pnode;
	ret = phead->val;
	pnode = phead;
	phead = phead->next;
	free(pnode);

	return ret;
}

// ��������ı�ͷ�ڵ��ֵ
static int peek()
{
	if(!phead)
	{
		printf("peek failed! link is empty!");
		return -1;
	}

	return phead->val;
}

static int size()
{
	int count = 0;
	struct node *pnode = phead;

	while(pnode != NULL)
	{
		pnode = pnode->next;
		count++;
	}

	return count;
}

static int is_empty() { return phead == NULL; }

static void print_single_link()
{
	if(is_empty())
	{
		printf("stack is empty\n");
		return ;
	}

	printf("stack size() = %d\n", size());
	struct node *pnode = phead;

	while(pnode != NULL)
	{
		printf("%d\n", pnode->val);
		pnode = pnode->next;
	}
}


int main()
{
	int tmp = 0;

	push(10);
	push(20);
	push(30);

	print_single_link();
	printf("\n");

	tmp = pop();
	printf("tmp = %d\n", tmp);

	tmp = peek();
	printf("tmp = %d\n", tmp);
	printf("\n");

	push(40);
	print_single_link();
	printf("\n");

	getchar();
	return 0;
}

