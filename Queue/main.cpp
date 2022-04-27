#include<iostream>
#include<queue>

int main()
{


	return 0;
}

/* --------------------------------------- 列车车厢重排 --------------------------------------- */

/* ----------------------------------------- 电路布线 ----------------------------------------- */
struct position
{
	int row;
	int col;
}start, finish;

int pathLength;

const int size = 5;
int grid[size + 2][size + 2] =
{
	{1,1,1,1,1,1,1},
	{1,0,1,1,0,0,1},
	{1,0,0,0,0,1,1},
	{1,1,0,1,1,1,1},
	{1,1,0,0,1,1,1},
	{1,0,0,1,0,0,1},
	{1,1,1,1,1,1,1}
};

position* path;

bool findPath()
{// 寻找从开始到终点的最短路径
 // 找到时,返回true,否则返回false

	if ((start.row == finish.row) && (start.col == finish.row))
	{// 始点 == 终点
		pathLength = 0;
		return true;
	}

	// 初始化偏移量
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// 右
	offset[1].row = 1;	offset[1].col = 0;		// 下
	offset[2].row = 0;	offset[2].col = -1;		// 左
	offset[3].row = -1;	offset[3].col = 0;		// 上

	// 初始化迷宫外围的障碍墙
	for (int i = 0; i <= size + 1; i++)
	{
		grid[0][i] = grid[size + 1][i] = 1;		// 底部和顶部
		grid[i][0] = grid[i][size + 1] = 1;		// 左和右
	}

	position here = start;
	grid[start.row][start.col] = 2;				// 标记
	int numOfNbrs = 4;							// 一个方格相邻位置数

	// 对可达到的位置做标记
	std::queue<position> q;
	position nbr;
	do {// 给相临位置做标记
		for (int i = 0; i < numOfNbrs; i++)
		{// 检查相临位置
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == 0)
			{// 对不可标记的nbr做标记
				grid[nbr.row][nbr.col]
					= grid[here.row][here.col] + 1;
				if ((nbr.row == finish.row) &&
					(nbr.col == finish.col))	break;		// 标记完成
				// 把后者插入队列
				q.push(nbr);
			}
		}

		// 是否到达终点
		if ((nbr.row == finish.row) &&
			(nbr.col == finish.col))	break;		// 到达

		// 终点不可到达,可以移到nbr嘛
		if (q.empty())
			return false;							// 路径不存在
		here = q.front();							// 取下一个位置
		q.pop();
	} while (true);

	// 构造路径
	pathLength = grid[finish.row][finish.col] - 2;
	path = new position[pathLength];

	// 从终点回溯
	here = finish;
	for (int j = pathLength - 1; j >= 0; j--)
	{
		path[j] = here;
		// 寻找祖先位置
		for (int i = 0; i < numOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == j + 2)	break;
		}
		here = nbr;						// 移向祖先
	}
	return true;
}

/* ----------------------------------------- 原图识别 ----------------------------------------- */
int pixel[size + 2][size + 2] =
{
	{1,1,1,1,1,1,1},
	{1,0,1,1,0,0,1},
	{1,0,0,0,0,1,1},
	{1,1,0,1,1,1,1},
	{1,1,0,0,1,1,1},
	{1,0,0,1,0,0,1},
	{1,1,1,1,1,1,1}
};

void labelComponents()
{// 给图元编号

	// 初始化数组 offset
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// 右
	offset[1].row = 1;	offset[1].col = 0;		// 下
	offset[2].row = 0;	offset[2].col = -1;		// 左
	offset[3].row = -1;	offset[3].col = 0;		// 上

	// 初始化 0 值像素围墙
	for (int i = 0; i <= size + 1; i++)
	{
		pixel[0][i] = pixel[size + 1][i] = 0;	// 底部和顶部
		pixel[i][0] = pixel[i][size + 1] = 0;	// 左和右
	}

	int numOfNbrs = 4;

	// 扫描所有像素,标记图元
	std::queue<position> q;
	position here, nbr;
	int id = 1;									// 图元 id
	for(int r=1;r<=size;r++)					// 图像的行 r
		for(int c=1;c<=size;c++)				// 图像的列 c
			if (pixel[r][c] == 1)
			{// 新图元
				pixel[r][c] = ++id;				// 取下一个 id
				here.row = r;
				here.col = c;

				while (true)
				{// 寻找其余的图元
					for (int i = 0; i < numOfNbrs; i++)
					{// 检查所有相临位置
						nbr.row = here.row + offset[i].row;
						nbr.col = here.col + offset[i].col;
						if (pixel[nbr.row][nbr.col] == 1)
						{// 像素是当前图元的一部分
							pixel[nbr.row][nbr.col] = id;
							q.push(nbr);
						}
					}

					// 图元中任意未考察对象
					if (q.empty())	break;
					here = q.front();			// 一个图元像素
					q.pop();
				}
												// 结束 if
			}
}