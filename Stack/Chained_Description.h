#pragma once
#include"Abstract_Classes.h"

// ����ڵ�Ľṹ����
template<class T>
struct chainNode
{
	// ���ݳ�Ա
	T element;
	chainNode<T>* next;

	// ����
	chainNode() {}
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};

template<class T>
class linkedStack :public stack<T>
{
public:
	linkedStack(int initialCapacity = 10)
		{stackTop = NULL; stackSize = 0;}
	~linkedStack();
	bool empty() const
		{return stackSize == 0;}
	int size() const
		{return stackSize;}
	T& top()
	{
		if (stackSize == 0)
			throw stackEmpty();
		return stackTop->element;
	}
	void pop();
	void push(const T& theElement)
	{
		stackTop = new chainNode<T>(theElement, stackTop);
		stackSize++;
	}
private:
	chainNode<T>* stackTop;		// ջ��ָ��
	int stackSize;				// ջ�е�Ԫ�ظ���
};

template<class T>
linkedStack<T>::~linkedStack()
{// ��������
	while (stackTop != NULL)
	{// ɾ��ջ�����
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<class T>
void linkedStack<T>::pop()
{// ɾ��ջ�����
	if (stackSize == 0)
		throw stackEmpty();

	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}
