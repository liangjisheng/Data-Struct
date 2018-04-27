
/*
假设已有一个 n*n 的 上三角矩阵 A ，且上三角矩阵 A 的元素已按行为主序连续压缩 
存放在数组 B 中，设计一个算法，将 B 中的元素案列为主序连续压缩存放在数组 C中
         1 2  3  4  5 
         0 6  7  8  9
A(5*5) = 0 0 10 11 12 
         0 0  0 13 14
         0 0  0  0 15   
其中 B = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0},
     C = { 1, 2, 6, 3, 7, 10, 4, 8, 11, 13, 5, 9, 12, 14, 15, 0}.
     
思路：将一维数组B还原成二维数组A，再将二维数组储存在C中
*/

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

#define N 5

// 转换为原始二维数组
void Trans_To_Original(int array[N][N], int *arr);
// 上三角矩阵按行压缩
void Trans_To_Compress_row(int array[N][N], int *arr);
// 上三角矩阵按列压缩
void Trans_To_Compress_col(int array[N][N], int *arr);
// 显示原始矩阵，以及按行和按列压缩结果
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
	// 按行存储
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
	// 按列存储
	for(i = 0; i < N; i++)
	{
		for(j = 0; j <= i; j++)
			arr[k++] = array[j][i];
	}

	arr[N * (N + 1) / 2] = 0;
}

void show(int array[N][N], int *arr1, int *arr2)
{
	cout << "二维数组:" << endl;
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
			cout << std::setw(5) << std::setiosflags(std::ios::left) <<  array[i][j] << ' ';
		cout << endl;
	}

	cout << "以行为主序压缩所得结果：" << endl;
	for(int i = 0; i <= N * (N + 1) / 2; i++)
		cout << arr1[i] << ' ';
	cout << endl;

	cout << "以列为主序压缩所得结果:" << endl;
	for(int i = 0; i <= N * (N + 1) / 2; i++)
		cout << arr2[i] << ' ';
	cout << endl;
}
