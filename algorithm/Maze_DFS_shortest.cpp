
// �Ľ��������������DFS���ӻ���������·��
// ��������ķ������ǿ����ڴ˻���֮�Ͻ��иĽ�������Թ�����̵�·���������������£� 
// (1)���Ѿ����ʹ��Ľڵ�����ٴα����ʣ����������ǽ�mark��Ǹ�Ϊ��ǰ�ڵ㵽
// ���ľ��룬��Ϊ��ǰ�ڵ��Ȩֵ.������㿪ʼ��������4��������ң����߹��ĵ��ֵ��1
// (2)Ѱ��ջ��Ԫ�ص���һ���ɷ��ʵ����ڽڵ�,��������ջ��Ԫ�ص�Ȩֵ��1
// ����С����һ���ڵ��Ȩֵ(ǽ�����ߣ�δ�����ʵĽڵ�ȨֵΪ0)
// (3)������ʵ��յ㣬��¼��ǰ���·����������ǣ������Ѱ����һ���ڵ�
// (4)�ظ�����(2)��(3)֪��ջ��(�Թ������з��������Ľڵ��������)

#include <iostream>
#include <stack>
#include <vector>
using namespace std;

struct Point{  
	//������
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

// ��ȡ����δ�����ʵĽڵ�
Point getAdjacentNotVisitedNode(int **mark, Point point, 
	int row, int col, Point endP)
{
	Point resP(-1, -1);

	// �Ͻڵ���������
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

	// �ҽڵ���������
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

	// �½ڵ���������
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

	// ��ڵ���������
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
	������ά�Թ�������̿���·��
	maze:�Թ�
	row:��
	col:��
	startP:��ʼ�ڵ�
	endP:�����ڵ�
	pointStack:ջ�����·���ڵ�
	vecPath:������·��
**/
void mazePath(void *maze, int row, int col, Point& startP, Point endP,
	stack<Point>& pointStack, vector<Point>& vecPath)
{
	// �����������������Ķ�ά���黹ԭΪָ�����飬��֧���±����
	int ** maze2d = new int *[row];
	for(int i = 0; i < row; ++i)
		maze2d[i] = (int*)maze + i * col;

	// �������,��ʼ�ڵ�ͽ����ڵ���������ϰ��ڵ�
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// ���������ڵ���ʱ�ǣ���ʾ�ڵ㵽����Ȩֵ��Ҳ��¼����㵽��ǰ��·���ĳ���
	int** mark = new int*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new int[col];

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mark[i][j] = *((int*)maze + i * row + j);
	print_mark(mark, row, col);

	if(startP == endP)		// �������յ�
	{
		vecPath.push_back(startP);
		return ;
	}

	// ����һ���յ���ѱ����ʵ�ǰ���ڵ㼯
	// vector<Point> visitedEndPointPreNodeVec;

	// �������ջ
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;

	// ջ������ջ��Ԫ�ز�Ϊ������
	while(!pointStack.empty())
	{
		Point adjacentNotVisitedNode = getAdjacentNotVisitedNode(mark, 
			pointStack.top(), row, col, endP);
		if(adjacentNotVisitedNode.row == -1)		// û�з��������Ľڵ�
		{
			pointStack.pop();						// ���ݵ���һ���ڵ�
			continue;
		}

		// �Խ϶̵�·�����ҵ����յ�
		if(adjacentNotVisitedNode == endP)
		{
			mark[adjacentNotVisitedNode.row][adjacentNotVisitedNode.col] = 
				mark[pointStack.top().row][pointStack.top().col] + 1;
			pointStack.push(endP);
			stack<Point> pointStackTemp = pointStack;
			vecPath.clear();
			while(!pointStackTemp.empty())
			{
				vecPath.push_back(pointStackTemp.top());	// vecPath��ŵ�������·��
				pointStackTemp.pop();
			}
			pointStack.pop();		// ���յ��ջ
			continue;
		}

		// ��ջ�����÷��ʱ�־Ϊtrue
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

	// (1)mark��Ǹ�Ϊ�ڵ�Ȩֵ����¼��㵽�ڵ��·�����ȣ��������ȨֵΪ0
	// (2)Ϊ��Ӧmark��ǣ����Թ���ǽ��Ϊ-1��������ڵ�Ȩֵ����
	// (3)�����һ�����ʵĽڵ㣬�ж������ǽڵ��ȨֵҪС���䵱ǰȨֵ
}
