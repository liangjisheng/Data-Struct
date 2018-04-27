
/* 迷宫求路径
input:
1
6 8
0 1 1 1 0 1 1 1
1 0 1 0 1 0 1 0
0 1 0 0 1 1 1 1
0 1 1 1 0 0 1 1
1 0 0 1 1 0 0 0
0 1 1 0 0 1 1 0
output:
YES
(1,1)(2,2)(3,3)(3,4)(4,5)(4,6)(5,7)(6,8)
*/

// 广度优先搜索(BFS)
// 其优点：找出的第一条路径就是最短路径
// 其缺点：需要记录结点的前驱结点，来形成路径

#include <iostream>
#include <stack>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::queue;

void print_maze(int row, int column);

struct point 
{
	int x;
	int y;
};

// int **Maze;			// 初始化迷宫

int Maze[8][10] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 0, 1, 1, 1, 1},
	{1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 1},
	{1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
	{1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
point **Pre;		// 保存任意点在路径中的前一步
// 移动方向,横竖斜都可以
point move[8] = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};

void Create(int row, int column)
{
	// 创建迷宫，0表示可走，1表示墙，将整个输入的迷宫用墙围着
	// 处理的时候就不用特别注意边界问题
	int i, j;
	for(i = 0; i < row + 2; i++)
		Maze[i][0] = Maze[i][column + 1] = 1;
	for(j = 1; j < column + 1; j++)
		Maze[0][j] = Maze[row + 1][j] = 1;

	for(i = 1; i <= row; i++)
	{
		for(j = 1; j <= column; j++)
			cin >> Maze[i][j];
	}
}

bool MazePath(int row, int column, int x, int y)
{
	// 判断是否有路径从入口到出口，保存该路径(队列)
	if(x == row && y == column)
		return true;

	queue<point> q;		// 用于广度优先搜索
	point now;			// 当前位置
	now.x = x;
	now.y = y;
	q.push(now);
	Maze[now.x][now.y] = -1;

	while(!q.empty())
	{
		now = q.front();
		q.pop();
		for(int i = 0; i < 8; i++)
		{
			if(now.x + move[i].x == row && now.y + move[i].y == column)
			{
				Maze[now.x + move[i].x][now.y + move[i].y] = -1;
				Pre[row][column] = now;
				return true;
			}
			if(Maze[now.x + move[i].x][now.y + move[i].y] == 0)
			{  
				print_maze(row, column);
				point temp;     //下个位置  
				temp.x = now.x + move[i].x;  
				temp.y = now.y + move[i].y;  
				q.push(temp);  
				Maze[temp.x][temp.y] = -1;  
				Pre[temp.x][temp.y] = now;  
			}
		}
	}

	return false;
}

void PrintPath(int row,int column)
{  
	//输出最短路径  
	point temp;         //保存位置  
	stack<point> s;     //保存路径序列  
	temp.x = row;  
	temp.y = column;  
	while(temp.x != 1 || temp.y != 1)
	{  
		s.push(temp);  
		temp = Pre[temp.x][temp.y];  
	}  
	cout<<"(1,1)";
	while(!s.empty())
	{
		temp = s.top();
		cout << ' ' << '(' << temp.x << ',' << temp.y << ')';
		s.pop();
	}
	cout<<endl;  
}


int main()
{
	// int t;          //用例数量  
	int row = 6;        //迷宫行数  
	int column = 8;     //迷宫列数  
	// cin >> t;  
	//while(t--)
	//{  
		//cin >> row >> column;  
		//Maze = new int*[row + 2];  
		Pre = new point*[row + 2];  
		for(int i=0; i<row+2; i++){  
		//	Maze[i] = new int[column + 2];  
			Pre[i] = new point[column + 2];  
		}  
		//Create(row, column);
		print_maze(row, column);

		if(MazePath(row, column, 1, 1))
		{  
			cout << "YES" << endl;  
			PrintPath(row, column);  
		}  
		else 
			cout << "NO" << endl;
	//}

	system("pause");
	return 0;
}


void print_maze(int row, int column)
{
	cout << endl;
	for(int i = 1; i < row + 1; i++)
	{
		for(int j = 1; j < column + 1; j++)
			cout << Maze[i][j] << ' ';
		cout << endl;
	}
}