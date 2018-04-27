
// б��(Skew heap)Ҳ������Ӧ��(self-adjusting heap)����������ѵ�һ�����֣��������һ��
// ��ͨ������ʵ�����ȶ��У����ĺϲ�������ʱ�临�Ӷ�Ҳ��O(lg n)
// ���������ѣ�б�ѵĽڵ�û�������������ԡ�����֮�⣬����б�ѵĺϲ�����Ҳ��ͬ
// б�ѵĺϲ������㷨����:
// 1. ���һ����б����һ���ǿ�б�Ѻϲ������طǿ�б��
// 2. �������б�Ѷ��ǿգ���ô�Ƚ��������ڵ㣬ȡ��С�ѵĸ��ڵ�Ϊ�µĸ��ڵ㡣����С�ѵĸ��ڵ�
//    ���Һ�����ϴ�ѽ��кϲ�
// 3. �ϲ��󣬽����¶Ѹ��ڵ�����Ӻ��Һ���
// ��3����б��������ѵĺϲ��������Ĺؼ����ڣ����������ѣ���ϲ���Ҫ�Ƚ����Һ��ӵ������
// ��С�����Һ��ӵ������������ӵ�����룬�򽻻����Һ��ӣ���������ø��������

#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

typedef int Type;

typedef struct _SkewNode
{
	Type key;
	struct _SkewNode *left;
	struct _SkewNode *right;
}SkewNode, *SkewHeap;


// ǰ�����
void preorder_skewheap(SkewHeap heap);
// �������
void inorder_skewheap(SkewHeap heap);
// �������
void postorder_skewheap(SkewHeap heap);

// ��ȡ��Сֵ(���浽pval��)���ɹ�����0��ʧ�ܷ���-1
int skewheap_minimum(SkewHeap heap, Type* pval);
// �ϲ�б��x��y�����غϲ��������
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y);
// ���ڵ���뵽б���У������ظ��ڵ�
SkewNode* insert_skewheap(SkewHeap heap, Type key);
// ɾ�����ڵ㣬�������µĸ��ڵ�
SkewNode* delete_skewheap(SkewHeap heap);

// ����б��
void destroy_skewheap(SkewHeap heap);
// ��ӡб��
void print_skewheap(SkewHeap heap);

#endif // _SKEW_HEAP_H_