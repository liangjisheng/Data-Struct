
// 使用栈作为用户的输入缓冲区，允许用户输入出差错，并在发现有误时
// 可以及时更正，当用户发现刚刚输入的字符是错误的，可以补进一个退格符
// #,用以表示前一个字符无效，如果发现当前键入行内的出错较多或难以补救
// 则可以键入一个退行符@,以表示当前行中的字符均无效
// whli##ilr#e(s#*s)
//		outcha@putchar(*s=#++)
// 相当于下面的两行
// while(*s)
//		putchar(*s++);

#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

void LineEdit()
{
	stack<char> chStack;
	char ch = getchar();
	//chStack.push(ch);
	while(ch != EOF)
	{
		while(ch != EOF && ch != '\n')
		{
			switch(ch)
			{
			case '#':
				chStack.pop();
				break;
			case '@':
				while(!chStack.empty())
					chStack.pop();
				break;
			default:
				chStack.push(ch);
				break;
			}
			ch = getchar();			// 从终端接收下一个字符
		}

		while(!chStack.empty())
			chStack.pop();
		if(ch != EOF)
			ch = getchar();
	}
} // LineEdit

int main()
{
	LineEdit();

	system("pause");
	return 0;
}