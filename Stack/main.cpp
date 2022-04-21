#include"Array_Description.h"
#include"Chained_Description.h"

void printMatchedPairs(string);	// ����ƥ��
void towersOfHanoi(int, string, string, string);	// ��ŵ��_�ݹ鷽��
void towersOfHanoi(int n);		// ���� moveAndShow ��Ԥ�������
void moveAndShow(int, int, int, int);	// ��ŵ��_��ջ���
bool railroad(int[], int, int);		// �г���������
bool checkBox(int[], int);		// ���غв���
bool findPath();	// �Թ�����

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

/*-------------------------------------����ƥ��-------------------------------------*/
void printMatchedPairs(string expr)
{
	arrayStack<int> s;
	int length = (int)expr.size();

	// ɨ����ʽ expr Ѱ�������ź�������
	for (int i = 0; i < length; i++)
		if (expr.at(i) == '(')
			s.push(i);
		else
			if(expr.at(i)==')')
				try {
					// ��ջ��ɾ��ƥ���������
					cout << s.top() << ' ' << i << endl;
					s.pop();	// û��ջƥ��
				}
				catch (stackEmpty)
				{
					cout << "No match for right parenthesis"
						<< " at " << i << endl;
				}
	// ջ��Ϊ��,ʣ�ಿ����ջ�е��������ǲ�ƥ���
	while (!s.empty())
	{
		cout << "No match for left parenthesis at "
			<< s.top() << endl;
		s.pop();
	}
}

/*--------------------------------------��ŵ��--------------------------------------*/
// ��ŵ��_�ݹ鷽��
void towersOfHanoi(int n, string x, string y, string z)
{// ���� x ������ n �������Ƶ��� y
 // ���� z ��Ϊ��ת��
	if (n > 0)
	{
		towersOfHanoi(n - 1, x, z, y);
		cout << "Move top disk from tower " << x
			<< " to top of tower " << y << endl;
		towersOfHanoi(n - 1, z, y, x);
	}
}

// ��ŵ��_��ջ���
arrayStack<int> tower[4];		// ȫ�ֱ���, tower[1:3] ��ʾ������

void towersOfHanoi(int n)
{// ���� moveAndShow ��Ԥ�������
	for (int d = n; d > 0; d--)			// ��ʼ��
		tower[1].push(d);				// �ѵ��� d �ӵ��� 1
	
	// �� n �����Ӵ��� 1 �Ƶ��� 3,���� 2 ��Ϊ��תվ
	moveAndShow(n, 1, 2, 3);
}

void moveAndShow(int n, int x, int y, int z)
{// ���� x ������ n �������Ƶ��� y,��ʾ�ƶ���Ĳ���
 // ���� z ��Ϊ��תվ
	if (n > 0)
	{
		moveAndShow(n - 1, x, z, y);
		int d = tower[x].top();			// ��һ������
		tower[x].pop();					// ���� x �����Ƶ�
		tower[y].push(d);				// �� y �Ķ���
		cout << "��2: "; tower[2].showState();			// ��ʾ�� 3 �Ĳ���
		moveAndShow(n - 1, z, y, x);
	}
}

/*-----------------------------------�г���������-----------------------------------*/
// ȫ�ֱ���
arrayStack<int>* track;			// ����������
int numberOfCars;
int numberOfTracks;
int smallestCar;				// �ڻ������б����С�ĳ���
int itsTrack;					// ͣ������С��ų���Ļ�����

void outputFromHoldingTrack();
bool putInHoldingTrack(int c);

bool railroad(int inputOrder[], int theNumberOfCars, int theNumberOfTracks)
{// �ӳ�ʼ��˳��ʼ���ų���
 // ������ųɹ�,���� true,���򷵻� false

	numberOfCars = theNumberOfCars;
	numberOfTracks = theNumberOfTracks;

	// �������ڻ�������ջ
	track = new arrayStack<int>[numberOfTracks + 1];

	int nextCarToOutput = 1;
	smallestCar = numberOfCars + 1;			// ���������޳���

	// ���ų���
	for (int i = 1; i <= numberOfCars; i++)
		if (inputOrder[i] == nextCarToOutput)
		{// ������ inputOrder[i] ֱ���Ƶ����쵽
			cout << "Move car " << inputOrder[i]
				<< " from input track to output track" << endl;
			nextCarToOutput++;

			// �ӻ������Ƶ������
			while (smallestCar == nextCarToOutput)
			{
				outputFromHoldingTrack();
				nextCarToOutput++;
			}
		}
		else
			// ������ inputOrder[i] �Ƶ�һ��������
			if (!putInHoldingTrack(inputOrder[i]))
				return false;

	return true;
}

void outputFromHoldingTrack()
{// �������С�ĳ��Ỻ�����Ƶ������

	// ��ջ itsTrack ��ɾ�������С�ĳ���
	track[itsTrack].pop();
	cout << "Move car " << smallestCar << " from holding "
		<< "track " << itsTrack << " to output track" << endl;

	// �������ջ��ջ��,Ѱ�ұ����С�ĳ������������ջ itsTrack
	smallestCar = numberOfCars + 2;
	for (int i = 1; i <= numberOfTracks; i++)
		if (!track[i].empty() && (track[i].top() < smallestCar))
		{
			smallestCar = track[i].top();
			itsTrack = i;
		}
}

bool putInHoldingTrack(int c)
{// ������ c �Ƶ�һ��������.���� false ,���ҽ���û�п��õĻ�����

	// Ϊ���� c Ѱ������ʵĻ�����
	// ��ʼ��
	int bestTrack = 0,					// Ŀǰ����ʵĻ�����
		bestTop = numberOfCars + 1;		// ȡ bestTrack �ж����ĳ���

	// ɨ�軺����
	for (int i = 1; i <= numberOfTracks; i++)
		if (!track[i].empty())
		{// ������ i ����
			int topCar = track[i].top();
			if (c < topCar && topCar < bestTop)
			{// ������ i ��ջ�����б�Ÿ�С�ĳ���
				bestTop = topCar;
				bestTrack = i;
			}
		}
		else // ������ i Ϊ��
			if (bestTrack == 0)	bestTrack = i;

	if (bestTrack == 0) return false;		// û�п��õĻ�����

	// �ѳ��� c �Ƶ���� bestTrack
	track[bestTrack].push(c);
	cout << "Move car " << c << " from input track "
		<< "to holding track " << bestTrack << endl;

	// �����Ҫ,���� smallestCar �� itsTrack
	if (c < smallestCar)
	{
		smallestCar = c;
		itsTrack = bestTrack;
	}

	return true;
}

/*-------------------------------------���غв���-------------------------------------*/
bool checkBox(int net[], int n)		/* n */
{// ȷ�����غ��Ƿ�ɲ���
 // ���� net[0..n-1] �ܽ�����,�����γ�����
 // n �ǹܽŸ���

	arrayStack<int>* s = new arrayStack<int>(n);

	// ��˳ʱ��ɨ������
	for (int i = 0; i < n; i++)
		// ����ܽ� i
		if (!s->empty())
			// ���ջ�Ķ����ܽ�
			if (net[i] == net[s->top()])
				// �ܽ� net[i] �ǿɲ��ߵ�,��ջ��ɾ��
				s->pop();
			else  s->push(i);
		else  s->push(i);

	// �Ƿ���ʣ��Ĳ��ɲ��ߵĹܽ�
	if (s->empty())
	{// û��ʣ��Ĺܽ�
		cout << "Switch box is routable" << endl;
		return true;
	}

	cout << "Switch box is not routable" << endl;
	return false;
}

/*-----------------------------------���ߵȼ�������-----------------------------------*/


/*--------------------------------------�Թ�����--------------------------------------*/
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
{// Ѱ��һ�������(1,1)�������(size,size)��·��
 // ����ҵ�,����true,���򷵻�false

	arrayStack<position>* path = new arrayStack<position>;

	// ��ʼ��ƫ����
	position offset[4];
	offset[0].row = 0;	offset[0].col = 1;		// ��
	offset[1].row = 1;	offset[1].col = 1;		// ��
	offset[2].row = 0;	offset[2].col = -1;		// ��
	offset[3].row = -1;	offset[3].col = 1;		// ��

	// ��ʼ���Թ���Χ���ϰ�ǽ
	for (int i = 0; i <= size + 1; i++)
	{
		maze[0][i] = maze[size + 1][i] = 1;		// �ײ��Ͷ���
		maze[i][0] = maze[i][size + 1] = 1;		// �����
	}

	position here;
	here.col = 1;
	here.row = 1;
	maze[1][1] = 1;								// ��ֹ�ص����
	int option = 0;								// ��һ��
	int lastOption = 3;

	// Ѱ��һ��·��
	while (here.col != size || here.row != size)
	{// û�е������
		// �ҵ�Ҫ�ƶ������ڵ�һ��
		int r, c;
		while (option <= lastOption)
		{
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)	break;
			option++;							// ��һ��ѡ��
		}

		// ���ڵ�һ���Ƿ��ҵ���
		if (option <= lastOption)
		{// �Ƶ�maze[r][c]
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 1;						// ����1,�Է��ظ�����
			option = 0;
		}
		else
		{// û���ٽ���һ������,����
			if (path->empty())					// û��λ�ÿɷ���
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
	return true;								// �������
}