
#include <iostream>
#include <Windows.h>

using std::cout;
using std::endl;

void test1()
{
	char *buffer = new char[19];
	buffer[19] = 0;
	buffer[24] = 0;
	delete [] buffer;
}

void test2()
{
	char *buffer = new char[20];
	delete [] buffer;
	buffer[0] = 1;
}

void test3()
{
	int len = 5;
	char *p = (char *)HeapAlloc(GetProcessHeap(), 0, len);
	p[len] = 0;
	HeapFree(GetProcessHeap(), 0, p);
}

void test4()
{
	int *p = new int;
	delete p;
	delete p;
}

class A
{
public:
	int a;
	void del()
	{
		delete this;
		a = 10;
	}
};

void test5()
{
	cout << "test" << endl;
	A *pa = new A();
	pa->del();
	cout << "test" << endl;
}

int main()
{
	test3();

	system("pause");
	return 0;
}