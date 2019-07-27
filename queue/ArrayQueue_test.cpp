
/**
 * C++ : 数组实现“队列”，能存储任意数据。
 *
 * @author liangjisheng
 * @date 2017/10/09
*/

#include <iostream>
#include "ArrayQueue.h"

using namespace std;

int main()
{
	int tmp = 0;
	ArrayQueue<int> *aqueue = new ArrayQueue<int>();

	aqueue->add(10);
	aqueue->add(20);
	aqueue->add(30);

	tmp = aqueue->pop();
	cout << "tmp = " << tmp << endl;

	tmp = aqueue->front();
	cout << "tmp = " << tmp << endl;

	aqueue->add(40);

	cout << "is_empty() = " << aqueue->is_empty() << endl;
	cout << "size() = " << aqueue->size() << endl;

	cout << endl;
	while(!aqueue->is_empty())
	{
		tmp = aqueue->pop();
		cout << tmp << endl;
	}

	system("pause");
	return 0;
}