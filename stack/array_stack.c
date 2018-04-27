
/* C语言实现栈,并且只能存储int数据
 * 
 *
 * @author liangjisheng
 * @date 2017/10/09
*/

#include <stdio.h>
#include <malloc.h>

static int *arr = NULL;
static int count;

// 创建栈,默认大小是12
int create_array_stack(int sz = 12)
{
	arr = (int *)malloc(sz * sizeof(int));
	if(!arr)
	{
		printf("arr malloc error!");
		return -1;
	}

	return 0;
}

// 销毁栈
int destroy_array_stack()
{
	if(arr)
	{
		free(arr);
		arr = NULL;
	}

	return 0;
}

void push(int val) { arr[count++] = val; }

int peek() { return arr[count - 1]; }

int pop() { return arr[--count]; }

int size() { return count; }

int is_empty() { return size() == 0; }

void print_array_stack()
{
	if(is_empty())
	{
		printf("stack is empty\n");
		return ;
	}

	printf("stack size() = %d\n", size());
	int i = size() - 1;
	while(i >= 0)
		printf("%d\n", arr[i--]);
}


int main()
{
	int tmp = 0;
	create_array_stack(12);

	push(10);
	push(20);
	push(30);

	print_array_stack();
	printf("\n");

	tmp = pop();
	printf("tmp = %d\n", tmp);
	print_array_stack();
	printf("\n");

	tmp = peek();
	printf("tmp = %d\n", tmp);
	print_array_stack();
	printf("\n");

	push(40);
	print_array_stack();
	printf("\n");

	destroy_array_stack();

	getchar();
	return 0;
}