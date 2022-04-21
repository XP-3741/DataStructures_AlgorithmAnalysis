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
{// ��Ԫ�� theElement �������

	// �����Ҫ,���������鳤��
	if ((theBack + 1) % arrayLength == theFront)
	{// �ӱ����鳤��

		// �����µ�����ռ�
		T* newQueue = new T[arrayLength * 2];

		// ��ԭ����Ԫ�ظ��Ƶ�������
		int start = (theFront + 1) % arrayLength;
		if (start < 2)
			// û���γɻ�
			std::copy(queue + start, queue + start + arrayLength - 1, newQueue);
		else
		{	// �����γɻ�
			std::copy(queue + start, queue + arrayLength, newQueue);
			std::copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}

		// �����¶����׺�βԪ�ص�λ��
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;			// ���г���-1
		arrayLength *= 2;
		delete[]queue;
		queue = newQueue;
	}
	// ��Ԫ�� theElement ���뵽����β��
	queueBack = (queueBack + 1) % arrayLength;
	queue[queueBack] = theElement;
}

template<class T>
void arrayQueue<T>::pop()
{// ɾ��������Ԫ��
	if (theFront == theBack)
		throw queueEmpty();
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();			// ��T����
}