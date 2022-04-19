#pragma once
#include<iostream>
#include<sstream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// C++抽象类栈
template<class T>
class stack
{
public:
	virtual ~stack() {}
	virtual bool empty() const = 0;
			// 返回 true,当且仅当栈为空
	virtual int size() const = 0;
			// 返回栈中的元素个数
	virtual T& top() = 0;
			// 返回栈顶元素的引用
	virtual void pop() = 0;
			// 删除栈顶元素
	virtual void push(const T& theElement) = 0;
			// 将元素 theElement 压入栈顶
};

class stackEmpty
{

};
