
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

// 前面说过，如果在AVL树中进行插入或删除节点后，可能导致AVL树失去平衡
// 这种失去平衡的可以概括为4种姿态：LL(左左)，LR(左右)，RR(右右)和RL(右左)
// (1) LL：LeftLeft，也称为"左左"。插入或删除一个节点后，根节点的左子树
// 的左子树还有非空子节点，导致"根的左子树的高度"比"根的右子树的高度"大2
// 导致AVL树失去了平衡
// (2) LR：LeftRight，也称为"左右"。插入或删除一个节点后，根节点的左子树
// 的右子树还有非空子节点，导致"根的左子树的高度"比"根的右子树的高度"大2
// 导致AVL树失去了平衡
// (3) RL：RightLeft，称为"右左"。插入或删除一个节点后，根节点的右子树的
// 左子树还有非空子节点，导致"根的右子树的高度"比"根的左子树的高度"大2
// 导致AVL树失去了平衡
// (4) RR：RightRight，称为"右右"。插入或删除一个节点后，根节点的右子树的
// 右子树还有非空子节点，导致"根的右子树的高度"比"根的左子树的高度"大2
// 导致AVL树失去了平衡

// 左左(LL)对应的情况(左单旋转),返回旋转后的根节点
// 将tree->left变成根节点，tree->left的右子树变成tree的左子树,tree变成tree->left的右子树
static Node* left_left_rotation(AVLTree tree)
{
	AVLTree pLeft = tree->left;
	tree->left = pLeft->right;
	pLeft->right = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	pLeft->height = MAX(HEIGHT(pLeft->left), tree->height) + 1;

	return pLeft;
}

// RR旋转(右单旋转),返回旋转后的根节点
// k2变成根节点,k2的左子树变成k1的右子树,k1变成k2的左子树
static Node* right_right_rotation(AVLTree tree)
{
	AVLTree pRight = tree->right;
	tree->right = pRight->left;
	pRight->left = tree;

	tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;
	pRight->height = MAX(HEIGHT(pRight->right), tree->height) + 1;

	return pRight;
}

// LR旋转,需要经过两次旋转才能让AVL树恢复平衡
// 先将节点的左子树RR旋转,再将节点LL旋转
static Node* left_right_rotation(AVLTree tree)
{
	tree->left = right_right_rotation(tree->left);
	return left_left_rotation(tree);
}

// RL旋转,需要经过两次旋转才能将AVL树恢复平衡
// 先将节点的右子树LL旋转,再将节点RR旋转
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

// 树中节点可以有相同的值
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
		// 插入节点后,若avl树失去平衡,则进行相应的调节
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

// 树中节点不可以有相同的值
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
		// 插入节点后,若avl树失去平衡,则进行相应的调节
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
		printf("不允许添加相同的节点\n");


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
		// 若删除节点后,avl树失去平衡,则进行相应的调节
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
		// 删除后若失去平衡,则调节
		if(HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
		{
			Node *l = tree->left;
			if(HEIGHT(l->right) > HEIGHT(l->left))
				tree = left_right_rotation(tree);
			else
				tree = left_left_rotation(tree);
		}
	}
	else		// tree为对应要删除的节点
	{
		if(tree->left && tree->right)
		{
			// 当要删除的节点左右子树都不为空的时候,这时既可以用左子树的最大节点
			// 代替要删除的节点,也可以用右子树的最小节点代替要删除的节点,当要删除
			// 的节点的左子树的高度大于右子树的高度时,用左子树的最大节点代替,否则
			// 用右子树的最小节点代替.这样做的好处是删除节点后,avl树仍然是平衡的
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
		if(0 == direction)		// tree是根节点
			printf("%2d is root\n", tree->key);
		else
			printf("%2d is %2d's %6s child\n", tree->key, key, 
				direction == 1 ? "right" : "left");

		print_avltree(tree->left, tree->key, -1);
		print_avltree(tree->right, tree->key, 1);
	}
}
