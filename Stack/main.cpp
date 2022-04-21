#include"Array_Description.h"
#include"Chained_Description.h"

void printMatchedPairs(string);	// 括号匹配
void towersOfHanoi(int, string, string, string);	// 汉诺塔_递归方法
void towersOfHanoi(int n);		// 函数 moveAndShow 的预处理程序
void moveAndShow(int, int, int, int);	// 汉诺塔_用栈求解
bool railroad(int[], int, int);		// 列车车厢重排
bool checkBox(int[], int);		// 开关盒布线
bool findPath();	// 迷宫老鼠

int main()
{
	string input = "(fuck ( you ( ) ye)))";
	printMatchedPairs(input);

	towersOfHanoi(5, "1", "2", "3");

	towersOfHanoi(5);

	int inputOrder[10] = { -1,5,7,2,1,9,6,3,8,4 };
	if (railroad(inputOrder, 9, 5))
		cout << "Railroad success\n";

	int net[8] = { 1,2,2,1,3,3,4,4 };
	checkBox(net, 8);

	if (findPath())	cout << "FindPath success\n";
	else   cout << "FindPath fail\n";

	return 0;
}

/*-------------------------------------括号匹配-------------------------------------*/
void printMatchedPairs(string expr)
{
	arrayStack<int> s;
	int length = (int)expr.size();

	// 扫描表达式 expr 寻找左括号和右括号
	for (int i = 0; i < length; i++)
		if (expr.at(i) == '(')
			s.push(i);
		else
			if(expr.at(i)==')')
				try {
					// 从栈中删除匹配的左括号
					cout << s.top() << ' ' << i << endl;
					s.pop();	// 没有栈匹配
				}
				catch (stackEmpty)
				{
					cout << "No match for right parenthesis"
						<< " at " << i << endl;
				}
	// 栈不为空,剩余部分在栈中的左括号是不匹配的
	while (!s.empty())
	{
		cout << "No match for left parenthesis at "
			<< s.top() << endl;
		s.pop();
	}
}

/*--------------------------------------汉诺塔--------------------------------------*/
// 汉诺塔_递归方法
void towersOfHanoi(int n, string x, string y, string z)
{// 把塔 x 顶部的 n 个碟子移到塔 y
 // 用塔 z 作为中转地
	if (n > 0)
	{
		towersOfHanoi(n - 1, x, z, y);
		cout << "Move top disk from tower " << x
			<< " to top of tower " << y << endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}

// 汉诺塔_用栈求解
arrayStack<int> tower[4];		// 全局变量, tower[1:3] 表示三个塔

void towersOfHanoi(int n)
{// 函数 moveAndShow 的预处理程序
	for (int d = n; d > 0; d--)			// 初始化
		tower[1].push(d);				// 把碟子 d 加到塔 1
	
	// 把 n 个碟子从塔 1 移到塔 3,用塔 2 作为中转站
	moveAndShow(n, 1, 2, 3);
}

void moveAndShow(int n, int x, int y, int z)
{// 把塔 x 顶部的 n 个碟子移到塔 y,显示移动后的布局
 // 用塔 z 作为中转站
	if (n > 0)
	{
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();			// 把一个碟子
		tower[x].pop();					// 从塔 x 顶部移到
		tower[y].push(d);				// 塔 y 的顶部
		cout << "塔2: "; tower[2].showState();			// 显示塔 3 的布局
		moveAndShow(n - 1, z, y, x);
	}
}

/*-----------------------------------列车车厢重排-----------------------------------*/
// 全局变量
arrayStack<int>* track;			// 缓冲轨道数组
int numberOfCars;
int numberOfTracks;
int smallestCar;				// 在缓冲轨道中编号最小的车厢
int itsTrack;					// 停靠着最小编号车厢的缓冲轨道

void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{// 从初始化顺序开始重排车厢
 // 如果重排成功,返回 true,否则返回 false

	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;

	// 创建用于缓冲轨道的栈
	track = new arrayStack<int>[numberOfTracks + 1];

	int nextCarToOutput = 1;
	smallestCar = numberOfCars + 1;			// 缓冲轨道中无车厢

	// 重排车厢
	for (int i = 1; i <= numberOfCars; i++)
		if (inputOrder[i] == nextCarToOutput)
		{// 将车厢 inputOrder[i] 直接移到出轨到
			cout << "Move car " << inputOrder[i]
				<< " from input track to output track" << endl;
			nextCarToOutput++;

			// 从缓冲轨道移到出轨道
			while (smallestCar == nextCarToOutput)
			{
				outputFromHoldingTrack();
				nextCarToOutput++;
			}
		}
		else
			// 将车厢 inputOrder[i] 移到一个缓冲轨道
			if (!putInHoldingTrack(inputOrder[i]))
				return false;

	return true;
}

void outputFromHoldingTrack()
{// 将编号最小的车厢缓冲轨道移到出轨道

	// 从栈 itsTrack 中删除编号最小的车厢
	track[itsTrack].pop();
	cout << "Move car " << smallestCar << " from holding "
		<< "track " << itsTrack << " to output track" << endl;

	// 检查所有栈的栈顶,寻找编号最小的车厢和它所属的栈 itsTrack
	smallestCar = numberOfCars + 2;
	for (int i = 1; i <= numberOfTracks; i++)
		if (!track[i].empty() && (track[i].top() < smallestCar))
		{
			smallestCar = track[i].top();
			itsTrack = i;
		}
}

bool putInHoldingTrack(int c)
{// 将车厢 c 移到一个缓冲轨道.返回 false ,当且仅当没有可用的缓冲轨道

	// 为车厢 c 寻找最合适的缓冲轨道
	// 初始化
	int bestTrack = 0,					// 目前最合适的缓冲轨道
		bestTop = numberOfCars + 1;		// 取 bestTrack 中顶部的车厢

	// 扫描缓冲轨道
	for (int i = 1; i <= numberOfTracks; i++)
		if (!track[i].empty())
		{// 缓冲轨道 i 不空
			int topCar = track[i].top();
			if (c < topCar && topCar < bestTop)
			{// 缓冲轨道 i 的栈顶具有编号更小的车厢
				bestTop = topCar;
				bestTrack = i;
			}
		}
		else // 缓冲轨道 i 为空
			if (bestTrack == 0)	bestTrack = i;

	if (bestTrack == 0) return false;		// 没有可用的缓冲轨道

	// 把车厢 c 移到轨道 bestTrack
	track[bestTrack].push(c);
	cout << "Move car " << c << " from input track "
		<< "to holding track " << bestTrack << endl;

	// 如果需要,更新 smallestCar 和 itsTrack
	if (c < smallestCar)
	{
		smallestCar = c;
		itsTrack = bestTrack;
	}

	return true;
}

/*-------------------------------------开关盒布线-------------------------------------*/
bool checkBox(int net[], int n)		/* n */
{// 确定开关盒是否可布线
 // 数组 net[0..n-1] 管脚数组,用以形成网组
 // n 是管脚个数

	arrayStack<int>* s = new arrayStack<int>(n);

	// 按顺时针扫描网组
	for (int i = 0; i < n; i++)
		// 处理管脚 i
		if (!s->empty())
			// 检查栈的顶部管脚
			if (net[i] == net[s->top()])
				// 管脚 net[i] 是可布线的,从栈中删除
				s->pop();
			else  s->push(i);
		else  s->push(i);

	// 是否有剩余的不可布线的管脚
	if (s->empty())
	{// 没有剩余的管脚
		cout << "Switch box is routable" << endl;
		return true;
	}

	cout << "Switch box is not routable" << endl;
	return false;
}

/*-----------------------------------离线等价类问题-----------------------------------*/


/*--------------------------------------迷宫老鼠--------------------------------------*/
struct position
{
	int row;
	int col;
};

const int size = 5;
int maze[size + 2][size + 2] =
{
	{1,1,1,1,1,1,1},
	{1,0,1,1,0,0,1},
	{1,0,0,0,0,1,1},
	{1,1,0,1,1,1,1},
	{1,1,0,0,1,1,1},
	{1,0,0,1,0,0,1},
	{1,1,1,1,1,1,1}
};

bool findPath()
{// 寻找一条从入口(1,1)到达出口(size,size)的路径
 // 如果找到,返回true,否则返回false

	arrayStack<position>* path = new arrayStack<position>;

	// 初始化偏移量
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// 右
	offset[1].row = 1;	offset[1].col = 1;		// 下
	offset[2].row = 0;	offset[2].col = -1;		// 左
	offset[3].row = -1;	offset[3].col = 1;		// 上

	// 初始化迷宫外围的障碍墙
	for (int i = 0; i <= size + 1; i++)
	{
		maze[0][i] = maze[size + 1][i] = 1;		// 底部和顶部
		maze[i][0] = maze[i][size + 1] = 1;		// 左和右
	}

	position here;
	here.col = 1;
	here.row = 1;
	maze[1][1] = 1;								// 防止回到入口
	int option = 0;								// 下一步
	int lastOption = 3;

	// 寻找一条路径
	while (here.col != size || here.row != size)
	{// 没有到达出口
		// 找到要移动的相邻的一步
		int r, c;
		while (option <= lastOption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)	break;
			option++;							// 下一个选择
		}

		// 相邻的一步是否找到？
		if (option <= lastOption)
		{// 移到maze[r][c]
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;						// 设置1,以防重复访问
			option = 0;
		}
		else
		{// 没有临近的一步可走,返回
			if (path->empty())					// 没有位置可返回
				return false;
			position next = path->top();
			path->pop();
			if (next.row == here.row)
				option = 2 + next.col - here.col;
			else
				option = 3 + next.row - here.row;
			here = next;
		}
	}
	return true;								// 到达出口
}