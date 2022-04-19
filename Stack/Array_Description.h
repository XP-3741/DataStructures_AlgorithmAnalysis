#pragma once
#include"Abstract_Classes.h"

// 类 arrayStack
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
		stack[stackTop--].~T();		// T 的析构函数
	}
	void push(const T& theElement);
	void showState() 
		{ for (int i = 0; i <= stackTop; i++) cout << stack[i] << " "; cout << endl; }

private:
	int stackTop;		// 当前栈顶
	int arrayLength;	// 栈容量
	T* stack;			// 元素数组
};

template<class T>
arrayStack<T>::arrayStack(int initalCapacity)
{// 构造函数
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

// 改变一个一维数组长度
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0);
	//throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];							// 新数组
	int number = std::min(oldLength, newLength);		// 需要复制的元素个数
	std::copy(a, a + number, temp);
	delete[] a;											// 释放老数组的内存空间
	a = temp;
}

template<class T>
void arrayStack<T>::push(const T& theElement)
{// 将元素 theELement 压入栈
	if (stackTop == arrayLength - 1)
	{// 空间已满,容量加倍
		changeLength1D(stack, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}

	// 在栈顶插入
	stack[++stackTop] = theElement;
}
