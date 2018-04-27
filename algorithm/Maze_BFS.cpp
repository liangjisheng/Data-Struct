
// 广度优先搜索的优点是找出的第一条路径就是最短路径，所以经常用来搜索最短路径，思路和图的广度优先遍历一样，需要借助于队列
// 具体步骤:
// (1)从入口元素开始，判断它上下左右的临边元素是满足条件，如果满足条件就入队列
// (2)取队首元素并出队列，寻找其相邻未被访问的元素，将其入队列并标记元素的前驱节点为队首元素
// (3)重复步骤(2)，直到队列为空(没有找到可行路径)或者找到了终点.最后从终点开始
// 根据节点的前驱节点找出一条最短的可行路径

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Point{  
	//行与列
	int row;  
	int col;  

	//默认构造函数
	Point(){
		row=col=-1;
	}

	Point(int x,int y){
		this->row=x;
		this->col=y;
	}

	bool operator==(const Point& rhs) const{
		if(this->row==rhs.row&&this->col==rhs.col)
			return true;
		return false;
	}
};

int maze[5][5] =
{
	{0,0,0,0,0},
	{0,1,0,1,0},
	{0,1,1,1,0},
	{0,1,0,0,1},
	{0,0,0,0,0}
};

void print_mark(void** mark, int row, int col)
{
	Point** pMark = (Point**)mark;
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
			cout << "(" << pMark[i][j].row << "," << pMark[i][j].col << ")";
		cout << endl;
	}
	cout << endl;
}

void mazePath(void* maze, int row, int col, Point& startP, Point endP,
	vector<Point>& shortestPath)
{
	int** maze2d = new int*[row];
	for(int i = 0; i < row; i++)
		maze2d[i] = (int*)maze + i * col;

	// 输入错误
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// 起点即终点
	if(startP == endP)
	{
		shortestPath.push_back(startP);
		return ;
	}

	// mark标记每一个节点的前驱节点，如果没有则为(-1, -1),如果有则表示已经被访问
	Point** mark = new Point*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new Point[col];

	print_mark((void**)mark, row, col);

	queue<Point> queuePoint;
	queuePoint.push(startP);
	// 将起点的前驱节点设置为自己
	mark[startP.row][startP.col] = startP;

	while(!queuePoint.empty())
	{
		print_mark((void**)mark, row, col);

		Point pointFront = queuePoint.front();
		queuePoint.pop();

		// 上节点连通
		if(pointFront.row - 1 >= 0 && maze2d[pointFront.row - 1][pointFront.col] == 0)
		{
			// 上节点未被访问
			if(mark[pointFront.row - 1][pointFront.col] == Point())
			{
				mark[pointFront.row - 1][pointFront.col] = pointFront;
				queuePoint.push(Point(pointFront.row - 1, pointFront.col));
				if(Point(pointFront.row - 1, pointFront.col) == endP)	// 找到终点
					break;
			}
		}

		if(pointFront.col+1<col && maze2d[pointFront.row][pointFront.col+1]==0){//右节点连通
			if(mark[pointFront.row][pointFront.col+1]==Point()){//右节点未被访问，满足条件，入队列
				mark[pointFront.row][pointFront.col+1]=pointFront;
				queuePoint.push(Point(pointFront.row,pointFront.col+1));    //入栈
				if(Point(pointFront.row,pointFront.col+1)==endP){ //找到终点
					break;
				}
			}
		}

		if(pointFront.row+1<row && maze2d[pointFront.row+1][pointFront.col]==0){//下节点连通
			if(mark[pointFront.row+1][pointFront.col]==Point()){//下节点未被访问，满足条件，入队列
				mark[pointFront.row+1][pointFront.col]=pointFront;
				queuePoint.push(Point(pointFront.row+1,pointFront.col));    //入栈
				if(Point(pointFront.row+1,pointFront.col)==endP){ //找到终点
					break;
				}
			}
		}

		if(pointFront.col-1>=0 && maze2d[pointFront.row][pointFront.col-1]==0){//左节点连通
			if(mark[pointFront.row][pointFront.col-1]==Point()){//上节点未被访问，满足条件，入队列
				mark[pointFront.row][pointFront.col-1]=pointFront;
				queuePoint.push(Point(pointFront.row,pointFront.col-1));    //入栈
				if(Point(pointFront.row,pointFront.col-1)==endP){ //找到终点
					break;
				}
			}
		}
	}

	print_mark((void**)mark, row, col);

	if(queuePoint.empty()==false)
	{
		int row=endP.row;
		int col=endP.col;
		shortestPath.push_back(endP);
		while(!(mark[row][col]==startP)){
			shortestPath.push_back(mark[row][col]);
			row=mark[row][col].row;
			col=mark[row][col].col;
		}
		shortestPath.push_back(startP);
	}
}


int main()
{
	Point startP(0, 0);
	Point endP(4, 4);
	vector<Point> vecPath;
	mazePath(maze, 5, 5, startP, endP, vecPath);

	if(vecPath.empty())
		cout << "no right path" << endl;
	else
	{
		cout << "shortest path:";
		for(vector<Point>::reverse_iterator iter = vecPath.rbegin(); iter != vecPath.rend(); iter++)
		// for(vector<Point>::iterator iter = vecPath.begin(); iter != vecPath.end(); iter++)
			cout << "(" << iter->row << "," << iter->col << ")";
		cout << endl;
	}

	system("pause");
	return 0;
}