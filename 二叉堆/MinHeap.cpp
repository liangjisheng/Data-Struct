
/************************************************************************
 * C++实现二叉堆(最小堆)
 * author: 梁基圣
 * date: 20171112
************************************************************************/

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

template<class T>
class MinHeap
{
private:
	T *mHeap;			// 数据
	int mCapacity;		// 总的容量
	int mSize;			// 实际容量

private:
	// 最小堆的详向下调整算法
	void filterdown(int start, int end);
	// 最小堆的向上调整算法
	void filterup(int start);

public:
	MinHeap();
	MinHeap(int capacity);
	~MinHeap();

	int getIndex(T data);		// 返回data在二叉堆中的索引
	int remove(T data);			// 删除最小堆中的data,0:ok,-1:error
	int insert(T data);			// 将data插入到二叉堆中,0:ok,-1:error
	void print();				// 打印二叉堆
};

template<class T>
MinHeap<T>::MinHeap() { new (this)MinHeap(30); }

template<class T>
MinHeap<T>::MinHeap(int capacity)
{
	mSize = 0;
	mCapacity = capacity;
	mHeap = new T[mCapacity];
}

template<class T>
MinHeap<T>::~MinHeap()
{
	mSize = 0;
	mCapacity = 0;
	if(mHeap)
		delete [] mHeap;
	mHeap = NULL;
}

template<class T>
int MinHeap<T>::getIndex(T data)
{
	for (int i = 0; i < mSize; ++i)
		if(data == mHeap[i])
			return i;

	return -1;
}

/************************************************************************
 * 最下堆的向下调整算法
 * start: 被下调节点的起始位置(一般为0,表示从第一个开始)
 * end: 截止范围(一般为数组中最后一个元素的索引)
************************************************************************/
template<class T>
void MinHeap<T>::filterdown(int start, int end)
{
	int c = start;			// 当前节点的位置
	int l = 2 * c + 1;		// 左孩子的位置
	T tmp = mHeap[c];		// 当前节点的大小

	while(l <= end)
	{
		// l是左孩子,l + 1是右孩子
		// 左右两个孩子中选择较小的
		if(l < end && mHeap[l] > mHeap[l + 1])
			l++;

		if(tmp <= mHeap[l])
			break;
		else
		{
			mHeap[c] = mHeap[l];
			c = l;
			l = 2 * l + 1;
		}
	}

	mHeap[c] = tmp;
}

template<class T>
int MinHeap<T>::remove(T data)
{
	if(0 == mSize)
		return -1;

	int index = getIndex(data);
	if(-1 == index)
		return -1;

	mHeap[index] = mHeap[--mSize];		// 用最后的元素填补
	filterdown(index, mSize - 1);		// 从index号位置开始自上向下调整为最小堆

	return 0;
}

/************************************************************************
 * 最小堆的向上调整算法
 * start: 被上调节点的起始位置(一般为数组中最后一个元素的索引)
*************************************************************************/
template<class T>
void MinHeap<T>::filterup(int start)
{
	int c = start;				// 当前节点的位置
	int p = (c - 1) / 2;		// 父节点的位置
	T tmp = mHeap[c];			// 当前节点的大小

	while(c > 0)
	{
		if(mHeap[p] <= tmp)
			break;
		else
		{
			mHeap[c] = mHeap[p];
			c = p;
			p = (p - 1) / 2;
		}
	}

	mHeap[c] = tmp;
}

template<class T>
int MinHeap<T>::insert(T data)
{
	if(mSize == mCapacity)
		return -1;

	mHeap[mSize] = data;
	filterup(mSize);
	mSize++;

	return 0;
}

template<class T>
void MinHeap<T>::print()
{
	for (int i = 0; i < mSize; ++i)
		cout << mHeap[i] << ' ';
	cout << endl;
}


int main()
{
	int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
	int i, len=(sizeof(a)) / (sizeof(a[0])) ;
	MinHeap<int>* tree = new MinHeap<int>();

	cout << "== 依次添加: ";
	for (i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
		tree->insert(a[i]);
	}
	cout << endl;

	cout << "== 最小堆: ";
	tree->print();

	i = 15;
	tree->insert(i);
	cout << "== 添加元素: " << i << endl;
	cout << "== 最小堆: ";
	tree->print();

	i = 10;
	tree->remove(i);
	cout << "== 删除元素: " << i << endl;
	cout << "== 最小堆: ";
	tree->print();

	delete tree;

	system("pause");
	return 0;
}

