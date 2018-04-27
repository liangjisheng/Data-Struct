
// 改进深度优先搜索（DFS）加回溯求解最短路径
// 根据上面的方法我们可以在此基础之上进行改进，求出迷宫的最短的路径。具体做法如下： 
// (1)让已经访问过的节点可以再次被访问，具体做法是将mark标记改为当前节点到
// 起点的距离，作为当前节点的权值.即从起点开始出发，想4个方向查找，把走过的点的值加1
// (2)寻找栈顶元素的下一个可访问的相邻节点,条件就是栈顶元素的权值加1
// 必须小于下一个节点的权值(墙不能走，未被访问的节点权值为0)
// (3)如果访问到终点，记录当前最短路径，如果不是，则继续寻找下一个节点
// (4)重复步骤(2)和(3)知道栈空(迷宫中所有符合条件的节点均被访问)

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Point{  
	//行与列
	int row;  
	int col;  
	Point(int x,int y){
		this->row=x;
		this->col=y;
	}

	bool operator!=(const Point& rhs){
		if(this->row!=rhs.row||this->col!=rhs.col)
			return true;
		return false;
	}

	bool operator==(const Point& rhs) const{
		if(this->row==rhs.row&&this->col==rhs.col)
			return true;
		return false;
	}
};

void print_mark(int** mark, int row, int col)
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
			cout << mark[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

int maze[5][5]=
{
	{0, 0, 0, 0,0},
	{0,-1, 0,-1,0},
	{0,-1,-1, 0,0},
	{0,-1,-1, 0,-1},
	{0, 0, 0, 0, 0}
};

// 获取相邻未被访问的节点
Point getAdjacentNotVisitedNode(int **mark, Point point, 
	int row, int col, Point endP)
{
	Point resP(-1, -1);

	// 上节点满足条件
	if(point.row - 1 >= 0)
	{
		int prev = mark[point.row - 1][point.col];
		int cur = mark[point.row][point.col];
		if(mark[point.row - 1][point.col] == 0 
			|| mark[point.row][point.col] + 1 < mark[point.row - 1][point.col])
		{
			resP.row = point.row - 1;
			resP.col = point.col;
			return resP;
		}
	}

	// 右节点满足条件
	if(point.col + 1 < col)
	{
		int prev = mark[point.row][point.col + 1];
		int cur = mark[point.row][point.col];
		if(mark[point.row][point.col + 1] == 0
			|| mark[point.row][point.col] + 1 < mark[point.row][point.col + 1])
		{
			resP.row = point.row;
			resP.col = point.col + 1;
			return resP;
		}
	}

	// 下节点满足条件
	if(point.row + 1 < row)
	{
		int prev = mark[point.row + 1][point.col];
		int cur = mark[point.row][point.col];
		if(mark[point.row + 1][point.col] == 0
			|| mark[point.row][point.col] + 1 < mark[point.row + 1][point.col])
		{
			resP.row = point.row + 1;
			resP.col = point.col;
			return resP;
		}
	}

	// 左节点满足条件
	if(point.col - 1 >= 0)
	{
		int prev = mark[point.row][point.col - 1];
		int cur = mark[point.row][point.col];
		if(mark[point.row][point.col - 1] == 0
			|| mark[point.row][point.col] + 1 < mark[point.row][point.col - 1])
		{
			resP.row = point.row;
			resP.col = point.col - 1;
			return resP;
		}
	}


	return resP;
}

/**
	给定二维迷宫，求最短可行路径
	maze:迷宫
	row:行
	col:列
	startP:开始节点
	endP:结束节点
	pointStack:栈，存放路径节点
	vecPath:存放最短路径
**/
void mazePath(void *maze, int row, int col, Point& startP, Point endP,
	stack<Point>& pointStack, vector<Point>& vecPath)
{
	// 将给定的任意列数的二维数组还原为指针数组，以支持下标操作
	int ** maze2d = new int *[row];
	for(int i = 0; i < row; ++i)
		maze2d[i] = (int*)maze + i * col;

	// 输入错误,开始节点和结束节点必须是无障碍节点
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// 建立各个节点访问标记，表示节点到起点的权值，也记录了起点到当前节路径的长度
	int** mark = new int*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new int[col];

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mark[i][j] = *((int*)maze + i * row + j);
	print_mark(mark, row, col);

	if(startP == endP)		// 起点等于终点
	{
		vecPath.push_back(startP);
		return ;
	}

	// 增加一个终点的已被访问的前驱节点集
	// vector<Point> visitedEndPointPreNodeVec;

	// 将起点入栈
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;

	// 栈不空且栈顶元素不为结束点
	while(!pointStack.empty())
	{
		Point adjacentNotVisitedNode = getAdjacentNotVisitedNode(mark, 
			pointStack.top(), row, col, endP);
		if(adjacentNotVisitedNode.row == -1)		// 没有符合条件的节点
		{
			pointStack.pop();						// 回溯到上一个节点
			continue;
		}

		// 以较短的路径，找到了终点
		if(adjacentNotVisitedNode == endP)
		{
			mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = 
				mark[pointStack.top().row][pointStack.top().col] + 1;
			pointStack.push(endP);
			stack<Point> pointStackTemp = pointStack;
			vecPath.clear();
			while(!pointStackTemp.empty())
			{
				vecPath.push_back(pointStackTemp.top());	// vecPath存放的是逆序路径
				pointStackTemp.pop();
			}
			pointStack.pop();		// 将终点出栈
			continue;
		}

		// 入栈并设置访问标志为true
		mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = 
			mark[pointStack.top().row][pointStack.top().col] + 1;
		pointStack.push(adjacentNotVisitedNode);

		print_mark(mark, row, col);
	}
}


int main()
{
	Point startP(0, 0);
	Point endP(4, 4);
	stack<Point> pointStack;
	vector<Point> vecPath;
	mazePath(maze, 5, 5, startP, endP, pointStack, vecPath);

	if(vecPath.empty())
		cout << "no right path" << endl;
	else
	{
		cout << "shortest path:";
		for(vector<Point>::reverse_iterator iter = vecPath.rbegin(); iter != vecPath.rend(); iter++)
			cout << "(" << iter->row << "," << iter->col << ")";
		cout << endl;
	}

	system("pause");
	return 0;

	// (1)mark标记改为节点权值，记录起点到节点的路径长度，因此起点的权值为0
	// (2)为适应mark标记，将迷宫的墙改为-1，以免与节点权值混淆
	// (3)求解下一个访问的节点，判断条件是节点的权值要小于其当前权值
}
