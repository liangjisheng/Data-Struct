
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

static int moveCount = 0;

// ���ڶ����������ϵ�Բ���ƶ������ĸ�������ʾ������ȥ��
// �������������������Ϊ��������n��ʾ�ƶ���Բ�̸���
void hanoi(int n, char A, char B, char C)
{
	if(1 == n)
		cout << "��" << ++moveCount << "���ƶ�:\t" << A << "->" << C << endl;
	else
	{
		hanoi(n - 1, A, C, B);	// A����1��n-1��Բ���ƶ���B����
		cout << "��" << ++moveCount << "���ƶ�:\t" << A << "->" << C << endl;
		hanoi(n - 1, B, A, C);	// B����1��n-1��Բ���ƶ���C����
	}
}


int main()
{
	cout << "������Բ�̸���:";
	int count = 0;
	cin >> count;

	char a = 'A', b = 'B', c = 'C';
	hanoi(count, a, b, c);
	cout << endl;

	system("pause");
	return 0;
}