
// �Թ�����,������������ӻ�������һ������·��
// �ŵ�:��������������������(BFS)��¼ǰ�����
// ȱ��:�ҵ��ĵ�һ������·����һ�������·��,�����Ҫ�ҵ����·����
// ��ô��Ҫ�ҳ����п���·��������һ�Ƚϣ������·��

// ʵ�ֲ���
// (1)���������յ㣬�ж϶��ߵĺϷ��ԣ�������Ϸ�������
// (2)��������յ�Ϸ����������ջ
// (3)ȡջ��Ԫ�أ������ڽӵ�δ�����ʵ����ϰ���㣬����У�����
// Ϊ�ѷ��ʣ�����ջ.���û���������һ��㣬���������ǽ���ǰ
// ջ��Ԫ��ȡ��
// ���У����ڽ����ϰ�����˳������⣬����ʵ�������ϡ��ҡ��¡����˳�����
// (4)�ظ�����3��ֱ��ջ��(û���ҵ�����·��)����ջ��Ԫ�ص����յ�(�ҵ���һ������·��)

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
	��ȡ����δ�����ʵĽڵ�
	mark:�ڵ���
	point:�ڵ�
	row:��
	col:��
**/
Point getAdjacentNotVisitedNode(bool** mark, Point point, int row, int col)
{
	Point resP(-1, -1);
	// �Ͻڵ���������
	if(point.row - 1 >= 0 && mark[point.row - 1][point.col] == false)
	{
		resP.row = point.row - 1;
		resP.col = point.col;
		return resP;
	}
	// �ҽڵ���������
	if(point.col + 1 < col && mark[point.row][point.col + 1] == false)
	{
		resP.row = point.row;
		resP.col = point.col + 1;
		return resP;
	}
	// �½ڵ���������
	if(point.row + 1 < row && mark[point.row + 1][point.col] == false)
	{
		resP.row = point.row + 1;
		resP.col = point.col;
		return resP;
	}
	// ��ڵ���������
	if(point.col - 1 >= 0 && mark[point.row][point.col - 1] == false)
	{
		resP.row = point.row;
		resP.col = point.col - 1;
		return resP;
	}

	return resP;
}

/**
	������ά�Թ�,�����·��
	maze:�Թ�
	row:��
	col:��
	startP:��ʼ�ڵ�
	endP:�����ڵ�
	pointStack:ջ�����·���ڵ�
	����ֵ:��
**/
void mazePath(void* maze, int row, int col, 
	const Point& startP, Point endP, stack<Point>& pointStack)
{
	// �����������������Ķ�ά���黹ԭΪָ�����飬��֧���±����
	int ** maze2d = new int *[row];
	for(int i = 0; i < row; ++i)
		maze2d[i] = (int*)maze + i * col;

	// �������,��ʼ�ڵ�ͽ����ڵ���������ϰ��ڵ�
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// ���������ڵ���ʱ��
	bool** mark = new bool*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new bool[col];

	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mark[i][j] = *((int*)maze + i * row + j);

	// ����ʼ�ڵ���ջ
	pointStack.push(startP);
	mark[startP.row][startP.col] = true;	// ���Ϊ�Է���

	// ջ���ղ���ջ��Ԫ�ز�Ϊ�����ڵ�
	while(!pointStack.empty() && pointStack.top() != endP)
	{
		// ��ȡ�ڽ�δ���ʽڵ�
		Point adjacentNotVisitedNode = 
			getAdjacentNotVisitedNode(mark, pointStack.top(), row, col);
		if(adjacentNotVisitedNode.row == -1)	// û��δ�����ʽڵ�
		{
			pointStack.pop();	// ���ݵ���һ���ڵ�
			continue;
		}

		// ��ջ�����÷��ʱ�־Ϊtrue
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

	// û���ҵ����н�
	if(pointStack.empty())
		cout << "no right path" << endl;
	else
		print_path(pointStack);

	system("pause");
	return 0;

	// �ɼ�����·���������·����������ǵ���Ѱ����һ�����ʵ����ڽڵ��˳��
	// �ɻ��������ң������£����ܻ�õ����̵�·�������޷�ȷ�����κ������
	// ���ܵõ����·��
	// ������һ���ڵ��˳�������4����(��������)������4*3*2*1 = 24�ֿ�����
}

