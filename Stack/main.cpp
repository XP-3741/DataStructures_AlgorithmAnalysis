#include"Array_Description.h"
#include"Chained_Description.h"

void printMatchedPairs(string);	// ����ƥ��
void towersOfHanoi(int, string, string, string);	// ��ŵ��_�ݹ鷽��
void towersOfHanoi(int n);		// ���� moveAndShow ��Ԥ�������
void moveAndShow(int, int, int, int);	// ��ŵ��_��ջ���

int main()
{
	string input = "(fuck ( you ( ) ye)))";
	printMatchedPairs(input);

	towersOfHanoi(5, "1", "2", "3");

	towersOfHanoi(5);
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