// 抽象类队列
#pragma once

#include<algorithm>

template<class T>
class queue_
{
public:
	virtual ~queue() {}
	virtual bool empty() const = 0;
							// 返回 true,当且仅当队列为空
	virtual int size() const = 0;
							// 返回队列中元素个数
	virtual T& front() = 0;
							// 返回头元素的引用
	virtual T& back() = 0;
							// 返回尾元素的引用
	virtual void pop() = 0;
							// 删除首元素
	virtual void push(const T& theElement) = 0;
							// 把元素 theElement 加入队列
};

void queueEmpty()
{

}
