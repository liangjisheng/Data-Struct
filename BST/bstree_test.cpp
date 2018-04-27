
#include <stdio.h>
#include "bstree.h"

static int arr[] = {1, 5, 4, 3, 2, 6};
#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

void main()
{
	int i, ilen;
	BSTree root = NULL;

	printf("== �������:");
	ilen = TBL_SIZE(arr);
	for(i = 0; i < ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(root, arr[i]);
	}

	printf("\n== ǰ�����:");
	preorder_bstree(root);

	printf("\n== �������:");
	inorder_bstree(root);

	printf("\n== �������:");
	postorder_bstree(root);
	printf("\n");

	printf("== ��Сֵ: %d\n", bstree_minimum(root)->key);
	printf("== ���ֵ: %d\n", bstree_maximum(root)->key);
	printf("== ������ϸ��Ϣ:\n");
	bstree_print(root, root->key, 0);

	for(int i = 0; i < ilen; i++)
	{
		printf("\n== ɾ���ڵ�: %d", arr[i]);
		root = bstree_delete_1(root, arr[i]);

		printf("\n== �������:");
		inorder_bstree(root);
		printf("\n");
	}

	printf("\n");
	for(i = 0; i < ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(root, arr[i]);
	}

	printf("\n== ǰ�����:");
	preorder_bstree(root);

	printf("\n== �������:");
	inorder_bstree(root);

	printf("\n== �������:");
	postorder_bstree(root);
	printf("\n");

	for(int i = 0; i < ilen; i++)
	{
		printf("\n== ɾ���ڵ�: %d", arr[i]);
		root = bstree_delete_2(root, arr[i]);

		printf("\n== �������:");
		inorder_bstree(root);
		printf("\n");
	}

	getchar();
}