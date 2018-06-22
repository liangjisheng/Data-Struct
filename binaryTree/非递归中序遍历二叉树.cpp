// 非递归中序遍历二叉树
void inorder(pNode root)
{
	int i=0;
	pNode p,s[num];
	p=root;
	do {
		while(p!=NULL) {
			s[i++]=p;
			p=p->left;
		}
		if(i>0) {
			p=s[--i];
			printf("%d\t",p->data);
			p=p->right;
		}
	}while(i>0 || p!=NULL);
}