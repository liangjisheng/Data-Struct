
// ʹ��ջ��Ϊ�û������뻺�����������û������������ڷ�������ʱ
// ���Լ�ʱ���������û����ָո�������ַ��Ǵ���ģ����Բ���һ���˸��
// #,���Ա�ʾǰһ���ַ���Ч��������ֵ�ǰ�������ڵĳ���϶�����Բ���
// ����Լ���һ�����з�@,�Ա�ʾ��ǰ���е��ַ�����Ч
// whli##ilr#e(s#*s)
//		outcha@putchar(*s=#++)
// �൱�����������
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
			ch = getchar();			// ���ն˽�����һ���ַ�
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