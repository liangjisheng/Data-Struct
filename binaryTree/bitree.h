
/*
 * filename: bitree.h
 * author: ����ʥ
 * date: 2017/10/17
 */

#ifndef BITREE_H_
#define BITREE_H_

#include "DoubleLink.h"

// define a binary tree node
typedef struct BiTreeNode_
{
	void *data;
	struct BiTreeNode_ *left;
	struct BiTreeNode_ *right;
}BiTreeNode;

// define a binary tree
typedef struct BiTree_
{
	int size;			// number of the elements in the tree.(�������нڵ�����)
	BiTreeNode *root;	// root node
	int (*compare)(const void *key1, const void *key2);	// �ڵ�������Ϣ�ıȽϲ���
	void (*destroy)(void *data);		// ���ٶ�����
}BiTree;

// destroy
void destroy(void *data);
// create_tree
int create_tree(BiTree *tree, BiTreeNode *node);

// ��ʼ��������,�����յĶ�����,��ʱ��û���κνڵ�,���Ƕ��������к���������ǰ��
void bitree_init(BiTree *tree, void(*destroy)(void* data));
// ���ٶ�����
void bitree_destroy(BiTree *tree);
// ��data�е���Ϣ���뵽��ǰnode�ڵ����ָ����,��nodeΪNULLʱ,�Ӹ��ڵ�λ�ò���
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data);
// ��data�е���Ϣ���뵽��ǰnode�ڵ����ָ����,��nodeΪNULLʱ,�Ӹ��ڵ�λ�ò���
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data);
// ɾ����node�ڵ�Ϊ����������������,��node == NULLʱ,��Ϊɾ������������
void bitree_rem_left(BiTree *tree, BiTreeNode *node);
// ɾ����node�ڵ�Ϊ����������������,��node == NULLʱ,��Ϊɾ������������
void bitree_rem_right(BiTree *tree, BiTreeNode *node);
// ���������������ϲ�Ϊ��data��Ϊ�����¶�����
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);

// ǰ�����������
int preorder(const BiTreeNode *node, DoubleLink<void*> *list);
// �������������
int inorder(const BiTreeNode *node, DoubleLink<void*> *list);
// �������������
int postorder(const BiTreeNode *node, DoubleLink<void*> *list);

#define bitree_size(tree) ((tree)->size)		// ��ȡ��С
#define bitree_root(tree) ((tree)->root)		// ��ȡ���ڵ�
#define bitree_is_eob(node) ((node) == NULL)	// �жϷ�֧�Ƿ����
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)	// �ж��Ƿ���Ҷ�ӽڵ�
#define bitree_data(node) ((node)->data)		// ��ȡ������
#define bitree_left(node) ((node)->left)		// ��ȡ��ڵ�
#define bitree_right(node) ((node)->right)		// ��ȡ�ҽڵ�

#endif // BITREE_H_