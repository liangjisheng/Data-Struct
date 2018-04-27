
#include <stdio.h>
#include "avltree.h"

static int arr[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9, 9};
#define TBL_SIZE(a) ((sizeof(a)) / (sizeof(a[0])))

void main()
{
	int i, len;
	AVLTree root = NULL;

	printf("== �߶�: %d\n", avltree_height(root));
	printf("== �������: ");
	len = TBL_SIZE(arr);
	for(i = 0; i < len; i++)
	{
		printf("%d ", arr[i]);
		root = avltree_insert(root, arr[i]);
	}

	printf("\n== ǰ�����:");
	preorder_avltree(root);

	printf("\n== �������:");
	inorder_avltree(root);

	printf("\n== �������:");
	postorder_avltree(root);

	printf("\n\n");
	printf("== �߶�: %d\n", avltree_height(root));
	printf("== ��Сֵ: %d\n", avltree_minimum(root)->key);
	printf("== ���ֵ: %d\n", avltree_maximum(root)->key);
	printf("������ϸ��Ϣ:\n");
	print_avltree(root, root->key, 0);

	i = 8;
	printf("\nɾ���ڵ㣺 %d", i);
	root = avltree_delete(root, i);

	printf("\n== �߶�: %d\n", avltree_height(root));
	printf("== �������: ");
	inorder_avltree(root);
	printf("\n������ϸ��Ϣ: \n");
	print_avltree(root, root->key, 0);

	destroy_avltree(root);
	getchar();
}