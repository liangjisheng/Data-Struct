
/***********************************************************************
 * 文件名: B-Tree.cpp
 * 文件描述: B-Tree类接口实现
 * 作者: 梁基圣 20171105
 * 版本： 1.0
***********************************************************************/

#include "B-Tree.h"

using std::overflow_error;
using std::cin;

BTree::BTree() { head = NULL; }

// 如果关键字K在节点T中存在，则返回关键字K的下标
// 如果不存在，则返回最后一个小于K的关键字的下标(主要用在插入时)
int BTree::search(Node *& T, KeyType K)
{
	int i = 0;
	for (int j = 1; j <= T->keynum; ++j)
		if(T->key[j] <= K)
			i = j;

	return i;
}

bool BTree::searchKey_BTree(KeyType K, Node*& recNode, int& recIdx)
{
	if(!head)			// 树为空
		return false;

	Node* cur = head;
	bool bFound = false;
	int i = 0;

	// bFound在这里好像可有可无
	while(cur && !bFound)
	{
		i = search(cur, K);
		if(i > 0 && cur->key[i] == K)
		{
			// 找到节点和节点中关键字的下标
			recNode = cur;
			recIdx = i;
			return true;
		}
		else
		{
			recNode = cur;				// 记录当前节点，方便返回
			recIdx = i;
			cur = cur->ptr[recIdx];		// 查找下一个节点
		}
	}

	return false;
}

/***********************************************************************
 * 功能描述: 在节点T的关键字序列中插入一个关键字K
 * 参数说明: T插入的节点，i插入的位置，K表示插入的关键字,rhs表示关键字K所在的节点
***********************************************************************/
void BTree::insert(Node *& T, int i, KeyType K, Node* rhs)
{
	// 把关键字序列往后移，插入新的关键字
	for (int j = T->keynum - 1; j >= i + 1; --j)
	{
		T->key[j + 1] = T->key[j];
		T->ptr[j + 1] = T->ptr[j];
	}

	T->key[i + 1] = K;
	T->ptr[i + 1] = rhs;
	++T->keynum;
}

/***********************************************************************
 * 功能描述: 对T节点进行分裂
 * 参数说明: rhs为新建节点用于保存右半部分,midK为关键字序列的中间值
			 s表示关键字序列的中间值索引
***********************************************************************/
bool BTree::split(Node *& T, int s, Node*& rhs, KeyType& midK)
{
	rhs = new Node;
	if(!rhs)
	{
		overflow_error;
		return false;
	}

	// 把T分裂，所以rhs是T的兄弟节点，有相同的父母
	rhs->parent = T->parent;

	midK = T->key[s];

	// 这个通过画图可以得知，rhs的0号孩子的指针，就是t的s号节点指针
	rhs->ptr[0] = T->ptr[s];

	// 如果原来的T的s号孩子指针，现在的rhs的0号孩子指针不为空，则需要改变孩子的的父亲结点
	if(rhs->ptr[0])
		rhs->ptr[0]->parent = rhs;
	T->ptr[s] = NULL;

	for (int i = 1; i <= M - s; ++i)
	{
		// 现在是把右半部分复制到rhs中
		rhs->key[i] = T->key[s + i]; T->key[s + i] = 0;
		rhs->ptr[i] = T->ptr[s + i]; T->ptr[s + i] = NULL;

		// 改变孩子的父节点
		if(rhs->ptr[i])
			rhs->ptr[i]->parent = rhs;
	}

	rhs->keynum = M - s;
	T->keynum = s - 1;
	
	return true;
}

bool BTree::newroot(Node*& T, Node*& lhs, KeyType midK, Node*& rhs)
{
	Node* temp = new Node;
	if(!temp)
	{
		overflow_error;
		return false;
	}

	temp->keynum = 1;
	temp->key[1] = midK;

	temp->ptr[0] = lhs;
	// 左孩子不为空
	if(temp->ptr[0])
		temp->ptr[0]->parent = temp;

	temp->ptr[1] = rhs;
	// 右孩子不为空
	if(temp->ptr[1])
		temp->ptr[1]->parent = temp;

	T = temp;
	return true;
}

// 插入一个关键字
bool BTree::insert_BTree(KeyType K)
{
	Node *curNode = NULL;
	int	preIdx = 0;

	if(searchKey_BTree(K, curNode, preIdx))
	{
		cout << "关键字已经存在" << endl;
		return false;
	}
	else
	{
		KeyType curk = K;
		Node *rhs = NULL;
		bool finished = false;
		while(!finished && curNode)
		{
			// 不管是否合法，直接先插入刚才找到的那个关键字序列中
			insert(curNode, preIdx, curk, rhs);
			if(curNode->keynum < M)
				finished = true;
			else
			{
				int s = (M + 1) / 2;		// s为中间值下标
				if(!split(curNode, s, rhs, curk))
					return false;			// 分裂失败，直接返回
				if(curNode->parent == NULL)
					break;					// 如果curNode已经是根节点了，则可以直接退出
				else
				{
					// 如果有那个父亲节点的话，此时curk指向的是原来这个节点中间值
					// 所以需要和父节点融合
					curNode = curNode->parent;
					preIdx = search(curNode, curk);
				}
			}
		}

		// 如果head为空树，或者根节点已经分裂为节点curNode和rhs了，此时肯定是到了根节点了
		if(!finished && !newroot(head, curNode, curk, rhs))
		{
			cout << "failed to create new root" << endl;
			exit(EXIT_FAILURE);
		}
	}

	return true;
}

bool BTree::Delete_BTree(KeyType K)
{
	Node *curNode = NULL;
	int curIdx = 0;
	if(searchKey_BTree(K, curNode, curIdx))
	{
		Delete(curNode, curIdx);
		return true;
	}
	else
		return false;
}

void BTree::Delete(Node* curNode, int curIdx)
{
	// curIdx不合法，直接返回
	if(curIdx < 0 || curIdx > curNode->keynum)
		return ;

	while(true)
	{
		// 说明处于非叶子节点
		if(curNode->ptr[curIdx - 1] && curNode->ptr[curIdx])
		{
			// 使用右子树中最小的关键字替换对应当前的关键字，然后删除那个最小的关键字
			Node *p1 = curNode->ptr[curIdx];
			while(p1->ptr[0])
				p1 = p1->ptr[0];

			int res = p1->key[1];
			Delete_BTree(p1->key[1]);
			curNode->key[curIdx] = res;
			break;
		}
		else if(!curNode->ptr[curIdx - 1] && !curNode->ptr[curIdx])
		{
			// is leaf
			for (int i = curIdx; i <= curNode->keynum; ++i)
				curNode->key[i] = curNode->key[i + 1];
				// all ptr are NULL, no need to move

			--curNode->keynum;
			DeleteBalance(curNode);
			break;
		}
		else
			cout << "error" << endl;
	}
}

// 删除对应关键字后，我们需要对删除后的树进行调整
void BTree::DeleteBalance(Node* curNode)
{
	int lb = (int)M / 2;
	Node* parent = curNode->parent;

	// 删除关键字后，原来那个节点已经不符合B-树的最小要求了
	while(parent && curNode->keynum < lb)
	{
		int idx = 0;
		// 找到curNode在其父节点中的位置
		for (int i = 0; i <= parent->keynum; ++i)
		{
			if(parent->ptr[i] == curNode)
			{
				idx = i;
				break;
			}
		}

		Node* lsilb = NULL;
		Node* rsilb = NULL;
		// 如果当前节点有左兄弟
		if(idx - 1 >= 0)
			lsilb = parent->ptr[idx - 1];
		// 如果当前节点有右兄弟
		if(idx + 1 <= parent->keynum)
			rsilb = parent->ptr[idx + 1];

		// 只要右兄弟存在，且满足rsilb->keynum > lb,就是删除调整的情况2
		if(rsilb && rsilb->keynum > lb)
		{
			RotateLeft(parent, idx, curNode, rsilb);
			break;
		}
		else if(lsilb && lsilb->keynum > lb)	// 左兄弟满足
		{
			RotateRight(parent, idx, curNode, lsilb);
			break;
		}
		else
		{
			// 如果左右兄弟都不满足，那就是情况3了
			if(lsilb)	// 合并到左兄弟
				Merge(parent, idx, lsilb, curNode);
			else
				Merge(parent, idx + 1, curNode, rsilb);

			// potentially causing deficiency of parent
			curNode = parent;
			parent = curNode->parent;
		}
	}

	if(curNode->keynum == 0)
	{
		// root is empty此时树为空
		head = curNode->ptr[0];
		delete curNode;
	}
}

//这个是在右兄弟存在的情况下，而且满足rsilb->keynum > lb，则我们需要从把
//右兄弟结点中的最小关键字移动到父亲结点，而父亲结点中小于该右兄弟的关键字的关键字
//就要下移到刚刚删除的那个结点中
void BTree::RotateLeft(Node* parent, int idx, Node* cur, Node* rsilb)
{
	//父亲结点中某个结点下移
	cur->key[cur->keynum + 1] = parent->key[idx + 1]; 
	cur->ptr[cur->keynum + 1] = rsilb->ptr[0];
	if (cur->ptr[cur->keynum + 1])
		cur->ptr[cur->keynum + 1]->parent = cur;    

	rsilb->ptr[0] = NULL;

	++cur->keynum;

	parent->key[idx + 1] = rsilb->key[1];
	rsilb->key[idx] = 0;
	//右兄弟上移一个结点到父亲结点，
	for (int i = 0; i <= rsilb->keynum; ++i) {//删除最靠右的那个结点
		rsilb->key[i] = rsilb->key[i + 1];
		rsilb->ptr[i] = rsilb->ptr[i + 1];
	}
	rsilb->key[0] = 0;
	--rsilb->keynum;
}

//这个是在左兄弟存在的情况下，而且满足lsilb->keynum > lb，则我们需要从把
//左兄弟结点中的最大关键字移动到父亲结点，而父亲结点中大于该左兄弟的关键字的关键字
//就要下移到刚刚删除的那个结点中
void BTree::RotateRight(Node *parent, int idx, Node* cur, Node* lsilb)
{
	//因为是在左边插入
	for (int i = cur->keynum; i >= 0; --i) {//因为左边的都比右边小，所以要插入第一个位置
		cur->key[i + 1] = cur->key[i];
		cur->ptr[i + 1] = cur->ptr[i];
	}
	//在第一个位置插入父亲结点下移下来的结点
	cur->key[1] = parent->key[idx];
	cur->ptr[0] = lsilb->ptr[lsilb->keynum];

	if (cur->ptr[0])
		cur->ptr[0]->parent = cur;
	lsilb->ptr[lsilb->keynum] = NULL;
	++cur->keynum;

	// from lsilb to parent.
	parent->key[idx] = lsilb->key[lsilb->keynum];
	lsilb->key[lsilb->keynum] = 0;
	--lsilb->keynum;
}

void BTree::Merge(Node* parent, int idx, Node* lsilb, Node* cur)
{
	//函数实现都是往lsilb上合并，首先是先把cur中的剩余部分，全部合到左兄弟中个，
	for (int i = 0; i <= cur->keynum; ++i) {
		lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
		lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
		if (lsilb->ptr[lsilb->keynum + 1 + i])
			lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
	}
	//然后再把父亲结点中的idx对应的内容添加到左兄弟
	lsilb->key[lsilb->keynum + 1] = parent->key[idx];
	lsilb->keynum = lsilb->keynum + cur->keynum + 1;
	delete cur;
	//然后更新我们的父亲结点内容
	for (int i = idx; i <= parent->keynum; ++i) {
		parent->key[i] = parent->key[i + 1];
		parent->ptr[i] = parent->ptr[i + 1];
	}//end for.
	--parent->keynum;
}

void BTree::Destroy(Node * & T) 
{	//是否空间
	if (!T)
		return;

	for (int i = 0; i <= T->keynum; ++i)
		Destroy(T->ptr[i]);
	delete T;
	T = NULL;
	return;
}

void BTree::WalkThrough(Node * &T) {
	if (!T) return;
	static int depth = 0;
	++depth;
	int index = 0;

	bool running = true;

	while (running) {
		int ans = 0;
		if (index == 0) {
			ans = 2;
		}
		else {
			cout << "Cur depth: " << depth << endl;
			cout << "Cur Pos: " << (void*)T << ";  "
				<< "Keynum: " << T->keynum << "; " << endl;
			cout << "Index: " << index << ";  Key: " << T->key[index] << endl;

			do {
				cout << "1.Prev Key; 2.Next Key; 3.Deepen Left; 4.Deepen Right; 5.Backup" << endl;
				cin >> ans;
				if (1 <= ans && ans <= 5)
					break;
			} while (true);
		}


		switch (ans) {
		case 1:
			if (index == 1)
				cout << "Failed." << endl;
			else
				--index;
			break;
		case 2:
			if (index == T->keynum)
				cout << "Failed" << endl;
			else
				++index;
			break;
		case 4:
			if (index > 0 && T->ptr[index])
				WalkThrough(T->ptr[index]);
			else
				cout << "Failed" << endl;
			break;
		case 3:
			if (index > 0 && T->ptr[index - 1])
				WalkThrough(T->ptr[index - 1]);
			else
				cout << "Failed" << endl;
			break;
		case 5:
			running = false;
			break;
		}//endsw
	}//endw

	--depth;
}

Node * BTree::gethead() { return this->head; }
