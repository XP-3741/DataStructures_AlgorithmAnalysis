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
{// 把元素 theElement 插入到队列尾部

	// 申请新元素结点
	chainNode<T>* newNode = new chainNode<T>(theElement, NULL);

	// 把新结点插入到队尾
	if (queueSIze == 0)
		queueFront = newNode;			// 队列空
	else
		queueBack->next = newNode;		// 队列不空
	queueBack = newNode;

	queueSIze++;
}

template<class T>
void linkedQueue<T>::pop()
{// 删除队列首元素
	if (queueFront == NULL)
		throw queueEmpty();

	chanNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSIze--;
}
