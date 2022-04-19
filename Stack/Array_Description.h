#pragma once
#include"Abstract_Classes.h"

// �� arrayStack
template<class T>
class arrayStack :public stack<T>
{
public:
	arrayStack(int initalCapcity = 10);
	~arrayStack() { delete[]stack; }
	bool empty()const { return stackTop == -1; }
	int size() const
		{return stackTop + 1;}
	T& top()
	{
		if (stackTop == -1)
			throw stackEmpty();
		return stack[stackTop];
	}
	void pop()
	{
		if (stackTop == -1)
			throw stackEmpty();
		stack[stackTop--].~T();		// T ����������
	}
	void push(const T& theElement);
	void showState() 
		{ for (int i = 0; i <= stackTop; i++) cout << stack[i] << " "; cout << endl; }

private:
	int stackTop;		// ��ǰջ��
	int arrayLength;	// ջ����
	T* stack;			// Ԫ������
};

template<class T>
arrayStack<T>::arrayStack(int initalCapacity)
{// ���캯��
	if (initalCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << initalCapacity << " Must be > 0";
		//throw illegalParameterValue(s.str());
	}
	arrayLength = initalCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

// �ı�һ��һά���鳤��
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0);
	//throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];							// ������
	int number = std::min(oldLength, newLength);		// ��Ҫ���Ƶ�Ԫ�ظ���
	std::copy(a, a + number, temp);
	delete[] a;											// �ͷ���������ڴ�ռ�
	a = temp;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{// ��Ԫ�� theELement ѹ��ջ
	if (stackTop == arrayLength - 1)
	{// �ռ�����,�����ӱ�
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// ��ջ������
	stack[++stackTop] = theElement;
}
