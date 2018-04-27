
#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define HEIGHT(tree) ((tree == NULL) ? -1 : (((Node*)(tree))->height))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int avltree_height(AVLTree tree) { return HEIGHT(tree); }

void preorder_avltree(AVLTree tree)
{
     if(tree != NULL)
     {
         printf("%d ", tree->key);
         preorder_avltree(tree->left);
         preorder_avltree(tree->right);
     }
}

void inorder_avltree(AVLTree tree)
{
	if(tree)
	{
		inorder_avltree(tree->left);
		printf("%d ", tree->key);
		inorder_avltree(tree->right);
	}
}

void postorder_avltree(AVLTree tree)
{
	if(tree)
	{
		postorder_avltree(tree->left);
		postorder_avltree(tree->right);
		printf("%d ", tree->key);
	}
}

Node* avltree_search(AVLTree x, Type key)
{
	if(NULL == x || x->key == key)
		return x;
	
	if(key < x->key)
		return avltree_search(x->left, key);
	else
		return avltree_search(x->right, key);
}

Node* iterative_avltree_search(AVLTree x, Type key)
{
	while(x && x->key != key)
	{
		if(key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

Node* avltree_minimum(AVLTree tree)
{
	if(NULL == tree)
		return NULL;

	while(tree->left)
		tree = tree->left;
	return tree;
}

Node* avltree_maximum(AVLTree tree)
{
	if(NULL == tree)
		return NULL;

	while(tree->right)
		tree = tree->right;
	return tree;
}

// ǰ��˵���������AVL���н��в����ɾ���ڵ�󣬿��ܵ���AVL��ʧȥƽ��
// ����ʧȥƽ��Ŀ��Ը���Ϊ4����̬��LL(����)��LR(����)��RR(����)��RL(����)
// (1) LL��LeftLeft��Ҳ��Ϊ"����"�������ɾ��һ���ڵ�󣬸��ڵ��������
// �����������зǿ��ӽڵ㣬����"�����������ĸ߶�"��"�����������ĸ߶�"��2
// ����AVL��ʧȥ��ƽ��
// (2) LR��LeftRight��Ҳ��Ϊ"����"�������ɾ��һ���ڵ�󣬸��ڵ��������
// �����������зǿ��ӽڵ㣬����"�����������ĸ߶�"��"�����������ĸ߶�"��2
// ����AVL��ʧȥ��ƽ��
// (3) RL��RightLeft����Ϊ"����"�������ɾ��һ���ڵ�󣬸��ڵ����������
// ���������зǿ��ӽڵ㣬����"�����������ĸ߶�"��"�����������ĸ߶�"��2
// ����AVL��ʧȥ��ƽ��
// (4) RR��RightRight����Ϊ"����"�������ɾ��һ���ڵ�󣬸��ڵ����������
// ���������зǿ��ӽڵ㣬����"�����������ĸ߶�"��"�����������ĸ߶�"��2
// ����AVL��ʧȥ��ƽ��

// ����(LL)��Ӧ�����(����ת),������ת��ĸ��ڵ�
// ��tree->left��ɸ��ڵ㣬tree->left�����������tree��������,tree���tree->left��������
static Node* left_left_rotation(AVLTree tree)
{
	AVLTree pLeft = tree->left;
	tree->left = pLeft->right;
	pLeft->right = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	pLeft->height = MAX(HEIGHT(pLeft->left), tree->height) + 1;

	return pLeft;
}

// RR��ת(�ҵ���ת),������ת��ĸ��ڵ�
// k2��ɸ��ڵ�,k2�����������k1��������,k1���k2��������
static Node* right_right_rotation(AVLTree tree)
{
	AVLTree pRight = tree->right;
	tree->right = pRight->left;
	pRight->left = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	pRight->height = MAX(HEIGHT(pRight->right), tree->height) + 1;

	return pRight;
}

// LR��ת,��Ҫ����������ת������AVL���ָ�ƽ��
// �Ƚ��ڵ��������RR��ת,�ٽ��ڵ�LL��ת
static Node* left_right_rotation(AVLTree tree)
{
	tree->left = right_right_rotation(tree->left);
	return left_left_rotation(tree);
}

// RL��ת,��Ҫ����������ת���ܽ�AVL���ָ�ƽ��
// �Ƚ��ڵ��������LL��ת,�ٽ��ڵ�RR��ת
static Node* right_left_rotation(AVLTree tree)
{
	tree->right = left_left_rotation(tree->right);
	return right_right_rotation(tree);
}


static Node* avltree_create_node(Type key, Node* left, Node* right)
{
	Node *p = (Node*)malloc(sizeof(Node));
	if(!p)
		return NULL;

	p->key = key;
	p->height = 0;
	p->left = left;
	p->right = right;

	return p;
}

// ���нڵ��������ͬ��ֵ
Node* avltree_insert(AVLTree tree, Type key)
{
	if(NULL == tree)
	{
		tree = avltree_create_node(key, NULL, NULL);
		if(!tree)
		{
			printf("Error:create avltree node failed\n");
			return NULL;
		}
	}
	else if(key < tree->key)
	{
		tree->left = avltree_insert(tree->left, key);
		// ����ڵ��,��avl��ʧȥƽ��,�������Ӧ�ĵ���
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if(key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else if(key >= tree->key)
	{
		tree->right = avltree_insert(tree->right, key);
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			if(key > tree->right->key)
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}

// ���нڵ㲻��������ͬ��ֵ
Node* avltree_insert_1(AVLTree tree, Type key)
{
	if(NULL == tree)
	{
		tree = avltree_create_node(key, NULL, NULL);
		if(!tree)
		{
			printf("Error:create avltree node failed\n");
			return NULL;
		}
	}
	else if(key < tree->key)
	{
		tree->left = avltree_insert(tree->left, key);
		// ����ڵ��,��avl��ʧȥƽ��,�������Ӧ�ĵ���
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			if(key < tree->left->key)
				tree = left_left_rotation(tree);
			else
				tree = left_right_rotation(tree);
		}
	}
	else if(key > tree->key)
	{
		tree->right = avltree_insert(tree->right, key);
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			if(key > tree->right->key)
				tree = right_right_rotation(tree);
			else
				tree = right_left_rotation(tree);
		}
	}
	else	// key == tree->key
		printf("�����������ͬ�Ľڵ�\n");


	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

	return tree;
}


static Node* delete_node(AVLTree tree, Node* pNode)
{
	if(NULL == tree || NULL == pNode)
		return NULL;

	if(pNode->key < tree->key)
	{
		tree->left = delete_node(tree->left, pNode);
		// ��ɾ���ڵ��,avl��ʧȥƽ��,�������Ӧ�ĵ���
		if(HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
		{
			Node *r = tree->right;
			if(HEIGHT(r->left) > HEIGHT(r->right))
				tree = right_left_rotation(tree);
			else
				tree = right_right_rotation(tree);
		}
	}
	else if(pNode->key > tree->key)
	{
		tree->right = delete_node(tree->right, pNode);
		// ɾ������ʧȥƽ��,�����
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			Node *l = tree->left;
			if(HEIGHT(l->right) > HEIGHT(l->left))
				tree = left_right_rotation(tree);
			else
				tree = left_left_rotation(tree);
		}
	}
	else		// treeΪ��ӦҪɾ���Ľڵ�
	{
		if(tree->left && tree->right)
		{
			// ��Ҫɾ���Ľڵ�������������Ϊ�յ�ʱ��,��ʱ�ȿ����������������ڵ�
			// ����Ҫɾ���Ľڵ�,Ҳ����������������С�ڵ����Ҫɾ���Ľڵ�,��Ҫɾ��
			// �Ľڵ���������ĸ߶ȴ����������ĸ߶�ʱ,�������������ڵ����,����
			// ������������С�ڵ����.�������ĺô���ɾ���ڵ��,avl����Ȼ��ƽ���
			if(HEIGHT(tree->left) > HEIGHT(tree->right))
			{
				Node *pMax = avltree_maximum(tree->left);
				tree->key = pMax->key;
				tree->left = delete_node(tree->left, pMax);
			}
			else
			{
				Node *pMin = avltree_minimum(tree->right);
				tree->key = pMin->key;
				tree->right = delete_node(tree->right, pMin);
			}
		}
		else
		{
			Node *pTmp = tree;
			tree = tree->left ? tree->left : tree->right;
			free(pTmp);
		}
	}

	return tree;
}

Node* avltree_delete(AVLTree tree, Type key)
{
	Node *pNode = avltree_search(tree, key);
	if(pNode)
		tree = delete_node(tree, pNode);
	return tree;
}

void destroy_avltree(AVLTree tree)
{
	if(NULL == tree)
		return ;

	if(tree->left)
		destroy_avltree(tree->left);
	if(tree->right)
		destroy_avltree(tree->right);

	free(tree);
}

void print_avltree(AVLTree tree, Type key, int direction)
{
	if(tree)
	{
		if(0 == direction)		// tree�Ǹ��ڵ�
			printf("%2d is root\n", tree->key);
		else
			printf("%2d is %2d's %6s child\n", tree->key, key, 
				direction == 1 ? "right" : "left");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}
