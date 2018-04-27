
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

// AVL���Ǹ������ķ�����G.M. Adelson-Velsky��E.M. Landis������
// ����ƽ����:�κνڵ�����������ĸ߶Ȳ��С�ڵ���1
// avl���Ĳ��ҡ������ɾ����ƽ�����������¶���O(logn)
// http://www.cnblogs.com/skywang12345/p/3576969.html

typedef int Type;

typedef struct AVLTreeNode
{
	Type key;
	int height;
	struct AVLTreeNode *left;
	struct AVLTreeNode *right;
}Node, *AVLTree;

// ��ȡAVL���ĸ߶�
int avltree_height(AVLTree tree);

// ǰ�����"AVL��"
void preorder_avltree(AVLTree tree);
// �������"AVL��"
void inorder_avltree(AVLTree tree);
// �������"AVL��"
void postorder_avltree(AVLTree tree);

void print_avltree(AVLTree tree, Type key, int direction);

// (�ݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
Node* avltree_search(AVLTree x, Type key);
// (�ǵݹ�ʵ��)����"AVL��x"�м�ֵΪkey�Ľڵ�
Node* iterative_avltree_search(AVLTree x, Type key);

// ������С��㣺����treeΪ������AVL������С���
Node* avltree_minimum(AVLTree tree);
// ��������㣺����treeΪ������AVL���������
Node* avltree_maximum(AVLTree tree);

// �������뵽AVL���У����ظ��ڵ�,���Բ�����ͬ��ֵ
Node* avltree_insert(AVLTree tree, Type key);

// �������뵽AVL���У����ظ��ڵ�,�����Բ�����ͬ��ֵ
Node* avltree_insert_1(AVLTree tree, Type key);

// ɾ�����(key�ǽڵ�ֵ)�����ظ��ڵ�
Node* avltree_delete(AVLTree tree, Type key);

// ����AVL��
void destroy_avltree(AVLTree tree);

#endif // _AVL_TREE_H_