
// 10进制正数转换成对应的8进制

#include <iostream>
#include <stack>
#include <cmath>

using std::cout;
using std::endl;
using std::stack;
using std::powl;

int conversion(int ndec, int nbase)
{
	stack<int> res;
	int mod = ndec;
	while(mod)
	{
		res.push(mod % nbase);
		mod /= nbase;
	}

	int nConver = 0;
	int sz = res.size();
	for(int i = sz - 1; i >= 0; i--)
	{
		nConver = nConver + powl(10, i) * res.top();
		res.pop();
	}

	return nConver;

	//while(!res.empty())
	//{
	//	cout << res.top();
	//	res.pop();
	//}
}

int main()
{
	int ndec = 16;
	int noct = conversion(ndec, 2);
	cout << noct << endl;
	noct = conversion(ndec, 3);
	cout << noct << endl;
	noct = conversion(ndec, 4);
	cout << noct << endl;
	noct = conversion(ndec, 5);
	cout << noct << endl;
	noct = conversion(ndec, 6);
	cout << noct << endl;
	noct = conversion(ndec, 7);
	cout << noct << endl;
	noct = conversion(ndec, 8);
	cout << noct << endl;
	noct = conversion(ndec, 9);
	cout << noct << endl;
	noct = conversion(ndec, 10);
	cout << noct << endl;

	system("pause");
	return 0;
}