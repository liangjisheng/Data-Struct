
/**
  * ����������(C����): C����ʵ�ֵĶ�����������
  *
  * @author liangjisheng
  * @date 2017/10/18
  */

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"


static Node* create_bstree_node(Type key, Node *parent, Node *left, Node *right)
{
	Node *p = (Node *)malloc(sizeof(Node));
	if(!p)
		return NULL;

	p->key = key;
	p->left = left;
	p->right = right;
	p->parent = parent;

	return p;
}


void preorder_bstree(BSTree tree)
{
	if(tree)
	{
		printf("%d ", tree->key);
		preorder_bstree(tree->left);
		preorder_bstree(tree->right);
	}
}

void inorder_bstree(BSTree tree)
{
	if(tree)
	{
		inorder_bstree(tree->left);
		printf("%d ", tree->key);
		inorder_bstree(tree->right);
	}
}

void postorder_bstree(BSTree tree)
{
	if(tree)
	{
		postorder_bstree(tree->left);
		postorder_bstree(tree->right);
		printf("%d ", tree->key);
	}
}


Node* bstree_search(BSTree tree, Type key)
{
	if(tree == NULL || tree->key == key)
		return tree;

	if(key < tree->key)
		return bstree_search(tree->left, key);
	else
		return bstree_search(tree->right, key);
}

Node* iterative_bstree_search(BSTree tree, Type key)
{
	while(tree && tree->key != key)
	{
		if(key < tree->key)
			tree = tree->left;
		else
			tree = tree->right;
	}

	return tree;
}


Node* bstree_maximum(BSTree tree)
{
	if(!tree)
		return NULL;

	while(tree->right)
		tree = tree->right;

	return tree;
}

Node* bstree_minimum(BSTree tree)
{
	if(!tree)
		return NULL;

	while(tree->left)
		tree = tree->left;

	return tree;
}


Node* bstree_predecessor(Node *x)
{
	// ���x��������,��x��ǰ���ڵ�Ϊ"��������Ϊ�������������ڵ�"
	if(x->left)
		return bstree_maximum(x->left);

	// ���xû������,��Ϊ����ǰ���ڵ�,�ڶ���������в���Ҫ����x���Һ���
	// �����ֿ���:
	// 1:x��һ���Һ���,��x��ǰ���ڵ�Ϊ���ĸ��ڵ�
	// 2:x��һ������,�����x����͸��ڵ�,���Ҹø��ڵ�Ҫ�����Һ���
	//   �ҵ���������ڵ����x��ǰ���ڵ�
	Node* par = x->parent;
	// ���ҵ�x��ǰ���ڵ�ʱ,��ʱ��xһ�������ĸ��ڵ���Һ���,���ϲ�����͸��ڵ�
	while(par && par->left == x)
	{
		x = par;
		par = par->parent;
	}

	return par;
}

Node* bstree_successor(Node* x)
{
	// ���x�����Һ���,��x�ĺ�̽ڵ�Ϊ�����Һ���Ϊ������������С�ڵ�
	if(x->right)
		return bstree_minimum(x->right);

	// ���xû���Һ���,��x�����ֿ���
	// 1:x��һ������,��x�ĺ�̽ڵ�Ϊ���ĸ��ڵ�
	// 2:x��һ���Һ���,�����x����͸��ڵ�,���Ҹø��ڵ�Ҫ��������,
	//   �ҵ��������͸��ڵ����x�ĺ�̽ڵ�
	Node* par = x->parent;
	while(par && x == par->right)
	{
		x = par;
		par = par->parent;
	}

	return par;
}


static Node* bstree_insert(BSTree tree, Node *z)
{
	Node *pre = NULL;
	Node *cur = tree;

	// ����z�Ĳ���λ��
	while(cur)
	{
		pre = cur;
		if(z->key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	// ����Ĳ���z��λ��ʵ�ֵ������������ͬ��ֵ�Ľڵ�,�����ϣ������
	// ��ͬ��ֵ�Ľڵ�,�ɽ�����z��λ�õĴ��뻻�������
	// ����z�Ĳ���λ��
	//while(cur)
	//{
	//	pre = cur;
	//	if(z->key < cur->key)
	//		cur = cur->left;
	//	else if(z->key > cur->key)
	//		cur = cur->right;
	//	else
	//	{
	//		free(z);		// �ͷ�֮ǰ�����ϵͳ
	//		return tree;
	//	}
	//}

	z->parent = pre;
	if(pre == NULL)
		tree = z;
	else if(z->key < pre->key)
		pre->left = z;
	else
		pre->right = z;

	return tree;
}

Node* bstree_insert(BSTree tree, Type key)
{
	Node *z = NULL;
	z = create_bstree_node(key, NULL, NULL, NULL);
	if(!z)
		return tree;

	return bstree_insert(tree, z);
}


static Node* bstree_delete(BSTree tree, Node *z)
{
	if(!tree)		// ��Ϊ��,ֱ�ӷ���
		return NULL;

	Node *x = NULL;
	Node *y = NULL;

	// ���z��Ҷ�ӽڵ����zֻ��һ������
	if(z->left == NULL || z->right == NULL)
		y = z;
	else
		y = bstree_successor(z);

	if(y->left)
		x = y->left;
	else
		x = y->right;

	if(x)
		x->parent = y->parent;

	if(y->parent == NULL)
		tree = x;
	else if(y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	if(y != z)
		z->key = y->key;

	if(y)
		free(y);

	return tree;
}

Node* bstree_delete(BSTree tree, Type key)
{
	Node *z;
	if((z = bstree_search(tree, key)) != NULL)
		tree = bstree_delete(tree, z);

	return tree;
}


static Node* bstree_delete_1(BSTree tree, Node *pNode)
{
	// ��һ�����:ɾ��û���ӽڵ�Ľڵ�
	if(pNode->left == NULL && pNode->right == NULL)
	{
		if(pNode == tree)
		{ 
			// ����Ǹ��ڵ㣬��ô��ɾ��������
			free(pNode); 
			tree = NULL; 
		}
		else if(pNode == pNode->parent->left)
		{
			// �������ڵ��Ǹ��ڵ����ڵ㣬�򽫸��ڵ����ڵ���Ϊ��
			pNode->parent->left = pNode->left;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// �������ڵ��Ǹ��ڵ���ҽڵ㣬�򽫸��ڵ���ҽڵ���Ϊ��
			pNode->parent->right = pNode->right;
			free(pNode);
		}

		return tree;
	}

	// ɾ��ֻ��һ���ӽڵ�Ľڵ�
	// ���Ҫɾ���Ľڵ�ֻ���Һ���
	if(pNode->right!= NULL && pNode->left == NULL)
	{
		if(pNode == tree)
		{
			// ɾ�����ڵ�
			tree = pNode->right;
			tree->parent = NULL;
			free(pNode);
		}
		else if(pNode == pNode->parent->left)
		{
			// ɾ���ڵ�������
			pNode->parent->left = pNode->right;
			pNode->right->parent = pNode->parent;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// ɾ���ڵ����Һ���
			pNode->parent->right = pNode->right;
			pNode->right->parent = pNode->parent;
			free(pNode);
		}

		return tree;
	}

	// Ҫɾ���Ľڵ�ֻ������
	if(pNode->left != NULL && pNode->right == NULL)
	{
		if(pNode == tree)
		{
			// ɾ�����ڵ�
			tree = pNode->left;
			tree->parent = NULL;
			free(pNode);
		}
		else if(pNode == pNode->parent->left)
		{
			// ɾ���ڵ�������
			pNode->parent->left = pNode->left;
			pNode->left->parent = pNode->parent;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// ɾ���ڵ����Һ���
			pNode->parent->right = pNode->left;
			pNode->left->parent = pNode->parent;
			free(pNode);
		}

		return tree;
	}

	// ɾ�����������ӵĽڵ�,�����Һ��Ӷ��ǿ�
	// ��������Ҫɾ���ڵ�ĺ����ڵ����Ҫɾ���Ľڵ㣬��ɾ�������ڵ�
	// (ɾ�������ڵ��ʱ��ͬ���ĵݹ����)
	// ����Ҫ�õ������Ҳ�ͻᷢ������,�������ڵ㲻���ڼ����ݹ��ɾ��
	// ��һ�������ڵ�,��ΪҪɾ���Ľڵ�ĺ����ڵ�϶���:Ҫɾ�����Ǹ��ڵ��
	// ����������С�ؼ���,�������С�ؼ��ֿ϶���������ڵ㣬������ɾ��
	// �����ڵ��ʱ��϶������õ�(�����ڵ㶼�ǿյ��ж�),������ӽڵ�
	// �϶�ֻ��һ���ҽڵ�
	if(pNode->left && pNode->right)
	{
		// pNode�ĺ����ڵ�
		Node *successorNode = bstree_successor(pNode);
		if(pNode == tree)
			tree->key = successorNode->key;
		else
			// �������ڵ��ֵ��ֵ���Ǹ�Ҫɾ���Ľڵ�
			pNode->key = successorNode->key;
		bstree_delete_1(tree, successorNode);

		return tree;
	}

	return tree;
}

Node* bstree_delete_1(BSTree tree, Type key)
{
	if(tree)
	{
		Node *pNode = bstree_search(tree, key);
		if(pNode)
			tree = bstree_delete_1(tree, pNode);
	}

	return tree;
}

// ���ɾ����ʵ�ֲ�û�п��Ǹ��ڵ�,���������������ʵ�����治�ܷ��ʸ��ڵ�
Node* bstree_delete_2(BSTree tree, Type key)
{
	if(tree)
	{
		Node *pNode = bstree_search(tree, key);
		if(pNode)
		{
			Node *cur = tree, *pre = NULL;
			while(cur)
			{
				if(key < cur->key)
				{
					pre = cur;
					cur = cur->left;
				}
				else if(key > cur->key)
				{
					pre = cur;
					cur = cur->right;
				}
				else if(cur->left && cur->right)
				{
					key = cur->key = bstree_minimum(cur->right)->key;
					pre = cur;
					cur = cur->right;
				}
				else
				{
					Node* oldnode = cur;
					cur = cur->left ? cur->left : cur->right;
					//cur->parent = oldnode->parent;
					free(oldnode);
					break;
				}
			}

			if(pre == NULL)
			{
				// preΪ��˵��ɾ�����Ǹ��ڵ�
				tree = cur;
				return tree;
			}
			else if(pre->key > key)
			{
				//free(pre);
				//pre = NULL;
				pre->left = cur;
			}
			else
			{
				//free(pre);
				//pre = NULL;
				pre->right = cur;
			}

			return tree;
		}
		else
			return tree;
	}
	else
		return NULL;
}


void bstree_print(BSTree tree, Type key, int direction)
{
	if(tree)
	{
		if(direction == 0)		// tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else
			printf("%2d is %2d's %6s child\n", tree->key, key, 
				direction == 1 ? "right" : "left");

		bstree_print(tree->left, tree->key, -1);
		bstree_print(tree->right, tree->key, 1);
	}
}

void bstree_destroy(BSTree tree)
{
	if(!tree)
		return ;

	if(tree->left)
		bstree_destroy(tree->left);
	if(tree->right)
		bstree_destroy(tree->right);

	free(tree);
}

