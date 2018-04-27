
// 迷宫问题,深度优先搜索加回溯求解第一条可行路径
// 优点:无需想广度优先搜索那样(BFS)记录前驱结点
// 缺点:找到的第一条可行路径不一定是最短路径,如果需要找的最短路径，
// 那么需要找出所有可行路径后，在逐一比较，求最短路径

// 实现步骤
// (1)给定起点和终点，判断二者的合法性，如果不合法，返回
// (2)如果起点和终点合法，将起点入栈
// (3)取栈顶元素，求其邻接的未被访问的无障碍结点，如果有，记其
// 为已访问，并入栈.如果没有则回溯上一结点，具体做法是将当前
// 栈顶元素取出
// 其中，求邻接无障碍结点的顺序可任意，本文实现是以上、右、下、左的顺序求解
// (4)重复步骤3，直到栈空(没有找到可行路径)或者栈顶元素等于终点(找到第一条可行路径)

#include <iostream>
#include <stack>

using std::cout;
using std::endl;
using std::stack;

struct Point
{
	int row;
	int col;
	Point(int x, int y)
	{
		this->row = x;
		this->col = y;
	}

	bool operator!=(const Point& rhs)
	{
		if(this->row != rhs.row || this->col != rhs.col)
			return true;
		else
			return false;
	}
};


/**
	获取相邻未被访问的节点
	mark:节点标记
	point:节点
	row:行
	col:列
**/
Point getAdjacentNotVisitedNode(bool** mark, Point point, int row, int col)
{
	Point resP(-1, -1);
	// 上节点满足条件
	if(point.row - 1 >= 0 && mark[point.row - 1][point.col] == false)
	{
		resP.row = point.row - 1;
		resP.col = point.col;
		return resP;
	}
	// 右节点满足条件
	if(point.col + 1 < col && mark[point.row][point.col + 1] == false)
	{
		resP.row = point.row;
		resP.col = point.col + 1;
		return resP;
	}
	// 下节点满足条件
	if(point.row + 1 < row && mark[point.row + 1][point.col] == false)
	{
		resP.row = point.row + 1;
		resP.col = point.col;
		return resP;
	}
	// 左节点满足条件
	if(point.col - 1 >= 0 && mark[point.row][point.col - 1] == false)
	{
		resP.row = point.row;
		resP.col = point.col - 1;
		return resP;
	}

	return resP;
}

/**
	给定二维迷宫,求可行路径
	maze:迷宫
	row:行
	col:列
	startP:开始节点
	endP:结束节点
	pointStack:栈，存放路径节点
	返回值:无
**/
void mazePath(void* maze, int row, int col, 
	const Point& startP, Point endP, stack<Point>& pointStack)
{
	// 将给定的任意列数的二维数组还原为指针数组，以支持下标操作
	int ** maze2d = new int *[row];
	for(int i = 0; i < row; ++i)
		maze2d[i] = (int*)maze + i * col;

	// 输入错误,开始节点和结束节点必须是无障碍节点
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// 建立各个节点访问标记
	bool** mark = new bool*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new bool[col];

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mark[i][j] = *((int*)maze + i * row + j);

	// 将起始节点入栈
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;	// 标记为以访问

	// 栈不空并且栈顶元素不为结束节点
	while(!pointStack.empty() && pointStack.top() != endP)
	{
		// 获取邻接未访问节点
		Point adjacentNotVisitedNode = 
			getAdjacentNotVisitedNode(mark, pointStack.top(), row, col);
		if(adjacentNotVisitedNode.row == -1)	// 没有未被访问节点
		{
			pointStack.pop();	// 回溯到上一个节点
			continue;
		}

		// 入栈并设置访问标志为true
		mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = true;
		pointStack.push(adjacentNotVisitedNode);
	}
	
	for(int i = 0; i < row; i++)
		delete [] mark[i];
	delete[] mark;
	mark = NULL;

	//for(int i = 0; i < row; i++)
	//	delete [] maze2d[i];
	delete [] maze2d;
	maze2d = NULL;
}

void print_path(stack<Point>& pointStack)
{
	stack<Point> tmpStack;
	cout << "path:";
	while(!pointStack.empty())
	{
		tmpStack.push(pointStack.top());
		pointStack.pop();
	}

	while(!tmpStack.empty())
	{
		cout << "(" << tmpStack.top().row << "," 
			<< tmpStack.top().col << ") ";
		tmpStack.pop();
	}
	cout << endl;
}

int main()
{
	int maze[5][5]=
	{
		{0, 0, 0, 0, 0},
		{0, 1, 0, 1, 0},
		{0, 1, 1, 0, 0},
		{0, 1, 1, 0, 1},
		{0, 0, 0, 0, 0}
	};

	Point startP(0, 0);
	Point endP(4, 4);
	stack<Point> pointStack;
	mazePath(maze, 5, 5, startP, endP, pointStack);

	// 没有找到可行解
	if(pointStack.empty())
		cout << "no right path" << endl;
	else
		print_path(pointStack);

	system("pause");
	return 0;

	// 可见这条路径不是最短路径，如果我们调整寻找下一个访问的相邻节点的顺序
	// 可换成先左右，后上下，可能会得到更短的路径，但无法确保在任何情况下
	// 都能得到最短路径
	// 访问下一个节点的顺序如果是4方向(上下左右)可能有4*3*2*1 = 24种可能性
}

