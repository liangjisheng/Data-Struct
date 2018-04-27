
/**
  * C ����: ����ʵ�ֵĶ��У�ֻ�ܴ洢int���ݡ�
  *
  * @author liangjisheng
  * @date 2017/10/09
*/

#include <stdio.h>
#include <malloc.h>

static int *arr = NULL;
static int count;

// ��������
int create_array_queue(int sz)
{
	arr = (int *)malloc(sz * sizeof(int));
	if(!arr)
	{
		printf("arr malloc error!");
		return -1;
	}
	count = 0;

	return 0;
}

// ���ٶ���
int destroy_array_queue()
{
	if(arr)
	{
		delete [] arr;
		arr = NULL;
	}

	return 0;
}

// ��val��ӵ����е�ĩβ
void add(int val) { arr[count++] = val; }

// ���ض��п�ͷԪ��
int front() { return arr[0]; }

// ���ز�ɾ�����п�ͷԪ��
int pop()
{
	int i = 0;
	int ret = arr[0];

	count--;
	while(i++ < count)
		arr[i - 1] = arr[i];

	return ret;
}

int size() { return count; }

int is_empty() { return count == 0; }


int main()
{
	int tmp = 0;
	create_array_queue(12);

	add(10);
	add(20);
	add(30);

	tmp = pop();
	printf("tmp = %d\n", tmp);

	tmp = front();
	printf("tmp = %d\n", tmp);

	add(40);

	printf("is_empty() = %d\n", is_empty());
	printf("size() = %d\n", size());

	while(!is_empty())
		printf("%d\n", pop());

	destroy_array_queue();

	getchar();
	return 0;
}