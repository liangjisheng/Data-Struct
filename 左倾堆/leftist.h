
// 左倾堆(leftist tree 或 leftist heap)，又被称为左偏树、左偏堆、最左堆，和二叉堆一样，都是优先队列
// 实现方式，当优先队列中涉及到"对两个优先队列进行合并"的问题时，二叉堆的效率就无法令人满意，而左倾
// 堆则可以很好的解决这类问题
// 左倾堆的定义: 左倾堆是一棵二叉树，它的节点除了和二叉树的节点一样具有左右子树指针外，还有两个属性
// ：键值和零距离。
// (01) 键值的作用是来比较节点的大小，从而对节点进行排序。
// (02) 零距离(英文名NPL，即Null Path Length)则是从一个节点到一个"最近的不满节点"的路径长度。不满节点
// 是指该该节点的左右孩子至少有有一个为NULL。叶节点的NPL为0，NULL节点的NPL为-1

// 左倾堆的基本性质：
// 1.节点的键值小于或等于它的左右子节点的键值
// 2.节点的左孩子的NPL >= 右孩子的NPL
// 3.节点的NPL = 它的右孩子的NPL + 1

// 左倾堆，顾名思义，是有点向左倾斜的意思了。它在统计问题、最值问题、模拟问题和贪心问题等问题中有着广泛的应用
// 前面说过，它能和好的解决"两个优先队列合并"的问题。实际上，左倾堆的合并操作的平摊时间复杂度为O(lg n)，
// 而完全二叉堆为O(n)。合并就是左倾树的重点，插入和删除操作都是以合并操作为基础的。插入操作，可以看作
// 两颗左倾树合并；删除操作(移除优先队列中队首元素)，则是移除根节点之后再合并剩余的两个左倾树

// 合并操作是左倾堆的重点，基本思想如下:
// 1.如果一个空左倾堆与一个非空左倾堆合并，返回非空左倾堆
// 2.如果两个左倾堆都非空，那么比较两个根节点，取较小堆的根节点为新的根节点。
//   将较小堆的根节点的右孩子与较大堆进行合并
// 3.如果新堆的右孩子的NPL>左孩子的NPL，则交换左右孩子
// 4.设置新堆的根节点的NPL=右子堆的NPL + 1

#ifndef _LEFTIST_TREE_H_
#define _LEFTIST_TREE_H_

typedef int Type;

typedef struct _LeftistNode
{
	Type key;						// 键值
	int npl;						// 零路径长度(NULL Path, Length)
	struct _LeftistNode *left;		// 左孩子
	struct _LeftistNode *right;		// 右孩子
}LeftistNode, *LeftistHeap;


// 前序遍历
void preorder_leftist(LeftistHeap heap);
// 中序遍历
void inorder_leftist(LeftistHeap heap);
// 后序遍历
void postorder_leftist(LeftistHeap heap);


// 获取最小值(保存到pval中)，成功返回0，失败返回-1
int leftist_minimum(LeftistHeap heap, Type *pval);

// 合并左倾堆x和左倾堆y，并返回合并后的新树
LeftistNode* merge_leftist(LeftistHeap x, LeftistHeap y);

// 将节点插入到左倾堆中，并返回根节点
LeftistNode* insert_leftist(LeftistHeap heap, Type key);

// 删除节点(key为节点的键值),并返回根节点
LeftistNode* delete_leftist(LeftistHeap heap);

// 销毁左倾堆
void destroy_leftist(LeftistHeap heap);

// 打印左倾堆
void print_leftist(LeftistHeap heap);


#endif // _LEFTIST_TREE_H_