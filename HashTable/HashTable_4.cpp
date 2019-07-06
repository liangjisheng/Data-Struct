
// 哈希表的数组实现，线性探测，二次探测

#include <iostream>

using std::cout;
using std::endl;

enum State
{
	EMPTY,		// 空
	EXCITE,		// 存在
	DELETE,		// 标记为空，但不为空
};

template<typename T>
class HashTable
{
public:
	HashTable(size_t capacity) : _capacity(capacity), _size(0)
	{
		_table = new T[_capacity];		// 开辟哈希空间
		_state = new State[_capacity];		// 开辟和哈希容量一样的空间存放状态
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
		if (_size == _capacity)		// 空间已满
			return false;
		size_t pos = hashFun1(key);	// 计算key的下标
		int idx = 1;
		while (_state[pos] == EXCITE)	// 这个位置有值
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
		if (_size <= 0)			// 哈希表为空
			return false;

		size_t pos = hashFun1(key);	// 计算key的下标
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
	// 一次探测
	size_t hashFun1(const T& key) { return key % _capacity; }
	// 二次探测
	size_t hashFun2(size_t lasthash, int idx) { return (lasthash + 2 * idx - 1) % _capacity; }

private:
	T *_table;			// 哈希表
	State *_state;		// 状态
	size_t _capacity;	// 容量
	size_t _size;		// 元素个数
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
