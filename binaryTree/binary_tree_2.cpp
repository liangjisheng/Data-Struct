#include"iostream"
using namespace std;

struct BT {
	char data;
	struct BT * left;
	struct BT * right;
};
typedef struct BT Node;
typedef struct BT* pNode;

pNode create_bt_pre(pNode root);
void print_bt_pre(pNode root);
void print_bt_mid(pNode root);
void print_bt_post(pNode root);
void leaf_count(pNode root,int* count);
void tree_depth(pNode root,int* l,int* h);

int main()
{
	pNode root;
	cout<<"input the data to create binary tree:"<<endl;
	root=create_bt_pre(root);

	// pre_print
	cout<<"前序遍历二叉树:";
	if(root!=NULL)
		print_bt_pre(root);
	cout<<endl;

	// mid_print
	// cout<<"中序遍历二叉树:";
	// if(root!=NULL)
	//	print_bt_mid(root);
	// cout<<endl;

	// post_print
	// cout<<"后序遍历二叉树:";
	// if(root!=NULL)
	//	print_bt_post(root);
	// cout<<endl;

	// 叶子节点个数
	int count=0;
	leaf_count(root,&count);
	cout<<"leaf node is:"<<count<<endl;

	// 二叉树的深度
	int level=0,high=0;
	tree_depth(root,&level,&high);
	cout<<"depth is:"<<high<<endl;

	system("pause");
	return 0;
}

pNode create_bt_pre(pNode root)
{
	char ch;
	scanf("%c",&ch);
	// getchar();
	if(ch==' ') root=NULL;
	else {
		root=new Node;
		root->data=ch;
		root->left=create_bt_pre(root->left);
		root->right=create_bt_pre(root->right);
	}
	return root;
}

void print_bt_pre(pNode root)
{
	if(root==NULL) return ;
	else {
		cout<<root->data<<' ';
		print_bt_pre(root->left);
		print_bt_pre(root->right);
	}
}

void print_bt_mid(pNode root)
{
	if(root==NULL) return ;
	else {
		print_bt_pre(root->left);
		cout<<root->data<<' ';
		print_bt_pre(root->right);
	}
}

void print_bt_post(pNode root)
{
	if(root==NULL) return ;
	else {
		print_bt_pre(root->left);
		print_bt_pre(root->right);
		cout<<root->data<<' ';
	}
}

void leaf_count(pNode root,int* count)
{
	if(root==NULL) return;
	else {
		if(root->left==NULL && root->right==NULL) 
		{ (*count)++; return; }
		leaf_count(root->left,count);
		leaf_count(root->right,count);
	}
}

void tree_depth(pNode root,int* l,int* h)
{
	int l1=0,l2=0,h1=0,h2=0;
	if(root==NULL) return;
	else {
		(*l)++;
		if(*l>*h) *h=*l;
		tree_depth(root->left,&l1,&h1);
		tree_depth(root->right,&l2,&h2);
		if(h1>h2) *h=*h+h1;
		else *h=*h+h2;
	}
}