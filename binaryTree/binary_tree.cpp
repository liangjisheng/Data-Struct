
// 二叉树的建立与遍历
#include <iostream>
#include <stack>

using namespace std;

typedef struct node
{
	struct node *lchild;
	struct node *rchild;
	char data;
}BiTreeNode, *BiTree;

// 前序遍历建立二叉树
void createBiTree(BiTree &T)
{
	char c;
	cin >> c;
	if('#' == c)
		T = NULL;
	else
	{
		T = new BiTreeNode;
		T->data = c;
		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}
}

// 前序遍历二叉树并打印出来
void preorder(BiTree T)
{
	if(T)
	{
		cout << T->data << ' ';
		preorder(T->lchild);
		preorder(T->rchild);
	}
}

// 前序非递归遍历,对于任一节点p
// 1:访问节点p,并将节点p入栈
// 2:判断节点p的左孩子是否为空,若为空,则取栈顶节点进行出栈,并将栈顶节点
//   的右孩子置为当前节点p,循环1;若不为空,则将p的左孩子置为当前节点p
// 3:直到p为空,并且栈为空,则遍历结束
int NoPreOrderTraverse(BiTree T)
{
	stack<BiTree> s;
	BiTree tmp = T;

	if(tmp == NULL)
	{
		cout << "the tree is NULL" << endl;
		return -1;
	}

	// 先将左子树入栈，当到叶子节点后，出栈，获取右子树
	// 将右子树的左子树入栈
	while((tmp != NULL) || !s.empty())
	{
		while(tmp != NULL)
		{
			s.push(tmp);
			cout << tmp->data << ' ';
			tmp = tmp->lchild;
		}
		if(!s.empty())
		{
			tmp = s.top();
			s.pop();
			tmp = tmp->rchild;
		}
	}

	return 0;
}

// 中序遍历
void inorder(BiTree T)
{
	if(T)
	{
		inorder(T->lchild);
		cout << T->data << ' ';
		inorder(T->rchild);
	}
}

// 中序非递归遍历:对于任一节点
// 1:若其左孩子不为空,则将p入栈,并将p的左孩子设置为当前的p,然后对当前节点进行相同的操作
// 2:若其左孩子为空,则取栈顶元素并进行出栈操作,访问该栈顶节点,
//   将当前p置为栈顶节点的右孩子
// 3:直到p为空且栈为空,遍历结束
int NoInOrderTraverse(BiTree T)
{
	if(!T)
	{
		cout << "tree is null" << endl;
		return -1;
	}

	stack<BiTree> s;
	BiTree tmp = T;
	
	while(tmp != NULL || !s.empty())
	{
		while(tmp != NULL)
		{
			s.push(tmp);
			tmp = tmp->lchild;
			// cout << tmp->data << ' ';
		}
		if(!s.empty())
		{
			tmp = s.top();
			s.pop();
			cout << tmp->data << ' ';
			tmp = tmp->rchild;
		}
	}

	return 0;
}

// 后序遍历
void postorder(BiTree T)
{
	if(T)
	{
		postorder(T->lchild);
		postorder(T->rchild);
		cout << T->data << ' ';
	}
}

// 后序非递归遍历的实现是三种遍历方式中最难的一种，因为要保证左孩子和右孩子
// 都已经被访问，并且左孩子在右孩子之前访问才能访问根节点,下面介绍这样一种思路
// 要保证根节点在左孩子和右孩子访问之后才能访问，因此对于任一节点p,先不将其
// 入栈.若p不存在左孩子和右孩子,则可以直接访问它，或者p存在左孩子和右孩子，
// 但是其左孩子和右孩子都已经被访问过，则同样可以直接访问该节点。若非上述两种
// 情况，则将p的右孩子和左孩子一次入栈，这样就保证了每次取栈顶元素的时候，
// 左孩子在右孩子之前被访问，左孩子和右孩子都在根节点前被访问
int NoPostOrderTraverse(BiTree T)
{
	if(!T)
	{
		cout << "tree is null" << endl;
		return -1;
	}

	stack<BiTree> s;
	BiTree tmp = T;
	BiTree cur = NULL, pre = NULL;

	s.push(T);
	while(!s.empty())
	{
		cur = s.top();
		if((cur->lchild == NULL && cur->rchild == NULL) 
			|| (pre != NULL && (pre == cur->lchild || pre == cur->rchild)))
		{
			// 如果当前节点没有孩子节点或者孩子节点都已被访问过
			cout << cur->data << ' ';
			s.pop();
			pre = cur;
		}
		else
		{
			if(cur->lchild)
				s.push(cur->rchild);
			if(cur->rchild)
				s.push(cur->lchild);
		}
	}

	return 0;
}


int main()
{
	BiTree T = NULL;
	cout << "前序遍历建立二叉树:" << endl;
	cout << "输入前序序列:";		// input ab##c##
	createBiTree(T);
	cout << "二叉树建立完成" << endl;

	cout << "前序遍历二叉树:" << endl;
	preorder(T);
	cout << endl;

	cout << "前序非递归遍历二叉树:" << endl;
	NoPreOrderTraverse(T);
	cout << endl;

	cout << "中序遍历二叉树:" << endl;
	inorder(T);
	cout << endl;

	cout << "中序非递归遍历二叉树:" << endl;
	NoInOrderTraverse(T);
	cout << endl;

	cout << "后序遍历二叉树:" << endl;
	postorder(T);
	cout << endl;

	cout << "后序非递归遍历:" << endl;
	NoPostOrderTraverse(T);
	cout << endl;

	system("pause");
	return 0;
}

