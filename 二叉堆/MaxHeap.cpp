
/************************************************************************
 * C++ʵ�ֶ����(����)
 * author: ����ʥ
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
	T *mHeap;				// ����
	int mCapacity;			// ������
	int mSize;				// ʵ������

private:
	// ���ѵ����µ����㷨
	void filterdown(int start, int end);
	// ���ѵ����ϵ����㷨(��start��ʼ����ֱ��0,������)
	void filterup(int start);
public:
	MaxHeap();
	MaxHeap(int capacity);
	~MaxHeap();

	int getIndex(T data);			// ����data�ڶ�����е�����
	int remove(T data);				// ɾ�������е�data,0:�ɹ�,-1ʧ��
	int insert(T data);				// ��data���뵽�������,0:�ɹ�,-1ʧ��
	void print();					// ��ӡ�����
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
	int c = start;				// ��ǰ�ڵ��λ��
	int l = 2 * c + 1;			// ���ӵ�λ��
	T tmp = mHeap[c];			// ��ǰ�ڵ�Ĵ�С

	while(l <= end)
	{
		// l������,l + 1���Һ���
		// ���Һ�����ѡ��ϴ��
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
	if(0 == mSize)			// �ѿ�,����-1
		return -1;

	int index = getIndex(data);
	if(-1 == index)
		return -1;

	mHeap[index] = mHeap[--mSize];			// �����Ԫ���
	filterdown(index, mSize - 1);			// ��indexλ�ÿ�ʼ�������µ���Ϊ����

	return 0;
}

template<class T>
void MaxHeap<T>::filterup(int start)
{
	int c = start;				// ��ǰ�ڵ��λ��
	int p = (c - 1) / 2;		// ���ڵ��λ��
	T tmp = mHeap[c];			// ��ǰ�ڵ�Ĵ�С

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
	if(mSize == mCapacity)			// ����,����-1
		return -1;

	mHeap[mSize] = data;			// �����ݲ���ĩβ
	filterup(mSize);				// ���ϵ�����
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

	cout << "== �������: ";
	for (i = 0; i < len; ++i)
	{
		cout << a[i] << ' ';
		tree->insert(a[i]);
	}

	cout << endl;
	cout << "== ����: ";
	tree->print();

	i = 85;
	tree->insert(i);
	cout << "== ���Ԫ��: " << i << endl;
	cout << "== ����: ";
	tree->print();

	i = 90;
	tree->remove(i);
	cout << "== ɾ��Ԫ��: " << i << endl;
	cout << "== ����: ";
	tree->print();

	system("pause");
	return 0;
}

