
/**
  * C 语言: 数组实现的队列，只能存储int数据。
  *
  * @author liangjisheng
  * @date 2017/10/09
*/

#include <stdio.h>
#include <malloc.h>

static int *arr = NULL;
static int count;

// 创建队列
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

// 销毁队列
int destroy_array_queue()
{
	if(arr)
	{
		delete [] arr;
		arr = NULL;
	}

	return 0;
}

// 将val添加到队列的末尾
void add(int val) { arr[count++] = val; }

// 返回队列开头元素
int front() { return arr[0]; }

// 返回并删除队列开头元素
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