
#include "bitree.h"

int main()
{
	int ret;
	int *int_ptr;
	BiTree tree1, tree2, tree_merge;
	DoubleLink<void *>* pdlink = new DoubleLink<void *>();
	BiTreeNode *pnode;

	/* tree1 as follows:
			1
		  /   \
		 2	   5
	   /   \  /  \
	  3	   4 6    7
	*/
	create_tree(&tree1, NULL);		// input "123#4#56#7#"
	getchar();
	printf("\nstep:tree1 build success\n");

	/* tree2 as follows:
				0
			  /   \
			 8	   9
			/ \	  / \
		   6   7 3
	*/
	int_ptr = NULL;
	create_tree(&tree2, NULL);	// input "086#7#93###"
	printf("step2: tree2 build success\n");

	int_ptr = (int *)malloc(sizeof(int));
	if(!int_ptr)
		return -1;
	*int_ptr = 11;

	/* after merged as follow( by tree1 and tree2 ) : 
                                11 
                          /             \ 
                         1               0 
                     /       \         /    \ 
                    2         5       8      9 
                 /    \    /    \   /   \   /  \ 
                3      4  6      9 6     7 3    NULL 
    */  
	ret = bitree_merge(&tree_merge, &tree1, &tree2, int_ptr);
	printf("step3: after merged: there are %d number nodes in the tree_merge\n",
		bitree_size(&tree_merge));

	/* after remove the right tree: 
                   11  
                 /   \ 
                1     NULL 
              /   \ 
             2     5 
            / \   / \ 
           3  4  6   7 
     */   
	printf("\nstep4: remove the right tree in tree_merge.\n");
	bitree_rem_right(&tree_merge, bitree_root(&tree_merge));
	printf("after remove the right tree, there are %d number nodes in the tree_merge\n",
		bitree_size(&tree_merge));

	printf("'\nstep5: preorder traverse the tree and insert the nodes into the list\n");
	ret = preorder(bitree_root(&tree_merge), pdlink);
	printf("according to the sequence of the preorder traversing the tree:\n");
	// for(void* iter = pdlink->get_first(); iter != pdlink->get_last(); iter++)
		// printf("%d ", *(int *)iter);
	for(int i = 0; i < pdlink->size(); i++)
		printf("%d ", *(int *)pdlink->get(i));
	printf("\n");
	for(int i = 0; i < pdlink->size();)
		pdlink->del(i);
	int nsize = pdlink->size();

	printf("\nsetp6: inorder traverse the tree and insert the nodes into the list\n");
	ret = inorder(bitree_root(&tree_merge), pdlink);
	printf("according to the sequence of the inorder traversing the tree:\n");
	for(int i = 0; i < pdlink->size(); i++)
		printf("%d ", *(int *)pdlink->get(i));
	printf("\n");
	// for(int i = 0; i < pdlink->size();)
		// pdlink->del(i);
	while(pdlink->size())
		pdlink->del(0);

	printf("\nsetp7: postorder traverse the tree and insert the nodes into the list\n");
	ret = postorder(bitree_root(&tree_merge), pdlink);
	printf("according to the sequence of the postorder traversing the tree:\n");
	for(int i = 0; i < pdlink->size(); i++)
		printf("%d ", *(int *)pdlink->get(i));
	printf("\n");
	while(pdlink->size())
		pdlink->del(0);

	printf("\nstep8: delete all the nodes in the tree.\n");  
	bitree_rem_left( &tree_merge, NULL );  
	printf("there are %d number nodes.\n", bitree_size(&tree_merge) );

	bitree_destroy(&tree_merge);

	getchar();
	getchar();
	getchar();
	return 0;
}