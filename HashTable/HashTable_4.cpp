
// ��ϣ�������ʵ�֣�����̽�⣬����̽��

#include <iostream>

using std::cout;
using std::endl;

enum State
{
	EMPTY,		// ��
	EXCITE,		// ����
	DELETE,		// ���Ϊ�գ�����Ϊ��
};

template<typename T>
class HashTable
{
public:
	HashTable(size_t capacity) : _capacity(capacity), _size(0)
	{
		_table = new T[_capacity];		// ���ٹ�ϣ�ռ�
		_state = new State[_capacity];		// ���ٺ͹�ϣ����һ���Ŀռ���״̬
		memset(_table, T(), sizeof(T) * _capacity);
		memset(_state, EMPTY, sizeof(State) * _capacity);
	}
	~HashTable()
	{
		delete [] _table;
		_table = NULL;
		delete [] _state;
		_state = NULL;
	}
public:
	bool Insert(const T& key)
	{
		if (_size == _capacity)		// �ռ�����
			return false;
		size_t pos = hashFun1(key);	// ����key���±�
		int idx = 1;
		while (_state[pos] == EXCITE)	// ���λ����ֵ
		{
			if (_table[pos] == key)
				return false;
			pos = hashFun2(pos, idx++);
		}

		_table[pos] = key;
		_state[pos] = EXCITE;
		_size++;
		return true;
	}
	bool Remove(const T& key)
	{
		if (_size <= 0)			// ��ϣ��Ϊ��
			return false;

		size_t pos = hashFun1(key);	// ����key���±�
		int idx = 1;
		while (_state[pos] != EMPTY)
		{
			if (_table[pos] == key && _state[pos] != DELETE)
			{
				_state[pos] = DELETE;
				return true;
			}
			pos = hashFun2(pos, idx++);
		}
		
		return false;
	}
	bool Find(const T& key)
	{
		if (_size <= 0)
			return false;
		size_t pos = hashFun1(key);
		int idx = 1;
		while (_state[pos] != EMPTY)
		{
			if (_table[pos] == key && _state[pos] != DELETE)
				return true;
			pos = hashFun2(pos, idx++);
		}
		return false;
	}

	void HashPrint();
private:
	// һ��̽��
	size_t hashFun1(const T& key) { return key % _capacity; }
	// ����̽��
	size_t hashFun2(size_t lasthash, int idx) { return (lasthash + 2 * idx - 1) % _capacity; }

private:
	T *_table;			// ��ϣ��
	State *_state;		// ״̬
	size_t _capacity;	// ����
	size_t _size;		// Ԫ�ظ���
};

template<typename T>
void HashTable<T>::HashPrint()
{
	for (size_t idx = 0; idx < _capacity; ++idx)
		cout << _table[idx] << "->" << _state[idx] << " ";
	cout << endl;
}

void FuncTest()
{
	HashTable<int> ht(10);
	ht.Insert(18);
	ht.Insert(49);  
	ht.Insert(10);  
	ht.Insert(58);  
	ht.Insert(43); 

	ht.HashPrint();
	ht.Remove(18);
	ht.HashPrint();

	cout << "find:(18): " << ht.Find(18) << endl;
}

int main()
{
	FuncTest();

	system("pause");
	return 0;
}
