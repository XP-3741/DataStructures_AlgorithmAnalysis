#include"Array_Description.h"
#include"Chained_Description.h"

void printMatchedPairs(string);	// 括号匹配
void towersOfHanoi(int, string, string, string);	// 汉诺塔_递归方法
void towersOfHanoi(int n);		// 函数 moveAndShow 的预处理程序
void moveAndShow(int, int, int, int);	// 汉诺塔_用栈求解

int main()
{
	string input = "(fuck ( you ( ) ye)))";
	printMatchedPairs(input);

	towersOfHanoi(5, "1", "2", "3");

	towersOfHanoi(5);
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