
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

static int moveCount = 0;

// 将第二个参数塔上的圆盘移动到第四个参数表示的塔上去，
// 第三个参数代表的塔作为辅助塔，n表示移动的圆盘个数
void hanoi(int n, char A, char B, char C)
{
	if(1 == n)
		cout << "第" << ++moveCount << "次移动:\t" << A << "->" << C << endl;
	else
	{
		hanoi(n - 1, A, C, B);	// A塔上1到n-1的圆盘移动到B塔上
		cout << "第" << ++moveCount << "次移动:\t" << A << "->" << C << endl;
		hanoi(n - 1, B, A, C);	// B塔上1到n-1的圆盘移动到C塔上
	}
}


int main()
{
	cout << "请输入圆盘个数:";
	int count = 0;
	cin >> count;

	char a = 'A', b = 'B', c = 'C';
	hanoi(count, a, b, c);
	cout << endl;

	system("pause");
	return 0;
}