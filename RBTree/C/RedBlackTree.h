
// �����(Red-Black Tree�����R-B Tree)����һ������Ķ����������
// �����������Ķ������������ζ������������������������
// ����һ���ڵ��������ļ�ֵ�����ڵ������ӵļ�ֵ��С�ڵ����Һ��ӵļ�ֵ��
// ���˾߱�������֮�⣬��������������������Ϣ��
// �������ÿ���ڵ��϶��д洢λ��ʾ�ڵ����ɫ����ɫ�Ǻ�(Red)���(Black)

// �����������:
// (1)ÿ���ڵ�����Ǻ�ɫ�����Ǻ�ɫ
// (2)���ڵ��Ǻ�ɫ
// (3)ÿ��Ҷ�ӽڵ��Ǻ�ɫ.[ע��: �����Ҷ�ӽڵ���ָΪ�յ�Ҷ�ӽڵ�]
// (4)���һ���ڵ��Ǻ�ɫ��,�������ӽڵ�����Ǻ�ɫ��
// (5)��һ���ڵ㵽�ýڵ������ڵ������·���ϰ�����ͬ���ݵĺڽڵ�

// ����5��������,��Ҫע����������:
// 1.����(3)�е�Ҷ�ӽڵ�,��ָΪ��(NULL)�Ľڵ�
// 2.����(5),ȷ��û��һ��·���������·����������,���,���������Խӽ�ƽ��Ķ�����

#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED		0		// ��ɫ�ڵ�
#define BLACK	1		// ��ɫ�ڵ�

typedef int Type;

// ������Ľڵ�
typedef struct RBTreeNode
{
	unsigned char color;		// ��ɫ(RED��BLACK)
	Type key;					// �ؼ���
	struct RBTreeNode *left;	// ����
	struct RBTreeNode *right;	// �Һ���
	struct RBTreeNode *parent;	// ���ڵ�
}Node, *RBTree;

// ������ĸ�
typedef struct rb_root
{
	Node *node;
}RBRoot;


// ��������������غ�����ĸ�
RBRoot* create_rbtree();

// ���ٺ����
void destroy_rbtree(RBRoot* root);

// ���ڵ���뵽�������,�ɹ�����0,ʧ�ܷ���-1
int insert_rbtree(RBRoot *root, Type key);

// ɾ���ڵ�(keyΪ�ڵ��ֵ)
void delete_rbtree(RBRoot *root, Type key);


// ǰ����������
void preorder_rbtree(RBRoot *root);

// ������������
void inorder_rbtree(RBRoot *root);

// ������������
void postorder_rbtree(RBRoot *root);


// (�ݹ�ʵ��)���Һ�����м�ֵΪkey�Ľڵ�,�ҵ�����0,���򷵻�-1
int rbtree_search(RBRoot *root, Type key);

// (�ǵݹ�ʵ��)���Һ�����м�ֵΪkey�Ľڵ�,�ҵ�����0,���򷵻�-1
int iterative_rbtree_search(RBRoot *root, Type key);


// ������С�ڵ��ֵ(��ֵ���浽val��).�ҵ��Ļ�,����0,���򷵻�-1
int rbtree_minimum(RBRoot *root, int *val);

// �������ڵ��ֵ(��ֵ���浽val��).�ҵ��Ļ�,����0,���򷵻�-1
int rbtree_maximum(RBRoot *root, int *val);

// ��ӡ�����
void print_rbtree(RBRoot *root);

#endif // _RED_BLACK_TREE_H_