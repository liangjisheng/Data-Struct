
#include <iostream>
#include "ArrayStack.h"

using namespace std;

int main()
{
	int tmp = 0;
	ArrayStack<int> *astack = new ArrayStack<int>();
	cout << "main" << endl;

	astack->push(10);
	astack->push(20);
	astack->push(30);

	tmp = astack->pop();
	cout << "tmp = " << tmp << endl;

	tmp = astack->peek();
	cout << "tmp = " << tmp << endl;
	cout << endl;

	astack->push(40);
	while(!astack->isEmpty())
	{
		tmp = astack->pop();
		cout << tmp << endl;
	}

	system("pause");
	return 0;
}