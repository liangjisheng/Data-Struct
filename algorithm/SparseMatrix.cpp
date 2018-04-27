
// 稀疏矩阵3元组的压缩存储,{row, col, value}三元组存储每一个有效数据
// 按矩阵中的位置,以行优先级先后顺序依次存放

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

template<class T>
struct Triple
{
	Triple(size_t r, size_t c, T& value) : _r(r), _c(c), _value(value) {}
	Triple() {}

	T _value;
	size_t _r;
	size_t _c;
};

template<class T>
class SparseMatrix
{
public:
	SparseMatrix();
	SparseMatrix(T* a, size_t row, size_t col, const T& invalid);

	void Display();
	SparseMatrix<T> Transport();		// 矩阵转置
	SparseMatrix<T> FastTransport();	// 快速转置矩阵

private:
	vector<Triple<T> > _a;	// 有效值
	size_t _row;
	size_t _col;
	T _invalid;				// 非法值
};


template<class T>
SparseMatrix<T>::SparseMatrix() {}

template<class T>
SparseMatrix<T>::SparseMatrix(T* a, size_t row, size_t col, const T& invalid)
	: _a(NULL), _row(row), _col(col), _invalid(invalid)
{
	for(size_t i = 0; i < row; i++)
	{
		for(size_t j = 0; j < col; j++)
		{
			if(a[i * col + j] != invalid)
				_a.push_back(Triple<T>(i, j, a[i * col + j]));
		}
	}
}

template<class T>
void SparseMatrix<T>::Display()
{
	size_t index = 0;
	for(size_t i = 0; i < _row; i++)
	{
		for(size_t j = 0; j < _col; j++)
		{
			if(index < _a.size() && _a[index]._r == i && _a[index]._c == j)
				cout << _a[index++]._value << ' ';
			else
				cout << _invalid << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Transport()
{
	SparseMatrix<T> st;
	st._row = _col;
	st._col = _row;
	st._invalid = _invalid;
	st._a.reserve(_a.size());

	for(size_t i = 0; i < _col; i++)
	{
		size_t index = 0;
		while(index < _a.size())
		{
			if(_a[index]._c == i)
			{
				Triple<T> tmp(_a[index]._c, _a[index]._r, _a[index]._value);
				st._a.push_back(tmp);
			}
			index++;
		}
	}

	return st;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::FastTransport()
{
	SparseMatrix<T> fast;
	fast._row = _col;
	fast._col = _row;
	fast._invalid = _invalid;
	fast._a.resize(_a.size());

	// 统计每列中的合法值的个数
	int *count = new int[_col];
	memset(count, 0, sizeof(int) * _col);
	for(size_t i = 0; i < _a.size(); i++)
		++count[_a[i]._c];

	cout << "valid count in cols: ";
	for(size_t i = 0; i < _col; i++)
		cout << count[i] << ' ';
	cout << endl;

	// 统计每列中的第一个合法元素在转置后的三元组顺序表中的索引
	int *start = new int[_col];
	memset(start, 0, sizeof(int) * _col);
	start[0] = 0;
	for(size_t i = 1; i < _col; i++)
		start[i] = start[i - 1] + count[i - 1];

	// output
	cout << "Before transport start index is: ";
	for(size_t i = 0; i < _col; i++)
		cout << start[i] << ' ';
	cout << endl;

	for(size_t i = 0; i < _a.size(); i++)
	{
		size_t tmp = start[_a[i]._c];
		fast._a[tmp]._r = _a[i]._c;
		fast._a[tmp]._c = _a[i]._r;
		fast._a[tmp]._value = _a[i]._value;
		++start[_a[i]._c];
	}

	// output
	cout << "After transport strat index is: ";
	for(size_t i = 0; i < _col; i++)
		cout << start[i] << ' ';
	cout << endl;

	return fast;
}


void TestSparseMatrix()
{
	int arr[6][5] = 
	{
		{1, 0, 3, 0, 5},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{2, 0, 4, 0, 6},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	};

	SparseMatrix<int> s1((int*)arr, 6, 5, 0);
	s1.Display();

	cout << "General transport:" << endl;
	SparseMatrix<int> s2;
	s2 = s1.Transport();
	s2.Display();

	cout << "Fast transport:" << endl;
	SparseMatrix<int> s3;
	s3 = s1.FastTransport();
	s3.Display();
}


int main()
{
	TestSparseMatrix();

	system("pause");
	return 0;
}
