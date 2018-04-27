
/***********************************************************************
 * �ļ���: B-Tree.cpp
 * �ļ�����: B-Tree��ӿ�ʵ��
 * ����: ����ʥ 20171105
 * �汾�� 1.0
***********************************************************************/

#include "B-Tree.h"

using std::overflow_error;
using std::cin;

BTree::BTree() { head = NULL; }

// ����ؼ���K�ڽڵ�T�д��ڣ��򷵻عؼ���K���±�
// ��������ڣ��򷵻����һ��С��K�Ĺؼ��ֵ��±�(��Ҫ���ڲ���ʱ)
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
	if(!head)			// ��Ϊ��
		return false;

	Node* cur = head;
	bool bFound = false;
	int i = 0;

	// bFound�����������п���
	while(cur && !bFound)
	{
		i = search(cur, K);
		if(i > 0 && cur->key[i] == K)
		{
			// �ҵ��ڵ�ͽڵ��йؼ��ֵ��±�
			recNode = cur;
			recIdx = i;
			return true;
		}
		else
		{
			recNode = cur;				// ��¼��ǰ�ڵ㣬���㷵��
			recIdx = i;
			cur = cur->ptr[recIdx];		// ������һ���ڵ�
		}
	}

	return false;
}

/***********************************************************************
 * ��������: �ڽڵ�T�Ĺؼ��������в���һ���ؼ���K
 * ����˵��: T����Ľڵ㣬i�����λ�ã�K��ʾ����Ĺؼ���,rhs��ʾ�ؼ���K���ڵĽڵ�
***********************************************************************/
void BTree::insert(Node *& T, int i, KeyType K, Node* rhs)
{
	// �ѹؼ������������ƣ������µĹؼ���
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
 * ��������: ��T�ڵ���з���
 * ����˵��: rhsΪ�½��ڵ����ڱ����Ұ벿��,midKΪ�ؼ������е��м�ֵ
			 s��ʾ�ؼ������е��м�ֵ����
***********************************************************************/
bool BTree::split(Node *& T, int s, Node*& rhs, KeyType& midK)
{
	rhs = new Node;
	if(!rhs)
	{
		overflow_error;
		return false;
	}

	// ��T���ѣ�����rhs��T���ֵܽڵ㣬����ͬ�ĸ�ĸ
	rhs->parent = T->parent;

	midK = T->key[s];

	// ���ͨ����ͼ���Ե�֪��rhs��0�ź��ӵ�ָ�룬����t��s�Žڵ�ָ��
	rhs->ptr[0] = T->ptr[s];

	// ���ԭ����T��s�ź���ָ�룬���ڵ�rhs��0�ź���ָ�벻Ϊ�գ�����Ҫ�ı亢�ӵĵĸ��׽��
	if(rhs->ptr[0])
		rhs->ptr[0]->parent = rhs;
	T->ptr[s] = NULL;

	for (int i = 1; i <= M - s; ++i)
	{
		// �����ǰ��Ұ벿�ָ��Ƶ�rhs��
		rhs->key[i] = T->key[s + i]; T->key[s + i] = 0;
		rhs->ptr[i] = T->ptr[s + i]; T->ptr[s + i] = NULL;

		// �ı亢�ӵĸ��ڵ�
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
	// ���Ӳ�Ϊ��
	if(temp->ptr[0])
		temp->ptr[0]->parent = temp;

	temp->ptr[1] = rhs;
	// �Һ��Ӳ�Ϊ��
	if(temp->ptr[1])
		temp->ptr[1]->parent = temp;

	T = temp;
	return true;
}

// ����һ���ؼ���
bool BTree::insert_BTree(KeyType K)
{
	Node *curNode = NULL;
	int	preIdx = 0;

	if(searchKey_BTree(K, curNode, preIdx))
	{
		cout << "�ؼ����Ѿ�����" << endl;
		return false;
	}
	else
	{
		KeyType curk = K;
		Node *rhs = NULL;
		bool finished = false;
		while(!finished && curNode)
		{
			// �����Ƿ�Ϸ���ֱ���Ȳ���ղ��ҵ����Ǹ��ؼ���������
			insert(curNode, preIdx, curk, rhs);
			if(curNode->keynum < M)
				finished = true;
			else
			{
				int s = (M + 1) / 2;		// sΪ�м�ֵ�±�
				if(!split(curNode, s, rhs, curk))
					return false;			// ����ʧ�ܣ�ֱ�ӷ���
				if(curNode->parent == NULL)
					break;					// ���curNode�Ѿ��Ǹ��ڵ��ˣ������ֱ���˳�
				else
				{
					// ������Ǹ����׽ڵ�Ļ�����ʱcurkָ�����ԭ������ڵ��м�ֵ
					// ������Ҫ�͸��ڵ��ں�
					curNode = curNode->parent;
					preIdx = search(curNode, curk);
				}
			}
		}

		// ���headΪ���������߸��ڵ��Ѿ�����Ϊ�ڵ�curNode��rhs�ˣ���ʱ�϶��ǵ��˸��ڵ���
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
	// curIdx���Ϸ���ֱ�ӷ���
	if(curIdx < 0 || curIdx > curNode->keynum)
		return ;

	while(true)
	{
		// ˵�����ڷ�Ҷ�ӽڵ�
		if(curNode->ptr[curIdx - 1] && curNode->ptr[curIdx])
		{
			// ʹ������������С�Ĺؼ����滻��Ӧ��ǰ�Ĺؼ��֣�Ȼ��ɾ���Ǹ���С�Ĺؼ���
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

// ɾ����Ӧ�ؼ��ֺ�������Ҫ��ɾ����������е���
void BTree::DeleteBalance(Node* curNode)
{
	int lb = (int)M / 2;
	Node* parent = curNode->parent;

	// ɾ���ؼ��ֺ�ԭ���Ǹ��ڵ��Ѿ�������B-������СҪ����
	while(parent && curNode->keynum < lb)
	{
		int idx = 0;
		// �ҵ�curNode���丸�ڵ��е�λ��
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
		// �����ǰ�ڵ������ֵ�
		if(idx - 1 >= 0)
			lsilb = parent->ptr[idx - 1];
		// �����ǰ�ڵ������ֵ�
		if(idx + 1 <= parent->keynum)
			rsilb = parent->ptr[idx + 1];

		// ֻҪ���ֵܴ��ڣ�������rsilb->keynum > lb,����ɾ�����������2
		if(rsilb && rsilb->keynum > lb)
		{
			RotateLeft(parent, idx, curNode, rsilb);
			break;
		}
		else if(lsilb && lsilb->keynum > lb)	// ���ֵ�����
		{
			RotateRight(parent, idx, curNode, lsilb);
			break;
		}
		else
		{
			// ��������ֵܶ������㣬�Ǿ������3��
			if(lsilb)	// �ϲ������ֵ�
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
		// root is empty��ʱ��Ϊ��
		head = curNode->ptr[0];
		delete curNode;
	}
}

//����������ֵܴ��ڵ�����£���������rsilb->keynum > lb����������Ҫ�Ӱ�
//���ֵܽ���е���С�ؼ����ƶ������׽�㣬�����׽����С�ڸ����ֵܵĹؼ��ֵĹؼ���
//��Ҫ���Ƶ��ո�ɾ�����Ǹ������
void BTree::RotateLeft(Node* parent, int idx, Node* cur, Node* rsilb)
{
	//���׽����ĳ���������
	cur->key[cur->keynum + 1] = parent->key[idx + 1]; 
	cur->ptr[cur->keynum + 1] = rsilb->ptr[0];
	if (cur->ptr[cur->keynum + 1])
		cur->ptr[cur->keynum + 1]->parent = cur;    

	rsilb->ptr[0] = NULL;

	++cur->keynum;

	parent->key[idx + 1] = rsilb->key[1];
	rsilb->key[idx] = 0;
	//���ֵ�����һ����㵽���׽�㣬
	for (int i = 0; i <= rsilb->keynum; ++i) {//ɾ����ҵ��Ǹ����
		rsilb->key[i] = rsilb->key[i + 1];
		rsilb->ptr[i] = rsilb->ptr[i + 1];
	}
	rsilb->key[0] = 0;
	--rsilb->keynum;
}

//����������ֵܴ��ڵ�����£���������lsilb->keynum > lb����������Ҫ�Ӱ�
//���ֵܽ���е����ؼ����ƶ������׽�㣬�����׽���д��ڸ����ֵܵĹؼ��ֵĹؼ���
//��Ҫ���Ƶ��ո�ɾ�����Ǹ������
void BTree::RotateRight(Node *parent, int idx, Node* cur, Node* lsilb)
{
	//��Ϊ������߲���
	for (int i = cur->keynum; i >= 0; --i) {//��Ϊ��ߵĶ����ұ�С������Ҫ�����һ��λ��
		cur->key[i + 1] = cur->key[i];
		cur->ptr[i + 1] = cur->ptr[i];
	}
	//�ڵ�һ��λ�ò��븸�׽�����������Ľ��
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
	//����ʵ�ֶ�����lsilb�Ϻϲ����������Ȱ�cur�е�ʣ�ಿ�֣�ȫ���ϵ����ֵ��и���
	for (int i = 0; i <= cur->keynum; ++i) {
		lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
		lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
		if (lsilb->ptr[lsilb->keynum + 1 + i])
			lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
	}
	//Ȼ���ٰѸ��׽���е�idx��Ӧ��������ӵ����ֵ�
	lsilb->key[lsilb->keynum + 1] = parent->key[idx];
	lsilb->keynum = lsilb->keynum + cur->keynum + 1;
	delete cur;
	//Ȼ��������ǵĸ��׽������
	for (int i = idx; i <= parent->keynum; ++i) {
		parent->key[i] = parent->key[i + 1];
		parent->ptr[i] = parent->ptr[i + 1];
	}//end for.
	--parent->keynum;
}

void BTree::Destroy(Node * & T) 
{	//�Ƿ�ռ�
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
