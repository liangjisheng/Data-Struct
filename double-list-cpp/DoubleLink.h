
// C++实现双向链表

#ifndef DOUBLE_LINK_HXX_
#define DOUBLE_LINK_HXX_

#include <iostream>
using namespace std;

template<class T>
struct DNode
{
public:
	T value;
	DNode *prev;
	DNode *next;
public:
	DNode() {}
	DNode(T t, DNode *prev, DNode *next)
	{
		this->value = t;
		this->prev = prev;
		this->next = next;
	}
};

template<class T>
class DoubleLink
{
public:
	DoubleLink();
	~DoubleLink();

	int size();
	int is_empty();

	T get(int index);
	T get_first();
	T get_last();

	int insert(int index, T t);
	int insert_first(T t);
	int append_last(T t);

	int del(int index);
	int delete_first();
	int delete_last();

private:
	int count;
	DNode<T> *phead;
private:
	DNode<T> *get_node(int index);
};


template<class T>
DoubleLink<T>::DoubleLink() : count(0)
{
	// 创建表头,表头没有任何数据
	phead = new DNode<T>();
	phead->prev = phead->next = phead;
}

template<class T>
DoubleLink<T>::~DoubleLink()
{
	DNode<T> *ptmp;
	DNode<T> *pnode = phead->next;
	while(pnode != phead)
	{
		ptmp = pnode;
		pnode = pnode->next;
		delete ptmp;
	}

	delete phead;
	phead = NULL;
}

template<class T>
int DoubleLink<T>::size() { return count; }

template<class T>
int DoubleLink<T>::is_empty() { return count == 0; }

template<class T>
DNode<T>* DoubleLink<T>::get_node(int index)
{
	if(index < 0 || index >= count)
	{
		cout << "get node failed! the index in out of bound!" << endl;
		return NULL;
	}

	// 正向查找
	if(index <= count / 2)
	{
		int i = 0;
		DNode<T>* pindex = phead->next;
		while(i++ < index)
			pindex = pindex->next;

		return pindex;
	}

	// 反向查找
	int j = 0;
	int rindex = count - index - 1;
	DNode<T>* prindex = phead->prev;
	while(j++ < rindex)
		prindex = prindex->prev;

	return prindex;
}

template<class T>
T DoubleLink<T>::get(int index) { return get_node(index)->value; }

template<class T>
T DoubleLink<T>::get_first() { return get_node(0)->value; }

template<class T>
T DoubleLink<T>::get_last() { return get_node(count - 1)->value; }

template<class T>
int DoubleLink<T>::insert(int index, T t)
{
	if(0 == index)
		return insert_first(t);

	DNode<T>* pindex = get_node(index);
	DNode<T>* pnode = new DNode<T>(t, pindex->prev, pindex);
	pindex->prev->next = pnode;
	pindex->prev = pnode;
	count++;

	return 0;
}

template<class T>
int DoubleLink<T>::insert_first(T t)
{
	DNode<T>* pnode = new DNode<T>(t, phead, phead->next);
	phead->next->prev = pnode;
	phead->next = pnode;
	count++;

	return 0;
}

template<class T>
int DoubleLink<T>::append_last(T t)
{
	DNode<T>* pnode = new DNode<T>(t, phead->prev, phead);
	phead->prev->next = pnode;
	phead->prev = pnode;
	count++;

	return 0;
}

template<class T>
int DoubleLink<T>::del(int index)
{
	DNode<T>* pindex = get_node(index);
	pindex->prev->next = pindex->next;
	pindex->next->prev = pindex->prev;
	delete pindex;
	count--;

	return 0;
}

template<class T>
int DoubleLink<T>::delete_first() { return del(0); }

template<class T>
int DoubleLink<T>::delete_last() { return del(count - 1); }

#endif // DOUBLE_LINK_HXX_