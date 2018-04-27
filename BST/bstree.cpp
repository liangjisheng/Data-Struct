
/**
  * 二叉搜索树(C语言): C语言实现的二叉搜索树。
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
	// 如果x存在左孩子,则x的前驱节点为"以其左孩子为根的子树的最大节点"
	if(x->left)
		return bstree_maximum(x->left);

	// 如果x没有左孩子,因为是求前驱节点,在二叉查找树中不需要考虑x的右孩子
	// 有两种可能:
	// 1:x是一个右孩子,则x的前驱节点为它的父节点
	// 2:x是一个左孩子,则查找x的最低父节点,并且该父节点要具有右孩子
	//   找到的这个父节点就是x的前驱节点
	Node* par = x->parent;
	// 当找到x的前驱节点时,此时的x一定是它的父节点的右孩子,向上查找最低父节点
	while(par && par->left == x)
	{
		x = par;
		par = par->parent;
	}

	return par;
}

Node* bstree_successor(Node* x)
{
	// 如果x存在右孩子,则x的后继节点为以其右孩子为根的子树的最小节点
	if(x->right)
		return bstree_minimum(x->right);

	// 如果x没有右孩子,则x有两种可能
	// 1:x是一个左孩子,则x的后继节点为它的父节点
	// 2:x是一个右孩子,则查找x的最低父节点,并且该父节点要具有左孩子,
	//   找到的这个最低父节点就是x的后继节点
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

	// 查找z的插入位置
	while(cur)
	{
		pre = cur;
		if(z->key < cur->key)
			cur = cur->left;
		else
			cur = cur->right;
	}

	// 上面的查找z的位置实现的是允许插入相同键值的节点,如果不希望插入
	// 相同键值的节点,可将查找z的位置的代码换成下面的
	// 查找z的插入位置
	//while(cur)
	//{
	//	pre = cur;
	//	if(z->key < cur->key)
	//		cur = cur->left;
	//	else if(z->key > cur->key)
	//		cur = cur->right;
	//	else
	//	{
	//		free(z);		// 释放之前分配的系统
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
	if(!tree)		// 树为空,直接返回
		return NULL;

	Node *x = NULL;
	Node *y = NULL;

	// 如果z是叶子节点或者z只有一个孩子
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
	// 第一种情况:删除没有子节点的节点
	if(pNode->left == NULL && pNode->right == NULL)
	{
		if(pNode == tree)
		{ 
			// 如果是根节点，那么就删除整个树
			free(pNode); 
			tree = NULL; 
		}
		else if(pNode == pNode->parent->left)
		{
			// 如果这个节点是父节点的左节点，则将父节点的左节点设为空
			pNode->parent->left = pNode->left;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// 如果这个节点是父节点的右节点，则将父节点的右节点设为空
			pNode->parent->right = pNode->right;
			free(pNode);
		}

		return tree;
	}

	// 删除只有一个子节点的节点
	// 如果要删除的节点只有右孩子
	if(pNode->right!= NULL && pNode->left == NULL)
	{
		if(pNode == tree)
		{
			// 删除跟节点
			tree = pNode->right;
			tree->parent = NULL;
			free(pNode);
		}
		else if(pNode == pNode->parent->left)
		{
			// 删除节点是左孩子
			pNode->parent->left = pNode->right;
			pNode->right->parent = pNode->parent;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// 删除节点是右孩子
			pNode->parent->right = pNode->right;
			pNode->right->parent = pNode->parent;
			free(pNode);
		}

		return tree;
	}

	// 要删除的节点只有左孩子
	if(pNode->left != NULL && pNode->right == NULL)
	{
		if(pNode == tree)
		{
			// 删除根节点
			tree = pNode->left;
			tree->parent = NULL;
			free(pNode);
		}
		else if(pNode == pNode->parent->left)
		{
			// 删除节点是左孩子
			pNode->parent->left = pNode->left;
			pNode->left->parent = pNode->parent;
			free(pNode);
		}
		else if(pNode == pNode->parent->right)
		{
			// 删除节点是右孩子
			pNode->parent->right = pNode->left;
			pNode->left->parent = pNode->parent;
			free(pNode);
		}

		return tree;
	}

	// 删除有两个孩子的节点,即左右孩子都非空
	// 方法是用要删除节点的后续节点代替要删除的节点，并删除后续节点
	// (删除后续节点的时候同样的递归操作)
	// 这里要用到的最多也就会发生两次,即后续节点不会在继续递归的删除
	// 下一个后续节点,因为要删除的节点的后续节点肯定是:要删除的那个节点的
	// 右子树的最小关键字,而这个最小关键字肯定不会有左节点，所以在删除
	// 后续节点的时候肯定不会用到(两个节点都非空的判断),如果有子节点
	// 肯定只有一个右节点
	if(pNode->left && pNode->right)
	{
		// pNode的后续节点
		Node *successorNode = bstree_successor(pNode);
		if(pNode == tree)
			tree->key = successorNode->key;
		else
			// 将后续节点的值赋值给那个要删除的节点
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

// 这个删除的实现并没有考虑父节点,所以在这个函数的实现里面不能访问父节点
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
				// pre为空说明删除的是根节点
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
		if(direction == 0)		// tree是根节点
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

