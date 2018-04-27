
// ��������������ŵ����ҳ��ĵ�һ��·���������·�������Ծ��������������·����˼·��ͼ�Ĺ�����ȱ���һ������Ҫ�����ڶ���
// ���岽��:
// (1)�����Ԫ�ؿ�ʼ���ж����������ҵ��ٱ�Ԫ��������������������������������
// (2)ȡ����Ԫ�ز������У�Ѱ��������δ�����ʵ�Ԫ�أ���������в����Ԫ�ص�ǰ���ڵ�Ϊ����Ԫ��
// (3)�ظ�����(2)��ֱ������Ϊ��(û���ҵ�����·��)�����ҵ����յ�.�����յ㿪ʼ
// ���ݽڵ��ǰ���ڵ��ҳ�һ����̵Ŀ���·��

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Point{  
	//������
	int row;  
	int col;  

	//Ĭ�Ϲ��캯��
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

	// �������
	if(maze2d[startP.row][startP.col] == 1 || maze2d[endP.row][endP.col] == 1)
		return ;

	// ��㼴�յ�
	if(startP == endP)
	{
		shortestPath.push_back(startP);
		return ;
	}

	// mark���ÿһ���ڵ��ǰ���ڵ㣬���û����Ϊ(-1, -1),��������ʾ�Ѿ�������
	Point** mark = new Point*[row];
	for(int i = 0; i < row; i++)
		mark[i] = new Point[col];

	print_mark((void**)mark, row, col);

	queue<Point> queuePoint;
	queuePoint.push(startP);
	// ������ǰ���ڵ�����Ϊ�Լ�
	mark[startP.row][startP.col] = startP;

	while(!queuePoint.empty())
	{
		print_mark((void**)mark, row, col);

		Point pointFront = queuePoint.front();
		queuePoint.pop();

		// �Ͻڵ���ͨ
		if(pointFront.row - 1 >= 0 && maze2d[pointFront.row - 1][pointFront.col] == 0)
		{
			// �Ͻڵ�δ������
			if(mark[pointFront.row - 1][pointFront.col] == Point())
			{
				mark[pointFront.row - 1][pointFront.col] = pointFront;
				queuePoint.push(Point(pointFront.row - 1, pointFront.col));
				if(Point(pointFront.row - 1, pointFront.col) == endP)	// �ҵ��յ�
					break;
			}
		}

		if(pointFront.col+1<col && maze2d[pointFront.row][pointFront.col+1]==0){//�ҽڵ���ͨ
			if(mark[pointFront.row][pointFront.col+1]==Point()){//�ҽڵ�δ�����ʣ����������������
				mark[pointFront.row][pointFront.col+1]=pointFront;
				queuePoint.push(Point(pointFront.row,pointFront.col+1));    //��ջ
				if(Point(pointFront.row,pointFront.col+1)==endP){ //�ҵ��յ�
					break;
				}
			}
		}

		if(pointFront.row+1<row && maze2d[pointFront.row+1][pointFront.col]==0){//�½ڵ���ͨ
			if(mark[pointFront.row+1][pointFront.col]==Point()){//�½ڵ�δ�����ʣ����������������
				mark[pointFront.row+1][pointFront.col]=pointFront;
				queuePoint.push(Point(pointFront.row+1,pointFront.col));    //��ջ
				if(Point(pointFront.row+1,pointFront.col)==endP){ //�ҵ��յ�
					break;
				}
			}
		}

		if(pointFront.col-1>=0 && maze2d[pointFront.row][pointFront.col-1]==0){//��ڵ���ͨ
			if(mark[pointFront.row][pointFront.col-1]==Point()){//�Ͻڵ�δ�����ʣ����������������
				mark[pointFront.row][pointFront.col-1]=pointFront;
				queuePoint.push(Point(pointFront.row,pointFront.col-1));    //��ջ
				if(Point(pointFront.row,pointFront.col-1)==endP){ //�ҵ��յ�
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