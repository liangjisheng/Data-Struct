
// �������Ľ��������
#include <iostream>
#include <stack>

using namespace std;

typedef struct node
{
	struct node *lchild;
	struct node *rchild;
	char data;
}BiTreeNode, *BiTree;

// ǰ���������������
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

// ǰ���������������ӡ����
void preorder(BiTree T)
{
	if(T)
	{
		cout << T->data << ' ';
		preorder(T->lchild);
		preorder(T->rchild);
	}
}

// ǰ��ǵݹ����,������һ�ڵ�p
// 1:���ʽڵ�p,�����ڵ�p��ջ
// 2:�жϽڵ�p�������Ƿ�Ϊ��,��Ϊ��,��ȡջ���ڵ���г�ջ,����ջ���ڵ�
//   ���Һ�����Ϊ��ǰ�ڵ�p,ѭ��1;����Ϊ��,��p��������Ϊ��ǰ�ڵ�p
// 3:ֱ��pΪ��,����ջΪ��,���������
int NoPreOrderTraverse(BiTree T)
{
	stack<BiTree> s;
	BiTree tmp = T;

	if(tmp == NULL)
	{
		cout << "the tree is NULL" << endl;
		return -1;
	}

	// �Ƚ���������ջ������Ҷ�ӽڵ�󣬳�ջ����ȡ������
	// ������������������ջ
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

// �������
void inorder(BiTree T)
{
	if(T)
	{
		inorder(T->lchild);
		cout << T->data << ' ';
		inorder(T->rchild);
	}
}

// ����ǵݹ����:������һ�ڵ�
// 1:�������Ӳ�Ϊ��,��p��ջ,����p����������Ϊ��ǰ��p,Ȼ��Ե�ǰ�ڵ������ͬ�Ĳ���
// 2:��������Ϊ��,��ȡջ��Ԫ�ز����г�ջ����,���ʸ�ջ���ڵ�,
//   ����ǰp��Ϊջ���ڵ���Һ���
// 3:ֱ��pΪ����ջΪ��,��������
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

// �������
void postorder(BiTree T)
{
	if(T)
	{
		postorder(T->lchild);
		postorder(T->rchild);
		cout << T->data << ' ';
	}
}

// ����ǵݹ������ʵ�������ֱ�����ʽ�����ѵ�һ�֣���ΪҪ��֤���Ӻ��Һ���
// ���Ѿ������ʣ������������Һ���֮ǰ���ʲ��ܷ��ʸ��ڵ�,�����������һ��˼·
// Ҫ��֤���ڵ������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ�ڵ�p,�Ȳ�����
// ��ջ.��p���������Ӻ��Һ���,�����ֱ�ӷ�����������p�������Ӻ��Һ��ӣ�
// ���������Ӻ��Һ��Ӷ��Ѿ������ʹ�����ͬ������ֱ�ӷ��ʸýڵ㡣������������
// �������p���Һ��Ӻ�����һ����ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ��
// �������Һ���֮ǰ�����ʣ����Ӻ��Һ��Ӷ��ڸ��ڵ�ǰ������
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
			// �����ǰ�ڵ�û�к��ӽڵ���ߺ��ӽڵ㶼�ѱ����ʹ�
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
	cout << "ǰ���������������:" << endl;
	cout << "����ǰ������:";		// input ab##c##
	createBiTree(T);
	cout << "�������������" << endl;

	cout << "ǰ�����������:" << endl;
	preorder(T);
	cout << endl;

	cout << "ǰ��ǵݹ����������:" << endl;
	NoPreOrderTraverse(T);
	cout << endl;

	cout << "�������������:" << endl;
	inorder(T);
	cout << endl;

	cout << "����ǵݹ����������:" << endl;
	NoInOrderTraverse(T);
	cout << endl;

	cout << "�������������:" << endl;
	postorder(T);
	cout << endl;

	cout << "����ǵݹ����:" << endl;
	NoPostOrderTraverse(T);
	cout << endl;

	system("pause");
	return 0;
}

