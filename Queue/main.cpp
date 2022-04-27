#include<iostream>
#include<queue>

int main()
{


	return 0;
}

/* --------------------------------------- �г��������� --------------------------------------- */

/* ----------------------------------------- ��·���� ----------------------------------------- */
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
{// Ѱ�Ҵӿ�ʼ���յ�����·��
 // �ҵ�ʱ,����true,���򷵻�false

	if ((start.row == finish.row) && (start.col == finish.row))
	{// ʼ�� == �յ�
		pathLength = 0;
		return true;
	}

	// ��ʼ��ƫ����
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// ��
	offset[1].row = 1;	offset[1].col = 0;		// ��
	offset[2].row = 0;	offset[2].col = -1;		// ��
	offset[3].row = -1;	offset[3].col = 0;		// ��

	// ��ʼ���Թ���Χ���ϰ�ǽ
	for (int i = 0; i <= size + 1; i++)
	{
		grid[0][i] = grid[size + 1][i] = 1;		// �ײ��Ͷ���
		grid[i][0] = grid[i][size + 1] = 1;		// �����
	}

	position here = start;
	grid[start.row][start.col] = 2;				// ���
	int numOfNbrs = 4;							// һ����������λ����

	// �Կɴﵽ��λ�������
	std::queue<position> q;
	position nbr;
	do {// ������λ�������
		for (int i = 0; i < numOfNbrs; i++)
		{// �������λ��
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == 0)
			{// �Բ��ɱ�ǵ�nbr�����
				grid[nbr.row][nbr.col]
					= grid[here.row][here.col] + 1;
				if ((nbr.row == finish.row) &&
					(nbr.col == finish.col))	break;		// ������
				// �Ѻ��߲������
				q.push(nbr);
			}
		}

		// �Ƿ񵽴��յ�
		if ((nbr.row == finish.row) &&
			(nbr.col == finish.col))	break;		// ����

		// �յ㲻�ɵ���,�����Ƶ�nbr��
		if (q.empty())
			return false;							// ·��������
		here = q.front();							// ȡ��һ��λ��
		q.pop();
	} while (true);

	// ����·��
	pathLength = grid[finish.row][finish.col] - 2;
	path = new position[pathLength];

	// ���յ����
	here = finish;
	for (int j = pathLength - 1; j >= 0; j--)
	{
		path[j] = here;
		// Ѱ������λ��
		for (int i = 0; i < numOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == j + 2)	break;
		}
		here = nbr;						// ��������
	}
	return true;
}

/* ----------------------------------------- ԭͼʶ�� ----------------------------------------- */
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
{// ��ͼԪ���

	// ��ʼ������ offset
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// ��
	offset[1].row = 1;	offset[1].col = 0;		// ��
	offset[2].row = 0;	offset[2].col = -1;		// ��
	offset[3].row = -1;	offset[3].col = 0;		// ��

	// ��ʼ�� 0 ֵ����Χǽ
	for (int i = 0; i <= size + 1; i++)
	{
		pixel[0][i] = pixel[size + 1][i] = 0;	// �ײ��Ͷ���
		pixel[i][0] = pixel[i][size + 1] = 0;	// �����
	}

	int numOfNbrs = 4;

	// ɨ����������,���ͼԪ
	std::queue<position> q;
	position here, nbr;
	int id = 1;									// ͼԪ id
	for(int r=1;r<=size;r++)					// ͼ����� r
		for(int c=1;c<=size;c++)				// ͼ����� c
			if (pixel[r][c] == 1)
			{// ��ͼԪ
				pixel[r][c] = ++id;				// ȡ��һ�� id
				here.row = r;
				here.col = c;

				while (true)
				{// Ѱ�������ͼԪ
					for (int i = 0; i < numOfNbrs; i++)
					{// �����������λ��
						nbr.row = here.row + offset[i].row;
						nbr.col = here.col + offset[i].col;
						if (pixel[nbr.row][nbr.col] == 1)
						{// �����ǵ�ǰͼԪ��һ����
							pixel[nbr.row][nbr.col] = id;
							q.push(nbr);
						}
					}

					// ͼԪ������δ�������
					if (q.empty())	break;
					here = q.front();			// һ��ͼԪ����
					q.pop();
				}
												// ���� if
			}
}