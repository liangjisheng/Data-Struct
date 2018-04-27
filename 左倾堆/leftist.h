
// �����(leftist tree �� leftist heap)���ֱ���Ϊ��ƫ������ƫ�ѡ�����ѣ��Ͷ����һ�����������ȶ���
// ʵ�ַ�ʽ�������ȶ������漰��"���������ȶ��н��кϲ�"������ʱ������ѵ�Ч�ʾ��޷��������⣬������
// ������ԺܺõĽ����������
// ����ѵĶ���: �������һ�ö����������Ľڵ���˺Ͷ������Ľڵ�һ��������������ָ���⣬������������
// ����ֵ������롣
// (01) ��ֵ�����������ȽϽڵ�Ĵ�С���Ӷ��Խڵ��������
// (02) �����(Ӣ����NPL����Null Path Length)���Ǵ�һ���ڵ㵽һ��"����Ĳ����ڵ�"��·�����ȡ������ڵ�
// ��ָ�øýڵ�����Һ�����������һ��ΪNULL��Ҷ�ڵ��NPLΪ0��NULL�ڵ��NPLΪ-1

// ����ѵĻ������ʣ�
// 1.�ڵ�ļ�ֵС�ڻ�������������ӽڵ�ļ�ֵ
// 2.�ڵ�����ӵ�NPL >= �Һ��ӵ�NPL
// 3.�ڵ��NPL = �����Һ��ӵ�NPL + 1

// ����ѣ�����˼�壬���е�������б����˼�ˡ�����ͳ�����⡢��ֵ���⡢ģ�������̰����������������Ź㷺��Ӧ��
// ǰ��˵�������ܺͺõĽ��"�������ȶ��кϲ�"�����⡣ʵ���ϣ�����ѵĺϲ�������ƽ̯ʱ�临�Ӷ�ΪO(lg n)��
// ����ȫ�����ΪO(n)���ϲ��������������ص㣬�����ɾ�����������Ժϲ�����Ϊ�����ġ�������������Կ���
// �����������ϲ���ɾ������(�Ƴ����ȶ����ж���Ԫ��)�������Ƴ����ڵ�֮���ٺϲ�ʣ�������������

// �ϲ�����������ѵ��ص㣬����˼������:
// 1.���һ�����������һ���ǿ�����Ѻϲ������طǿ������
// 2.�����������Ѷ��ǿգ���ô�Ƚ��������ڵ㣬ȡ��С�ѵĸ��ڵ�Ϊ�µĸ��ڵ㡣
//   ����С�ѵĸ��ڵ���Һ�����ϴ�ѽ��кϲ�
// 3.����¶ѵ��Һ��ӵ�NPL>���ӵ�NPL���򽻻����Һ���
// 4.�����¶ѵĸ��ڵ��NPL=���Ӷѵ�NPL + 1

#ifndef _LEFTIST_TREE_H_
#define _LEFTIST_TREE_H_

typedef int Type;

typedef struct _LeftistNode
{
	Type key;						// ��ֵ
	int npl;						// ��·������(NULL Path, Length)
	struct _LeftistNode *left;		// ����
	struct _LeftistNode *right;		// �Һ���
}LeftistNode, *LeftistHeap;


// ǰ�����
void preorder_leftist(LeftistHeap heap);
// �������
void inorder_leftist(LeftistHeap heap);
// �������
void postorder_leftist(LeftistHeap heap);


// ��ȡ��Сֵ(���浽pval��)���ɹ�����0��ʧ�ܷ���-1
int leftist_minimum(LeftistHeap heap, Type *pval);

// �ϲ������x�������y�������غϲ��������
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);

// ���ڵ���뵽������У������ظ��ڵ�
LeftistNode* insert_leftist(LeftistHeap heap, Type key);

// ɾ���ڵ�(keyΪ�ڵ�ļ�ֵ),�����ظ��ڵ�
LeftistNode* delete_leftist(LeftistHeap heap);

// ���������
void destroy_leftist(LeftistHeap heap);

// ��ӡ�����
void print_leftist(LeftistHeap heap);


#endif // _LEFTIST_TREE_H_