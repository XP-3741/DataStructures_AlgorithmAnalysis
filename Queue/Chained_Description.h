#pragma once
#include"Abstract_Classes.h"

template<class T>
class linkedQueue :public queue_
{
private:
	int queueSIze;
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
public:
	bool empty() const;
	int size() const;
	T& front();
	T& back();
	void push(const T& theElement);
	void pop();
};

template<class T>
void linkedQueue<T>::push(const T& theElement)
{// ��Ԫ�� theElement ���뵽����β��

	// ������Ԫ�ؽ��
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);

	// ���½����뵽��β
	if (queueSIze == 0)
		queueFront = newNode;			// ���п�
	else
		queueBack->next = newNode;		// ���в���
	queueBack = newNode;

	queueSIze++;
}

template<class T>
void linkedQueue<T>::pop()
{// ɾ��������Ԫ��
	if (queueFront == NULL)
		throw queueEmpty();

	chanNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSIze--;
}
