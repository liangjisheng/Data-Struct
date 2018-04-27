
/************************************************************************
 * C++ʵ�ֶ����(��С��)
 * author: ����ʥ
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
	T *mHeap;			// ����
	int mCapacity;		// �ܵ�����
	int mSize;			// ʵ������

private:
	// ��С�ѵ������µ����㷨
	void filterdown(int start, int end);
	// ��С�ѵ����ϵ����㷨
	void filterup(int start);

public:
	MinHeap();
	MinHeap(int capacity);
	~MinHeap();

	int getIndex(T data);		// ����data�ڶ�����е�����
	int remove(T data);			// ɾ����С���е�data,0:ok,-1:error
	int insert(T data);			// ��data���뵽�������,0:ok,-1:error
	void print();				// ��ӡ�����
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
 * ���¶ѵ����µ����㷨
 * start: ���µ��ڵ����ʼλ��(һ��Ϊ0,��ʾ�ӵ�һ����ʼ)
 * end: ��ֹ��Χ(һ��Ϊ���������һ��Ԫ�ص�����)
************************************************************************/
template<class T>
void MinHeap<T>::filterdown(int start, int end)
{
	int c = start;			// ��ǰ�ڵ��λ��
	int l = 2 * c + 1;		// ���ӵ�λ��
	T tmp = mHeap[c];		// ��ǰ�ڵ�Ĵ�С

	while(l <= end)
	{
		// l������,l + 1���Һ���
		// ��������������ѡ���С��
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

	mHeap[index] = mHeap[--mSize];		// ������Ԫ���
	filterdown(index, mSize - 1);		// ��index��λ�ÿ�ʼ�������µ���Ϊ��С��

	return 0;
}

/************************************************************************
 * ��С�ѵ����ϵ����㷨
 * start: ���ϵ��ڵ����ʼλ��(һ��Ϊ���������һ��Ԫ�ص�����)
*************************************************************************/
template<class T>
void MinHeap<T>::filterup(int start)
{
	int c = start;				// ��ǰ�ڵ��λ��
	int p = (c - 1) / 2;		// ���ڵ��λ��
	T tmp = mHeap[c];			// ��ǰ�ڵ�Ĵ�С

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

	cout << "== �������: ";
	for (i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
		tree->insert(a[i]);
	}
	cout << endl;

	cout << "== ��С��: ";
	tree->print();

	i = 15;
	tree->insert(i);
	cout << "== ���Ԫ��: " << i << endl;
	cout << "== ��С��: ";
	tree->print();

	i = 10;
	tree->remove(i);
	cout << "== ɾ��Ԫ��: " << i << endl;
	cout << "== ��С��: ";
	tree->print();

	delete tree;

	system("pause");
	return 0;
}

