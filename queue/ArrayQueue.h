
// C++实现一：数组实现的队列，能存储任意类型的数据

#ifndef ARRAY_QUEUE_HXX
#define ARRAY_QUEUE_HXX

#include <iostream>
using namespace std;

template<class T>
class ArrayQueue
{
public:
	ArrayQueue();
	~ArrayQueue();

	void add(T t);
	T front();
	T pop();
	int size();
	int is_empty();

private:
	T *arr;
	int count;
};

template<class T>
ArrayQueue<T>::ArrayQueue()
{
	arr = new T[12];
	if(!arr)
		cout << "arr malloc error!" << endl;
	count = 0;
}

template<class T>
ArrayQueue<T>::~ArrayQueue()
{
	if(arr)
	{
		delete [] arr;
		arr = NULL;
	}
}

template<class T>
void ArrayQueue<T>::add(T t) { arr[count++] = t; }

template<class T>
T ArrayQueue<T>::front() { return arr[0]; }

template<class T>
T ArrayQueue<T>::pop()
{
	int i = 0;
	T ret = arr[0];
	count--;

	while(i++ < count)
		arr[i - 1] = arr[i];

	return ret;
}

template<class T>
int ArrayQueue<T>::size() { return count; }

template<class T>
int ArrayQueue<T>::is_empty() { return count == 0; }

#endif // ARRAY_QUEUE_HXX