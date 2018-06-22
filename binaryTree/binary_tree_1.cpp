#include"iostream"
using namespace std;

struct BTNode {
	char data;
	BTNode * left;
	BTNode * right;
};

typedef BTNode* pBTNode;

pBTNode Create_BTree_Pre();
void PreOrder(pBTNode root);
void MidOrder(pBTNode root);
void PostOrder(pBTNode root);
int BTreeCount(pBTNode root);
int BTreeDepth(pBTNode root);
pBTNode FindBTree(pBTNode root,char item);
void ClearBTree(pBTNode root);

int main() 
{
	pBTNode root=0;
	cout<<"input data to Create binary tree:"<<endl;
	// input data: abc##de#g##f###
	root=Create_BTree_Pre();

	cout<<"PreOrder  the tree:";
	PreOrder(root);
	cout<<endl;

	cout<<"MidOrder  the tree:";
	MidOrder(root);
	cout<<endl;

	cout<<"PostOrder the tree:";
	PostOrder(root);
	cout<<endl;

	int count=BTreeCount(root);
	cout<<"Node count:"<<count<<endl;

	int depth=BTreeDepth(root);
	cout<<"Tree Depth:"<<depth<<endl;

	pBTNode p=FindBTree(root,'d');
	cout<<"Find data:"<<p->data<<endl;

	ClearBTree(root);

	system("pause");
	return 0;
}

pBTNode Create_BTree_Pre()
{
	char item;
	pBTNode root;
	cin>>item;
	if(item=='#') 
	{ root=NULL; return root; }
	else {
		root=new BTNode;
		root->data=item;
		root->left=Create_BTree_Pre();
		root->right=Create_BTree_Pre();
		return root;
	}
}

void PreOrder(pBTNode root)
{
	if(root!=NULL) {
		cout<<root->data<<' ';
		PreOrder(root->left);
		PreOrder(root->right);
	}
}

void MidOrder(pBTNode root)
{
	if(root!=NULL) {
		MidOrder(root->left);
		cout<<root->data<<' ';
		MidOrder(root->right);
	}
}

void PostOrder(pBTNode root)
{
	if(root!=NULL) {
		PostOrder(root->left);
		PostOrder(root->right);
		cout<<root->data<<' ';
	}
}

int BTreeCount(pBTNode root)
{
	if(root==NULL) return 0;
	else return BTreeCount(root->left)+BTreeCount(root->right)+1;
}

int BTreeDepth(pBTNode root)
{
	if(root==NULL) return 0;
	else {
		int depl=BTreeDepth(root->left);
		int depr=BTreeDepth(root->right);
		if(depl>depr) return depl+1;
		else return depr+1;
	}
}

pBTNode FindBTree(pBTNode root,char item)
{
	if(root==NULL) return NULL;
	if(root->data==item) return root;
	pBTNode p=FindBTree(root->left,item);
	if(p!=NULL) return p;
	else return FindBTree(root->right,item);
}

void ClearBTree(pBTNode root)
{
	if(root!=NULL) {
		ClearBTree(root->left);
		ClearBTree(root->right);
		delete root;
		root=NULL;
	}
}