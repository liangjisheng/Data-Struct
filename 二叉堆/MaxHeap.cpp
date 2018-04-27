
/************************************************************************
 * C++实现二叉堆(最大堆)
 * author: 梁基圣
 * date: 20171112
************************************************************************/

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

template<class T>
class MaxHeap
{
private:
	T *mHeap;				// 数据
	int mCapacity;			// 总容量
	int mSize;				// 实际容量

private:
	// 最大堆的向下调整算法
	void filterdown(int start, int end);
	// 最大堆的向上调整算法(从start开始向上直到0,调整堆)
	void filterup(int start);
public:
	MaxHeap();
	MaxHeap(int capacity);
	~MaxHeap();

	int getIndex(T data);			// 返回data在二叉堆中的索引
	int remove(T data);				// 删除最大堆中的data,0:成功,-1失败
	int insert(T data);				// 将data插入到二叉堆中,0:成功,-1失败
	void print();					// 打印二叉堆
};


template<class T>
MaxHeap<T>::MaxHeap() { new (this)MaxHeap(30); }

template<class T>
MaxHeap<T>::MaxHeap(int capacity)
{
	mSize = 0;
	mCapacity = capacity;
	mHeap = new T[mCapacity];
}

template<class T>
MaxHeap<T>::~MaxHeap()
{
	mSize = 0;
	mCapacity = 0;
	if(mHeap)
		delete [] mHeap;
	mHeap = NULL;
}

template<class T>
int MaxHeap<T>::getIndex(T data)
{
	for (int i = 0; i < mSize; ++i)
		if(data == mHeap[i])
			return i;

	return -1;
}

template<class T>
void MaxHeap<T>::filterdown(int start, int end)
{
	int c = start;				// 当前节点的位置
	int l = 2 * c + 1;			// 左孩子的位置
	T tmp = mHeap[c];			// 当前节点的大小

	while(l <= end)
	{
		// l是左孩子,l + 1是右孩子
		// 左右孩子中选择较大的
		if(l < end && mHeap[l] < mHeap[l + 1])
			l++;
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
int MaxHeap<T>::remove(T data)
{
	if(0 == mSize)			// 堆空,返回-1
		return -1;

	int index = getIndex(data);
	if(-1 == index)
		return -1;

	mHeap[index] = mHeap[--mSize];			// 用最后元素填补
	filterdown(index, mSize - 1);			// 从index位置开始自上向下调整为最大堆

	return 0;
}

template<class T>
void MaxHeap<T>::filterup(int start)
{
	int c = start;				// 当前节点的位置
	int p = (c - 1) / 2;		// 父节点的位置
	T tmp = mHeap[c];			// 当前节点的大小

	while(c > 0)
	{
		if(mHeap[p] >= tmp)
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
int MaxHeap<T>::insert(T data)
{
	if(mSize == mCapacity)			// 堆满,返回-1
		return -1;

	mHeap[mSize] = data;			// 将数据插在末尾
	filterup(mSize);				// 向上调整堆
	mSize++;

	return 0;
}

template<class T>
void MaxHeap<T>::print()
{
	for (int i = 0; i < mSize; ++i)
		cout << mHeap[i] << ' ';
	cout << endl;
}


int main()
{
	int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
	int i, len = sizeof(a) / sizeof(a[0]);
	MaxHeap<int>* tree = new MaxHeap<int>();

	cout << "== 依次添加: ";
	for (i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
		tree->insert(a[i]);
	}

	cout << endl;
	cout << "== 最大堆: ";
	tree->print();

	i = 85;
	tree->insert(i);
	cout << "== 添加元素: " << i << endl;
	cout << "== 最大堆: ";
	tree->print();

	i = 90;
	tree->remove(i);
	cout << "== 删除元素: " << i << endl;
	cout << "== 最大堆: ";
	tree->print();

	system("pause");
	return 0;
}

