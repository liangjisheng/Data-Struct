
#include <stdio.h>
#include "bstree.h"

static int arr[] = {1, 5, 4, 3, 2, 6};
#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

void main()
{
	int i, ilen;
	BSTree root = NULL;

	printf("== 依次添加:");
	ilen = TBL_SIZE(arr);
	for(i = 0; i < ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(root, arr[i]);
	}

	printf("\n== 前序遍历:");
	preorder_bstree(root);

	printf("\n== 中序遍历:");
	inorder_bstree(root);

	printf("\n== 后序遍历:");
	postorder_bstree(root);
	printf("\n");

	printf("== 最小值: %d\n", bstree_minimum(root)->key);
	printf("== 最大值: %d\n", bstree_maximum(root)->key);
	printf("== 树的详细信息:\n");
	bstree_print(root, root->key, 0);

	for(int i = 0; i < ilen; i++)
	{
		printf("\n== 删除节点: %d", arr[i]);
		root = bstree_delete_1(root, arr[i]);

		printf("\n== 中序遍历:");
		inorder_bstree(root);
		printf("\n");
	}

	printf("\n");
	for(i = 0; i < ilen; i++)
	{
		printf("%d ", arr[i]);
		root = bstree_insert(root, arr[i]);
	}

	printf("\n== 前序遍历:");
	preorder_bstree(root);

	printf("\n== 中序遍历:");
	inorder_bstree(root);

	printf("\n== 后序遍历:");
	postorder_bstree(root);
	printf("\n");

	for(int i = 0; i < ilen; i++)
	{
		printf("\n== 删除节点: %d", arr[i]);
		root = bstree_delete_2(root, arr[i]);

		printf("\n== 中序遍历:");
		inorder_bstree(root);
		printf("\n");
	}

	getchar();
}