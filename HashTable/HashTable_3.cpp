
// 除留余数法，将关键字对整数p取的余数直接作为存储地址，整数p一般取小于等于哈希表长度
// size的质数，如果关键字不是整数，比如是个字符串，可以先将其做个转换，然后在对p取余
// 选择优秀的p可以避免冲突
// 这里用直接寻址法构造一个哈希函数

// 开放地址法计算简单快捷，处理起来方便，但是也存在不少缺点。线性探测法容易形成“堆聚”
// 的情况，即很多记录就连在一块，而且一旦形成“堆聚”，记录会越聚越多。另外，开放地址
// 法都有一个缺点，删除操作显得十分复杂，我们不能直接删除关键字所在的记录，否则在查找
// 删除位置后面的元素时，可能会出现找不到的情况，因为删除位置上已经成了空地址，查找到
// 这里时会终止查找。
// 链地址法。该方法将所有哈希地址相同的结点构成一个单链表，单链表的头结点存在哈希数组
// 链地址法常出现在经常插入和删除的情况下
// 相比开放地址法，链地址法有以下优点：不会出现“堆聚”现象，哈希地址不同的关键字不会
// 发生冲突;不需要重建哈希表，在开放地址法中，如果哈希表里存满关键字了就需要扩充哈希表
// 然后重建哈希表，而在链地址法里，因为结点都是动态申请的，所以不会出现哈希表里存满关
// 键字的情况；相比开放地址法，关键字删除更方便，只需要找到指定结点，删除该结点即可

// 开放地址法和链地址法各有千秋，适用于不同情况
// 当关键字规模少的时候，开放地址法比链地址法更节省空间，因为用链地址法可能会存在哈希
// 数组出现大量空地址的情况，而在关键字规模大的情况下，链地址法就比开放地址法更节省空间
// 链表产生的指针域可以忽略不计，关键字多，哈希数组里产生的空地址就少了

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

class HashTable
{
private:
	string *elem;		// 表明是动态开辟存放的
	int size;			// 哈希表的表长
public:
	HashTable()
	{
		size = 2000;
		elem = new string[size];

		// 用来标记该位置是否已经存放了用户名，#标记当前位置为空
		for (int i = 0; i < size; ++i)
			elem[i] = "#";
	}

	~HashTable() { delete [] elem; }

	int hash(string &index)
	{
		// 哈希函数构造方法，使用for循环中的构造方法为index字符串找到其在哈希表中的对应位置  
		int code = 0;
		for (size_t i = 0; i < index.length(); ++i)
			code = (code * 256 + index[i] + 128) % size;
		return code;
	}

	// 检验每次运用hash函数产生的哈希值的有效性
	bool search(string &index, int &pos, int &times)
	{
		pos = hash(index);
		times = 0;	// 记录冲突次数
		// 如果哈希值的标记处为空的话，那么就不必检验该处位置是否被占用等问题
		// 而如果哈希值的标记处的值与index相等的话，则说明在处理index之前，hash
		// 表中已经处理过了与index字符串相等的字符串了，并且将其放在了pos处，
		// 此时可提示该字符串在hash表中已经存在。所以当该处不为空，并且占有
		// 的元素不是index时，则说明产生了哈希冲突，因此需要重新为index字符串
		// 寻找位置
		while (elem[pos] != "#" && elem[pos] != index)
		{
			++times;
			if (times < size)//pos + 1的值可能会大于size的值,使用线性探测法解决哈希冲突
				pos = (pos + 1) % size;
			else			// //冲突次数达到了哈希表的长度，表示用线性探测法找不到能够容纳index字
				return false;
		}

		if (elem[pos] == index)
			return true;	// 表示hash表中已经处理过了与index字符串相等的字符串
		else
			return false;	//哈希冲突未解决
	}

	int insert(string &index)
	{
		int pos, times;
		//首先检测一下待插入的字符串是否在hash表中已经存在,若存在则返回2  
		if (search(index, pos, times))
			return 2;
		// 冲突次数少于表长一半(或者可另外规定)的情况下，将index字符串插入表中,
		// 因为如果冲突次数过多，说明表中 含有的元素已经很多了，再添加可能导致表溢出等问题
		else if (times < size / 2)
		{
			elem[pos] = index;
			return 1;
		}
		else
		{
			// 冲突次数过多，表明表中元素也过多了，无法再容纳新的元素，
			// 因此需要重建一个更大的哈希表
			recreate();
			return 0;  
		}
	}

	void recreate()
	{
		string *temp_elem;
		temp_elem = new string[size];  
		for(int i = 0;i < size;i++)  
			temp_elem[i] = elem[i];			//首先申请临时空间来存放原来哈希表中已经存放好的数据
		int copy_size = size;				//然后记录好原来哈希表的长度  

		size = size * 2;					//扩大哈希表的长度,使其成为原来的两倍  
		delete [] elem;						//删除原来申请的哈希表的空间，防止内存泄漏  
		elem = new string[size];			//申请新的空间  
		for (int i = 0; i < size; i++)
			elem[i] = "#";					//标记好原来已经存放元素的位置  

		for (int i = 0; i < copy_size; i++)
			if(temp_elem[i] != "#")
				insert(temp_elem[i]);       //将原来已经有存放元素的位置重新插入表中  
		delete [] temp_elem;				//删除临时申请的空间，防止内存泄漏  
	}

	void Display()
	{
		cout << "pos\tcontent" << endl;
		for (int i = 0; i < size; ++i)
			if (elem[i] != "#")
				cout << i << '\t' << elem[i] << endl;
	}
};


int main()
{
	HashTable hashtable;
	string buffer[] = { "test", "asdf", "qwer", "zxcv", "ghjk", "tyui" };
	int nlen = sizeof(buffer) / sizeof(buffer[0]);
	
	for (int i = 0; i < nlen; ++i)
	{
		int ans = hashtable.insert(buffer[i]);
		if (0 == ans)
			cout << "insert failed" << endl;
		else if (1 == ans)
			cout << "insert success" << endl;
		else if (2 == ans)
			cout << "It already exists" << endl;
	}
	cout << endl;

	hashtable.Display();
	cout << endl;

	int temp_pos, temp_times;	// 记录在哈希表中插入的位置和冲突次数
	string str1 = "asdf";
	if (hashtable.search(str1, temp_pos, temp_times))
		cout << "search success" << endl;
	else
		cout << "search failed" << endl;

	cout << "pos: " << temp_pos << endl;
	cout << "times: " << temp_times << endl;

	temp_pos = 0;
	temp_times = 0;
	str1 = "aaaa";
	if (hashtable.search(str1, temp_pos, temp_times))
		cout << "search success" << endl;
	else
		cout << "search failed" << endl;

	cout << "pos: " << temp_pos << endl;
	cout << "times: " << temp_times << endl;

	system("pause");
	return 0;
}