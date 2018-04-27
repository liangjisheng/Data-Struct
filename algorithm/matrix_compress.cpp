
/*
��������һ�� n*n �� �����Ǿ��� A ���������Ǿ��� A ��Ԫ���Ѱ���Ϊ��������ѹ�� 
��������� B �У����һ���㷨���� B �е�Ԫ�ذ���Ϊ��������ѹ����������� C��
         1 2  3  4  5 
         0 6  7  8  9
A(5*5) = 0 0 10 11 12 
         0 0  0 13 14
         0 0  0  0 15   
���� B = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0},
     C = { 1, 2, 6, 3, 7, 10, 4, 8, 11, 13, 5, 9, 12, 14, 15, 0}.
     
˼·����һά����B��ԭ�ɶ�ά����A���ٽ���ά���鴢����C��
*/

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

#define N 5

// ת��Ϊԭʼ��ά����
void Trans_To_Original(int array[N][N], int *arr);
// �����Ǿ�����ѹ��
void Trans_To_Compress_row(int array[N][N], int *arr);
// �����Ǿ�����ѹ��
void Trans_To_Compress_col(int array[N][N], int *arr);
// ��ʾԭʼ�����Լ����кͰ���ѹ�����
void show(int array[N][N], int *arr1, int *arr2);


int main()
{
	int A[N][N] = {0};
	int B[N * (N + 1) / 2 + 1] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
	Trans_To_Original(A, B);

	int C[N * (N + 1) / 2 + 1] = {0};
	Trans_To_Compress_col(A, C);

	show(A, B, C);

	system("pause");
	return 0;
}


void Trans_To_Original(int array[N][N], int *arr)
{
	int i, j, k;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			if(i <= j)
			{
				// k = j * (j + 1) / 2 + i;
				k = i * (2 * N - i + 1) / 2 + j - i;
				array[i][j] = arr[k];
			}
			else
			{
				k = N * (N + 1) / 2;
				array[i][j] = arr[k];
			}
		}
	}
}

void Trans_To_Compress_row(int array[N][N], int *arr)
{
	int i, j, k = 0;
	// ���д洢
	for(i = 0; i < N; i++)
	{
		for(j = i; j < N; j++)
			arr[k++] = array[i][j];
	}

	arr[N * (N + 1) / 2] = 0;
}

void Trans_To_Compress_col(int array[N][N], int *arr)
{
	int i, j, k = 0;
	// ���д洢
	for(i = 0; i < N; i++)
	{
		for(j = 0; j <= i; j++)
			arr[k++] = array[j][i];
	}

	arr[N * (N + 1) / 2] = 0;
}

void show(int array[N][N], int *arr1, int *arr2)
{
	cout << "��ά����:" << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			cout << std::setw(5) << std::setiosflags(std::ios::left) <<  array[i][j] << ' ';
		cout << endl;
	}

	cout << "����Ϊ����ѹ�����ý����" << endl;
	for(int i = 0; i <= N * (N + 1) / 2; i++)
		cout << arr1[i] << ' ';
	cout << endl;

	cout << "����Ϊ����ѹ�����ý��:" << endl;
	for(int i = 0; i <= N * (N + 1) / 2; i++)
		cout << arr2[i] << ' ';
	cout << endl;
}
