#pragma once
#include"Abstract_Classes.h"


// �ı�һ��һά���鳤��
template<class T>
void changeLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0);
		//throw illegalParameterValue("new length must be >= 0");

	T* temp = new T[newLength];							// ������
	int number = std::min(oldLength, newLength);		// ��Ҫ���Ƶ�Ԫ�ظ���
	std::copy(a, a + number, temp);
	delete[] a;											// �ͷ���������ڴ�ռ�
	a = temp;
}

// �� arrayList �Ķ���
// ������ linearList ��������
template<class T>
class arrayList :public linearList<T>
{
public:
	// ���캯�������ƹ��캯������������
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[]element; }

	// ADT ����
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	// ��������
	int capacity() const{ return arrayLength; }

	// �� arrayList ��һ��������
	class iterator
	{
	public:
		// �� C++ �� typedef ���ʵ��˫�������
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// ���캯��
		iterator(T* thePosition = 0) { position = thePosition; }

		// �������ò�����
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// ��������ֵ����
		iterator& operator++()				// ǰ��
		{
			++position; return *this;
		}
		iterator operator++(int)			// ���
		{
			iterator old = *this;
			++position;
			return old;
		}

		// ��������ֵ����
		iterator& operator--()				// ǰ��
		{
			--position; return *this;
		}
		iterator operator--(int)			// ���
		{
			iterator old = *this;
			--position;
			return old;
		}

		// �����Ƿ����
		bool operator!=(const iterator right)	const
		{
			return position != right.position;
		}
		bool operator==(const iterator right)	const
		{
			return position == right.position;
		}

	protected:
		T* position;		// ָ���Ԫ�ص�ָ��
	};
	iterator begin() {return iterator(element); }
	iterator end() {return iterator(element + listSize); }

protected:
	void checkIndex(int theIndex) const;
	// ������ theIndex ��Ч,���׳��쳣
	T* element;					// �洢���Ա�Ԫ�ص�һά����
	int arrayLength;			// һά���������
	int listSize;				// ���Ա��Ԫ�ظ���
};

// �� arrayList �Ĺ��캯��
template<class T>
arrayList<T>::arrayList(int initalCapacity)
{// ���캯��
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
{// ���ƹ��캯��
	arrayLength = theList.arrayLength;
	listSize = theList.listSize;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{// ȷ������ theIndex �� 0 �� listSize - 1 ֮��
	if (theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		//throw illegalindex(s.str());
	}
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{// ��������Ϊ theIndex ��Ԫ��
 // ����Ԫ�ز�����,���׳��쳣
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{// ���� theElement ��һ�γ���ʱ������
 // ��Ԫ�ز�����,�򷵻� -1

	// ����Ԫ�� theElement
	int theIndex = (int)(std::find(element, element + listSize, theElement) - element);

	// ȷ�� theElement �Ƿ��ҵ�
	if (theIndex == listSize)
		// û���ҵ�
		return -1;
	else return theIndex;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{// ɾ��������Ϊ theIndex ��Ԫ��
 // �����Ԫ�ز�����,���׳��쳣 illegalIndex
	checkIndex(theIndex);

	// ��Ч����,�ƶ����������� theIndex ��Ԫ��
	std::copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();		// ������������
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{// ������ theIndex ������Ԫ�� theElement
	if (theIndex<0 || theIndex>listSize)
	{// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		//throw illegalIndex(s.str());
	}

	// ��Ч����,ȷ�������Ƿ�����
	if (listSize == arrayLength)
	{// ����ռ�����,���鳤�ȱ���
		changeLength1D(element, arrayLength, arrayLength * 2);
		arrayLength *= 2;
	}

	// ��Ԫ�������ƶ�һ��λ��
	std::copy_backward(element + theIndex, element + listSize, element + listSize +1);

	element[theIndex] = theElement;

	listSize++;
}

// ��һ�����Ա���������
template<class T>
void arrayList<T>::output(std::ostream &out) const
{// �����Ա���������
	copy(element, element + listSize, std::ostream_iterator<T>(std::cout, "  "));
}
// ���� <<
template<class T>
std::ostream& operator << (std::ostream & out, const arrayList<T>&x)
{
	x.output(out);
	return out;
}

// ���� vector ʵ�ֻ�����������Ա�
template<class T>
class vectorList :public linearList<T>
{
public:
	// ���캯�������ƹ��캯������������
	vectorList(int initialCapacity = 10);
	vectorList(const vectorList<T>&);
	~vectorList() { delete element; }

	// ADT ����
	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out)const;

	// ���ӵķ���
	int capacity() const{ return (int)element->capacity(); }

	// ���Ա����ʼ�ͽ���λ�õĵ�����
	typedef typename std::vector<T>::iterator iterator;
	iterator begin() { return iterator(element->begin()); }
	iterator end() { return iterator(element->end()); }

protected:					// ���ӵĳ�Ա 
	void checkIndex(int theIndex) const;
	std::vector<T>* element;		// �洢���Ա�Ԫ�ص�����
};

// vectorList �Ĺ��캯��
template<class T>
vectorList<T>::vectorList(int initalCapacity)
{// ���캯��
	if (initalCapacity < 1)
	{
		std::ostringstream s;
		s << "Inital capacity = " << initalCapacity << " Must be > 0";
		//throw illegalParameterValue(s.str());
	}
	element = new std::vector<T>;
			// ��������Ϊ 0 �Ŀ�����
	element->reserve(initalCapacity);
			// vecotr ������ 0 ���ӵ� initalCapacity
}

template<class T>
vectorList<T>::vectorList(const vectorList<T>& theList)
{// ���ƹ��캯��
	element = new std::vector<T>(*theList.element);
}

// vectorList ��ɾ���Ͳ���
template<class T>
void vectorList<T>::erase(int theIndex)
{// ɾ������Ϊ theIndex ��Ԫ��
 // ���û�����Ԫ��,���׳��쳣
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<class T>
void vectorList<T>::insert(int theIndex, const T& theElement)
{// ������Ϊ theIndex ������Ԫ�� theElement
	if (theIndex<0 || theIndex>size())
	{// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << size();
		//throw illegalIndex(s.str());
	}
	element->insert(element->begin() + theIndex, theElement);
}
