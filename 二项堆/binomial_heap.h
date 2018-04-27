
// http://www.cnblogs.com/skywang12345/p/3655900.html
// 二项堆与之前的二叉堆、左倾堆、斜堆一样，也是用于实现优先队列的。
// 二项堆是二项树的集合
// 二项树是一种递归定义的树,定义如下:
// 1.二项树b0只有一个节点，
// 2.二项树bk有两颗二项树b(k-1)组成，其中一棵树是另一颗树根的最左孩子

// 二项树有以下性质：
// [性质一] Bk共有2k个节点。
// [性质二] Bk的高度为k。
// [性质三] Bk在深度i处恰好有C(k,i)个节点，其中i=0,1,2,...,k。
// [性质四] 根的度数为k，它大于任何其它节点的度数。
// 注意：树的高度和深度是相同的。关于树的高度的概念，《算法导论》中只有一个节点的树的高度是0，
// 而"维基百科"中只有一个节点的树的高度是1。本文使用了《算法导论中》"树的高度和深度"的概念

// 二项堆通常被用来实现优先队列，它堆是指满足以下性质的二项树的集合：
// (01) 每棵二项树都满足最小堆性质。即，父节点的关键字 <= 它的孩子的关键字。
// (02) 不能有两棵或以上的二项树具有相同的度数(包括度数为0)。换句话说，具有度数k的二项树有0个或1个。

// 合并操作是二项堆的重点，二项堆的添加操作也是基于合并操作来实现的,通过下面两步合并两个二项堆
// 1.将两个二项堆的根链表合并成一个链表，合并后的新链表按照节点的度数单调递增排列
// 2.将新链表中的根节点度数相同的二项树连接起来，直到所有跟节点度数都不相同

#ifndef _BINOMIAL_HEAP_H_
#define _BINOMIAL_HEAP_H_

typedef int Type;

typedef struct _BinomialNode
{
	Type key;						// 键值
	int degree;						// 度数
	struct _BinomialNode *child;	// 左孩子
	struct _BinomialNode *parent;	// 父节点
	struct _BinomialNode *next;		// 兄弟节点
}BinomialNode, *BinomialHeap;

// 新建key对应的节点，并将其插入到二项堆中
BinomialNode* binomial_insert(BinomialHeap heap, Type key);

// 删除键值为key的节点，返回删除后的二项树
BinomialNode* binomial_delete(BinomialHeap heap, Type key);

// 将二项堆heap的键值oldkey更新为newkey
void binomial_update(BinomialHeap heap, Type oldkey, Type newkey);

// 合并二项堆：将h1，h2合并成一个堆，返回合并后的堆
BinomialNode* binomial_union(BinomialHeap h1, BinomialHeap h2);

// 在二项堆中查找键值为key的节点
BinomialNode* binomial_search(BinomialHeap heap, Type key);

// 获取二项堆中的最小节点
BinomialNode* binomial_minimum(BinomialHeap heap);

// 删除最小节点，返回删除节点后的二项堆
BinomialNode* binomial_extract_minimum(BinomialHeap heap);

// 打印二项堆
void binomial_print(BinomialHeap heap);

#endif // _BINOMIAL_HEAP_H_
