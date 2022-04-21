#pragma once
#include"Abstract_Classes.h"

template<class T>
class arrayQueue :public queue_
{
private:
	T* queue;
	int theBack;
	int theFront;
	int queueBack;
	int queueFront;
	int arrayLength;
public:
	bool empty() const;
	int size() const;
	T& front();
	T& back();
	void push(const T& theElement);
	void pop();
};

template<class T>
void arrayQueue<T>::push(const T& theElement)
{// 把元素 theElement 加入队列

	// 如果需要,则增加数组长度
	if ((theBack + 1) % arrayLength == theFront)
	{// 加倍数组长度

		// 分配新的数组空间
		T* newQueue = new T[arrayLength * 2];

		// 把原数组元素复制到新数组
		int start = (theFront + 1) % arrayLength;
		if (start < 2)
			// 没有形成环
			std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
		else
		{	// 队列形成环
			std::copy(queue + start, queue + arrayLength, newQueue);
			std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}

		// 设置新队列首和尾元素的位置
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;			// 队列长度-1
		arrayLength *= 2;
		delete[]queue;
		queue = newQueue;
	}
	// 把元素 theElement 插入到队列尾部
	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
}

template<class T>
void arrayQueue<T>::pop()
{// 删除队列首元素
	if (theFront == theBack)
		throw queueEmpty();
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();			// 给T析构
}