#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include <algorithm>

// һ�����Ա�ĳ�����
template<class T>
class linearList
{
public:
	virtual ~linearList() {};
	virtual bool empty() const = 0;
	// ���� true, ���ҽ������Ա�Ϊ��
	virtual int size() const = 0;
	// �������Ա��Ԫ�ظ���
	virtual T& get(int theIndex) const = 0;
	// ��������Ϊ theIndex ��Ԫ��
	virtual int indexOf(const T& theElement) const = 0;
	// ����Ԫ�� theElement ��һ�γ���ʱ������
	virtual void erase(int theIndex) = 0;
	// ɾ������Ϊ theIndex ��Ԫ��
	virtual void insert(int theIndex, const T& theElement) = 0;
	// �� theElement �������Ա�������Ϊ theIndex ��λ����
	virtual void output(std::ostream& out)const = 0;
	// �����Ա��������� out
};
