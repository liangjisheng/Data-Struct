
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

typedef int Type;

typedef struct BSTreeNode
{
	Type key;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
	struct BSTreeNode *parent;
}Node, *BSTree;

// ǰ��������������
void preorder_bstree(BSTree tree);
// ����������������
void inorder_bstree(BSTree tree);
// ����������������
void postorder_bstree(BSTree tree);

// (�ݹ�ʵ��)���Ҷ���������м�ֵΪkey�Ľڵ�
Node* bstree_search(BSTree tree, Type key);
// (�ǵݹ�ʵ��)���Ҷ���������м�ֵΪkey�Ľڵ�
Node* iterative_bstree_search(BSTree tree, Type key);

// ������С�ڵ�:����treeΪ���ڵ�Ķ���������С�ڵ�
Node* bstree_minimum(BSTree tree);
// �������ڵ�:����treeΪ���ڵ�Ķ����������ڵ�
Node* bstree_maximum(BSTree tree);

// �ҽڵ�x�ĺ�̽ڵ�(�������).�����Ҷ�����������ֵ���ڸýڵ����С�ڵ�
Node* bstree_successor(Node* x);
// �ҽڵ�x��ǰ���ڵ�(�������).�����Ҷ�����������ֵС�ڸýڵ�����ڵ�
Node* bstree_predecessor(Node *x);

// ���ڵ���뵽��������,�����ظ��ڵ�
Node* bstree_insert(BSTree tree, Type key);

// ɾ���ڵ�(keyΪ�ڵ��ֵ),�����ظ��ڵ�
Node* bstree_delete(BSTree tree, Type key);

// ɾ���ڵ�(keyΪ�ڵ��ֵ),�����ظ��ڵ�
Node* bstree_delete_1(BSTree tree, Type key);

// ɾ���ڵ�(keyΪ�ڵ��ֵ),�����ظ��ڵ�
// bstree_delete_2()��ʵ�ֲ�����ȷ��
Node* bstree_delete_2(BSTree tree, Type key);

// ���ٶ�����
void bstree_destroy(BSTree tree);

// ��ӡ������
// tree��ʾ�������Ľڵ�,key��ʾ�ڵ�ļ�ֵ,direction��ʾ�ڵ������
// direction == 0,��ʾ�Ǹ��ڵ�
// direction == -1,��ʾ�ýڵ������ĸ��ڵ������
// direction == 1,��ʾ�ýڵ������ĸ��ڵ���Һ���
void bstree_print(BSTree tree, Type key, int direction);

#endif // _BINARY_SEARCH_TREE_H_