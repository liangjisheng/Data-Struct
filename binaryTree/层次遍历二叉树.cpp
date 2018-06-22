// ²ã´Î±éÀú¶þ²æÊ÷
void LevelOrder(pNode root)
{
	pNode p;
	pNode q[QueSize];
	int front=0,rear=0;
	if(root!=NULL) {
		rear=(rear+1)%QueSize;
		q[rear]=root;
	}
	while(front!=rear) {
		front=(front+1)%QueSize;
		p=q[front];
		printf("%c ",p->data);

		if(p->left!=NULL) {
			rear=(rear+1)%QueSize;
			q[rear]=p->left;
		}
		if(p->right!=NULL) {
			rear=(rear+1)%QueSize;
			q[rear]=p->right;
		}
	}
}