
// 利用C++标准库中的栈检验括号匹配,如果括号是匹配的,
// 在最后栈是空的,否则栈不为空
// [([][])]		// ok
// [(])			// error

#include <iostream>
#include <stack>
#include <string>

using std::cout;
using std::endl;
using std::stack;
using std::string;

bool check(string str)
{
	stack<char> cStack;
	cStack.push(str.at(0));
	for(unsigned int i = 1; i < str.size(); i++)
	{
		char ch = str.at(i);
		if(ch == ' ')
			continue;
		char ch1;
		if(cStack.empty())
			ch1 = ' ';
		else
			ch1 = cStack.top();
		if((ch1 == '(' && ch == ')') || (ch1 == '[' && ch == ']'))
		// if(str.at(i) == cStack.top())
			cStack.pop();
		else
			cStack.push(str.at(i));
	}

	if(cStack.empty())
		return true;
	else
		return false;
}

int main()
{
	string str1 = "[] ()";
	string str2 = "[(])";
	if(check(str1))
		cout << str1 << " is ok" << endl;
	else
		cout << str1 << " not ok" << endl;

	if(check(str2))
		cout << str2 << " is ok" << endl;
	else
		cout << str2 << " not ok" << endl;

	system("pause");
	return 0;
}