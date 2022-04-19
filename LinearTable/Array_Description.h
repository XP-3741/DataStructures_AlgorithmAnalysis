#pragma once
#include"Abstract_Classes.h"


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

// 类 arrayList 的定义
// 抽象类 linearList 的派生类
template<class T>
class arrayList :public linearList<T>
{
public:
	// 构造函数、复制构造函数和析构函数
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[]element; }

	// ADT 方法
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	// 其他方法
	int capacity() const{ return arrayLength; }

	// 类 arrayList 的一个迭代器
	class iterator
	{
	public:
		// 用 C++ 的 typedef 语句实现双向迭代器
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// 构造函数
		iterator(T* thePosition = 0) { position = thePosition; }

		// 解析引用操作符
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// 迭代器的值增加
		iterator& operator++()				// 前加
		{
			++position; return *this;
		}
		iterator operator++(int)			// 后加
		{
			iterator old = *this;
			++position;
			return old;
		}

		// 迭代器的值减少
		iterator& operator--()				// 前加
		{
			--position; return *this;
		}
		iterator operator--(int)			// 后加
		{
			iterator old = *this;
			--position;
			return old;
		}

		// 测试是否相等
		bool operator!=(const iterator right)	const
		{
			return position != right.position;
		}
		bool operator==(const iterator right)	const
		{
			return position == right.position;
		}

	protected:
		T* position;		// 指向表元素的指针
	};
	iterator begin() {return iterator(element); }
	iterator end() {return iterator(element + listSize); }

protected:
	void checkIndex(int theIndex) const;
	// 若索引 theIndex 无效,则抛出异常
	T* element;					// 存储线性表元素的一维数组
	int arrayLength;			// 一维数组的容量
	int listSize;				// 线性表的元素个数
};

// 类 arrayList 的构造函数
template<class T>
arrayList<T>::arrayList(int initalCapacity)
{// 构造函数
	if (initalCapacity < 1)
	{
		std::ostringstream s;
		s << "Inital capacity = " << initalCapacity << " Must be > 0";
		//throw illegalParameterValue(s.str());
	}
	arrayLength = initalCapacity;
	element = new T[arrayLength];
	listSize = 0;
}
template<class T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{// 复制构造函数
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// 确定索引 theIndex 在 0 和 listSize - 1 之间
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		//throw illegalindex(s.str());
	}
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{// 返回索引为 theIndex 的元素
 // 若此元素不存在,则抛出异常
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{// 返回 theElement 第一次出现时的索引
 // 若元素不存在,则返回 -1

	// 查找元素 theElement
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);

	// 确定 theElement 是否找到
	if (theIndex == listSize)
		// 没有找到
		return -1;
	else return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{// 删除其索引为 theIndex 的元素
 // 如果该元素不存在,则抛出异常 illegalIndex
	checkIndex(theIndex);

	// 有效索引,移动其索引大于 theIndex 的元素
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();		// 调用析构函数
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// 在索引 theIndex 出插入元素 theElement
	if (theIndex<0 || theIndex>listSize)
	{// 无效索引
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		//throw illegalIndex(s.str());
	}

	// 有效索引,确定数组是否已满
	if (listSize == arrayLength)
	{// 数组空间已满,数组长度倍增
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	// 把元素向右移动一个位置
	std::copy_backward(element + theIndex, element + listSize, element + listSize +1);

	element[theIndex] = theElement;

	listSize++;
}

// 把一个线性表插入输出流
template<class T>
void arrayList<T>::output(std::ostream &out) const
{// 把线性表插入输出流
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "  "));
}
// 重载 <<
template<class T>
std::ostream& operator << (std::ostream & out, const arrayList<T>&x)
{
	x.output(out);
	return out;
}

// 利用 vector 实现基于数组的线性表
template<class T>
class vectorList :public linearList<T>
{
public:
	// 构造函数、复制构造函数和析构函数
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList() { delete element; }

	// ADT 方法
	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	// 增加的方法
	int capacity() const{ return (int)element->capacity(); }

	// 线性表的起始和结束位置的迭代器
	typedef typename std::vector<T>::iterator iterator;
	iterator begin() { return iterator(element->begin()); }
	iterator end() { return iterator(element->end()); }

protected:					// 增加的成员 
	void checkIndex(int theIndex) const;
	std::vector<T>* element;		// 存储线性表元素的向量
};

// vectorList 的构造函数
template<class T>
vectorList<T>::vectorList(int initalCapacity)
{// 构造函数
	if (initalCapacity < 1)
	{
		std::ostringstream s;
		s << "Inital capacity = " << initalCapacity << " Must be > 0";
		//throw illegalParameterValue(s.str());
	}
	element = new std::vector<T>;
			// 创建容量为 0 的空向量
	element->reserve(initalCapacity);
			// vecotr 容量从 0 增加到 initalCapacity
}

template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{// 复制构造函数
	element = new std::vector<T>(*theList.element);
}

// vectorList 的删除和插入
template<class T>
void vectorList<T>::erase(int theIndex)
{// 删除索引为 theIndex 的元素
 // 如果没有这个元素,则抛出异常
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{// 在索引为 theIndex 处插入元素 theElement
	if (theIndex<0 || theIndex>size())
	{// 无效索引
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		//throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}
