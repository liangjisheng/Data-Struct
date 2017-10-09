
#include <stdio.h>
#include "double_link.h"

/**
 * C����ʵ��˫������Ĳ��Գ���
 * (01) int_test()
 *		��ʾ˫���������int����
 * (02) string_test()
 *		��ʾ��˫������������ַ������ݡ�
 * (03) object_test()
 *		��ʾ��˫���������������
 *
 * @author Liangjisheng
 * @date 2017/10/08
 */

void int_test()
{
	int iarr[4] = {10, 20, 30, 40};
	printf("\n----%s----\n", __FUNCTION__);
	create_dlink();

	dlink_insert(0, &iarr[0]);		// ��˫�������ͷ��������
	dlink_insert(0, &iarr[1]);
	dlink_insert(0, &iarr[2]);

	printf("dlink_is_empty() = %d\n", dlink_is_empty());
	printf("dlink_size() = %d\n", dlink_size());

	// ��ӡ˫�������е�ȫ������
	int i;
	int *p;
	int sz = dlink_size();
	for(i = 0; i < sz; i++)
	{
		p = (int *)dlink_get(i);
		printf("dlink_get(%d) = %d\n", i, *p);
	}

	destroy_dlink();
}

void string_test()
{
	char* sarr[4] = { "ten", "twenty", "thirty", "forty" };
	printf("\n----%s----\n", __FUNCTION__);
	create_dlink();

	dlink_insert(0, sarr[0]);
	dlink_insert(0, sarr[1]);
	dlink_insert(0, sarr[2]);

	printf("dlink_is_empty() = %d\n", dlink_is_empty());
	printf("dlink_size() = %d\n", dlink_size());

	int i;
	char *p;
	int sz = dlink_size();
	for(i = 0; i < sz; i++)
	{
		p = (char *)dlink_get(i);
		printf("dlink_get(%d) = %s\n", i, p);
	}

	destroy_dlink();
}


typedef struct tag_stu
{
	int id;
	char name[20];
}stu;

static stu arr_stu[] = 
{
	{10, "sky"},
	{20, "earth"},
	{30, "voice"},
	{40, "dance"}
};

#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

void object_test()
{
	printf("\n----%s----\n", __FUNCTION__);
	create_dlink();

	dlink_insert(0, &arr_stu[0]);
	dlink_insert(0, &arr_stu[1]);
	dlink_insert(0, &arr_stu[2]);

	printf("dlink_is_empty() = %d\n", dlink_is_empty());
	printf("dlink_size() = %d\n", dlink_size());

	int i;
	int sz = dlink_size();
	stu *p;
	for(i = 0; i < sz; i++)
	{
		p = (stu *)dlink_get(i);
		printf("dlink_get(%d) = [%d, %s]\n", i, p->id, p->name);
	}

	destroy_dlink();
}


int main()
{
	int_test();
	string_test();
	object_test();

	getchar();
	return 0;
}