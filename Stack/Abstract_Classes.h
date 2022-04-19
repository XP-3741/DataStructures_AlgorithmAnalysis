#pragma once
#include<iostream>
#include<sstream>
#include<string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// C++������ջ
template<class T>
class stack
{
public:
	virtual ~stack() {}
	virtual bool empty() const = 0;
			// ���� true,���ҽ���ջΪ��
	virtual int size() const = 0;
			// ����ջ�е�Ԫ�ظ���
	virtual T& top() = 0;
			// ����ջ��Ԫ�ص�����
	virtual void pop() = 0;
			// ɾ��ջ��Ԫ��
	virtual void push(const T& theElement) = 0;
			// ��Ԫ�� theElement ѹ��ջ��
};

class stackEmpty
{

};
