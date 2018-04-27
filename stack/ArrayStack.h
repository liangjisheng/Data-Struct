
#ifndef ARRAY_STACK_HXX_
#define ARRAY_STACK_HXX_

// C++:����ʵ�ֵ�ջ,�ܴ洢�������͵�����
#include <iostream>
using namespace std;

template<class T>
class ArrayStack
{
public:
	ArrayStack();
	~ArrayStack();

	void push(T t);
	T peek();
	T pop();
	int size();
	int isEmpty();
private:
	T *arr;
	int count;
};

// ����ջ,Ĭ�ϴ�С��12
template<class T>
ArrayStack<T>::ArrayStack()
{
	arr = new T[12];
	if(!arr)
		cout << "arr malloc error!" << endl;
	count = 0;
}

template<class T>
ArrayStack<T>::~ArrayStack()
{
	if(arr)
	{
		delete [] arr;
		arr = NULL;
	}
}

template<class T>
void ArrayStack<T>::push(T t) { arr[count++] = t; }

template<class T>
T ArrayStack<T>::peek() { return arr[count - 1]; }

template<class T>
T ArrayStack<T>::pop() { return arr[--count]; }

template<class T>
int ArrayStack<T>::size() { return count; }

template<class T>
int ArrayStack<T>::isEmpty() { return size() == 0; }

#endif // ARRAY_STACK_HXX_