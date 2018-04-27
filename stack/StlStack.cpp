
#include <iostream>
#include <stack>

using namespace std;

/**
 * C++ ����: STL �Դ��ġ�ջ��(stack)��ʾ����
 *
 * @author liangjisheng
 * @date 2017/10/09
*/

int main()
{
	int tmp = 0;
	stack<int> istack;

	istack.push(10);
	istack.push(20);
	istack.push(30);

	istack.pop();

	tmp = istack.top();
	cout << "tmp = " << tmp << endl;
	istack.push(40);

	while(!istack.empty())
	{
		tmp = istack.top();
		istack.pop();
		cout << tmp << endl;
	}

	system("pause");
	return 0;
}