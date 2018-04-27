
// ϡ��������
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

enum Status{ERROR, OK} status;

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
	SparseMatrix<T> Transport();		// ����ת��
	SparseMatrix<T> FastTransport();	// ����ת�þ���
	SparseMatrix<T> Multiply(const SparseMatrix<T>& src);

private:
	vector<Triple<T> > _a;		// ��Чֵ
	size_t _row;
	size_t _col;
	T _invalid;					// �Ƿ�ֵ
	vector<size_t> vecrcount;	// ÿ�з�0Ԫ�ĸ���
	vector<size_t> vecrpos;		// ÿ�е�һ����0Ԫ����Ԫ���е�����
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

	// ͳ��ÿ���кϷ�ֵ�ĸ���
	vecrcount.resize(row);
	for(size_t i = 0; i < _a.size(); i++)
		vecrcount[_a[i]._r]++;

	vecrpos.push_back(0);		// ��һ����0Ԫ����Ԫ����е�����Ϊ0
	// ͳ��ÿ���е�һ����0Ԫ����Ԫ����е�����
	for(size_t i = 1; i < row; i++)
		vecrpos.push_back(vecrpos[i - 1] + vecrcount[i - 1]);
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

	// ͳ��ÿ���еĺϷ�ֵ�ĸ���
	int *count = new int[_col];
	memset(count, 0, sizeof(int) * _col);
	for(size_t i = 0; i < _a.size(); i++)
		++count[_a[i]._c];

	cout << "valid count in cols: ";
	for(size_t i = 0; i < _col; i++)
		cout << count[i] << ' ';
	cout << endl;

	// ͳ��ÿ���еĵ�һ���Ϸ�Ԫ����ת�ú����Ԫ��˳����е�����
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
		// ��������1��Ϊ�˵õ�ԭ����_a[i]._c���е���һ���Ϸ�Ԫ��ֵ
		++start[_a[i]._c];
	}

	// output
	cout << "After transport strat index is: ";
	for(size_t i = 0; i < _col; i++)
		cout << start[i] << ' ';
	cout << endl;

	return fast;
}

template<class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(const SparseMatrix<T>& src)
{
	SparseMatrix<T> res;
	res._row = _row;
	res._col = src._col;
	res._invalid = _invalid;

	// ����������
	if(_a.size() * src._a.size() != 0)
	{
		// ��˻������ÿһ�еĽ��
		for(size_t i = 0; i < _row; i++)
		{
			int *ctemp = new int[src._col];
			memset(ctemp, 0, sizeof(int) * src._col);
			res.vecrpos.push_back(res._a.size());
			
			// ����Ԫ��˳�������
			for(size_t p = vecrpos[i]; p < vecrpos[i] + vecrcount[i]; p++)
			{
				size_t brow = _a[p]._c;		// ��ӦԪ��src�е��к�
				for(size_t q = src.vecrpos[brow]; q < src.vecrpos[brow] + src.vecrcount[brow]; q++)
				{
					size_t col = src._a[q]._c;
					ctemp[col] = ctemp[col] + _a[p]._value * src._a[q]._value;
				}
			}

			// ����i�з���Ԫ����res��
			for(size_t col = 0; col < src._col; col++)
			{
				if(ctemp[col])
				{
					// res.vecrpos[i]++;
					Triple<T> tmp(i, col, ctemp[col]);
					res._a.push_back(tmp);
				}
			}

			delete [] ctemp;
			ctemp = NULL;
		}

		// ͳ��ÿ���кϷ�ֵ�ĸ���
		res.vecrcount.resize(_row);
		for(size_t i = 0; i < _row; i++)
			res.vecrcount[res._a[i]._r]++;
	}

	return res;
}


int main()
{
	int M[3][4] = 
	{
		{3, 0, 0, 5},
		{0, -1, 0, 0},
		{2, 0, 0, 0}
	};

	int N[4][2] = 
	{
		{0, 2},
		{1, 0},
		{-2, 4},
		{0, 0}
	};

	SparseMatrix<int> sm((int*)M, 3, 4, 0);
	sm.Display();
	SparseMatrix<int> sn((int*)N, 4, 2, 0);
	sn.Display();

	SparseMatrix<int> sMulti;
	sMulti = sm.Multiply(sn);
	sMulti.Display();

	system("pause");
	return 0;
}