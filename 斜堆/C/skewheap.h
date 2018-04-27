
// 斜堆(Skew heap)也叫自适应堆(self-adjusting heap)，他是左倾堆的一个变种，和左倾堆一样
// 它通常用于实现优先队列，它的合并操作的时间复杂度也是O(lg n)
// 像比于左倾堆，斜堆的节点没有零距离这个属性。除此之外，他们斜堆的合并操作也不同
// 斜堆的合并操作算法如下:
// 1. 如果一个空斜堆与一个非空斜堆合并，返回非空斜堆
// 2. 如果两个斜堆都非空，那么比较两个根节点，取较小堆的根节点为新的根节点。将较小堆的根节点
//    的右孩子与较大堆进行合并
// 3. 合并后，交换新堆根节点的左孩子和右孩子
// 第3步是斜堆与左倾堆的合并操作差别的关键所在，如果是左倾堆，则合并后要比较左右孩子的零距离
// 大小，若右孩子的零距离大于左孩子的零距离，则交换左右孩子；最后，在设置根的零距离

#ifndef _SKEW_HEAP_H_
#define _SKEW_HEAP_H_

typedef int Type;

typedef struct _SkewNode
{
	Type key;
	struct _SkewNode *left;
	struct _SkewNode *right;
}SkewNode, *SkewHeap;


// 前序遍历
void preorder_skewheap(SkewHeap heap);
// 中序遍历
void inorder_skewheap(SkewHeap heap);
// 后序遍历
void postorder_skewheap(SkewHeap heap);

// 获取最小值(保存到pval中)，成功返回0，失败返回-1
int skewheap_minimum(SkewHeap heap, Type* pval);
// 合并斜堆x和y，返回合并后的新树
SkewNode* merge_skewheap(SkewHeap x, SkewHeap y);
// 将节点插入到斜堆中，并返回根节点
SkewNode* insert_skewheap(SkewHeap heap, Type key);
// 删除根节点，并返回新的根节点
SkewNode* delete_skewheap(SkewHeap heap);

// 销毁斜堆
void destroy_skewheap(SkewHeap heap);
// 打印斜堆
void print_skewheap(SkewHeap heap);

#endif // _SKEW_HEAP_H_