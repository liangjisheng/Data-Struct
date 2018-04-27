
// ∂‘≥∆æÿ’Û—πÀı¥Ê¥¢
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* a, size_t n);
	virtual ~SymmetricMatrix();

	T& Access(size_t i, size_t j);
	void Display();

private:
	T* _a;
	size_t _n;
};

template<class T>
SymmetricMatrix<T>::SymmetricMatrix(T* a, size_t n)
{
	_a = new T[n * (n + 1) / 2];
	_n = n;
	size_t index = 0;

	for(size_t i = 0; i < n; i++)
	{
		for(size_t j = 0; j <= i; j++)
			_a[index++] = a[i * n + j];
	}
}

template<class T>
SymmetricMatrix<T>::~SymmetricMatrix()
{
	if(_a)
		delete [] _a;
	_a = NULL;
}


template<class T>
T& SymmetricMatrix<T>::Access(size_t i, size_t j)
{
	if(i >= j)
		return _a[i * (i + 1) / 2 + j];
	else
		return _a[j * (j + 1) / 2 + i];
}

template<class T>
void SymmetricMatrix<T>::Display()
{
	for(size_t i = 0; i < _n; i++)
	{
		for(size_t j = 0; j < _n; j++)
			cout << Access(i, j) << ' ';
		cout << endl;
	}
	cout << endl;
}


void TestSymmetricMatrix()
{
	int a[5][5] = 
	{
		{0, 1, 2, 3, 4},
		{1, 0, 1, 2, 3},
		{2, 1, 0, 1, 2},
		{3, 2, 1, 0, 1},
		{4, 3, 2, 1, 0},
	};

	SymmetricMatrix<int> s((int*)a, 5);
	s.Display();
}


int main()
{
	TestSymmetricMatrix();

	system("pause");
	return 0;
}