#pragma once
#include"Abstract_Classes.h"

// ����ڵ�Ľṹ����
template<class T>
struct chainNode
{
	// ���ݳ�Ա
	T element;
	chainNode<T>* next;

	// ����
	chainNode() {}
	chainNode(const T& element)
		{this->element = element;}
	chainNode(const T& element,chainNode<T>* next)
		{this->element = element;
		 this->next = next;}
};

// �� chain
// ����ڵ�Ľṹ����
template<class T>
class chain :public linearList<T>
{
public:
	// ���캯��,���ƹ��캯������������
	chain(int initialCapacity = 10);
	chain(const chain<T>&);
	~chain();

	// �����������ͺ�ADT����
	bool empty() const { return listSize == 0; }
	int size() const { return listSize; }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(std::ostream& out) const;

protected:
	void checkIndex(int theIndex) const;
		// ��������Ч,���׳��쳣
	chainNode<T>* firstNode;	// ָ�������һ���ڵ��ָ��
	int listSize;				// ���Ա��Ԫ�ظ���
};

// ����Ĺ��캯���͸��ƹ��캯��
template<class T>
chain<T>::chain(int initialCapacity)
{// ���캯��
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Inital capacity = " << initalCapacity << " Must be > 0";
		//throw illegalParameterValue(s.str());
	}
	firstNode = NULL;
	listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T>& theList)
{// ���ƹ��캯��
	listSize = theList.listSize;

	if (listSize == 0)
	{// ���� theList Ϊ��
		firstNode = NULL;
		return;
	}

	// ���� theList Ϊ�ǿ�
	chainNode<T>* sourceNode = theList.firstNode;
					// Ҫ�������� theList �Ľڵ�
	firstNode = new chainNode<T>(sourceNode->element);
					// �������� theList ����Ԫ��
	sourceNode = sourceNode->next;
	chainNode<T>* tatgetNode = firstNode;
					// ��ǰ���� *this �����һ���ڵ�
	while (sourceNode != NULL)
	{// ����ʣ��Ԫ��
		tatgetNode->next = new chainNode<T>(sourceNode->element);
		tatgetNode = tatgetNode->next;
		sourceNode = sourceNode->next;
	}
	tatgetNode->next = NULL;
}

//�������������
template<class T>
chain<T>::~chain()
{// ������������,ɾ����������н��
	while (firstNode != NULL)
	{// ɾ���׽ڵ�
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

// ���� get �ķ���ֵ������Ϊ theIndex ��Ԫ��
template<class T>
T& chain<T>::get(int theIndex) const
{// ��������Ϊ theIndex ��Ԫ��
 // ����Ԫ�ز�����,���׳��쳣
	checkIndex(theIndex);

	// �ƶ�����Ҫ�Ľڵ�
	chainNode<T>* currentNode = firstNode;
	for (int i = 0; i < theIndex; i++)
		currentNode = currentNode->next;
	return currentNode->element;
}

// ����Ԫ�� theElement �״γ���ʱ������
template<class T>
int chain<T>::indexOf(const T& theElement) const
{// ����Ԫ�� theElement �״γ���ʱ������
 // ��Ԫ�ز�����,�򷵻�-1

	// ��������Ѱ��Ԫ�� theElement
	chainNode<T>* currentNode = firstNode;
	int index = 0;			// ��ǰ�ڵ������
	while (currentNode != NULL &&
		currentNode->element != theElement)
	{
		// ������һ���ڵ�
		currentNode = currentNode->next;
		index++;
	}

	// ȷ���Ƿ��ҵ�
	if (currentNode == NULL)
		return -1;
	else
		return index;
}

// ɾ������Ϊ theIndex ��Ԫ��
template<class T>
void chain<T>::erase(int theIndex)
{// ɾ������Ϊ theIndex ��Ԫ��
 // ��Ԫ�ز�����,���׳��쳣
	checkIndex(theIndex);

	// ������Ч,����Ҫɾ����Ԫ�ؽڵ�
	chainNode<T>* deleteNode;
	if(theIndex==0)
	{// ɾ���׽ڵ�
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else
	{// ��ָ�� p ָ��Ҫɾ���ڵ��ǰ���ڵ�
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		deleteNode = p;
		p->next = p->next->next;		// ɾ�� deleteNode ָ��Ľڵ�
	}
	listSize--;
	delete deleteNode;
}

template<class T>
void chain<T>::insert(int theIndex, const T& theElement)
{// ������Ϊ theIndex ��λ���ϲ���Ԫ�� theElement
	if (theIndex<0 || theIndex>listSize)
	{// ��Ч����
		std::ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		//throw illegalindex(s.str());
	}

	if (theIndex == 0)
		// ������ͷ����
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{	// Ѱ����Ԫ�ص�ǰ��
		chainNode<T>* p = firstNode;
		for (int i = 0; i < theIndex - 1; i++)
			p = p->next;

		// �� p ֮�����
		p->next = new chainNode<T>(theElement, p->next);
	}
	listSize++;
}

template<class T>
void chain<T>::output(std::ostream& out) const
{// ��������������
	for (chainNode<T>* currentNode = firstNode;
						currentNode != null;
						currentNode = currentNode->next)
		out << currentNode->element << " ";
}
// ����<<
template<class T>
std::ostream& operator<<(std::ostream& out,const chain<T>& x)
{x.output(out); return out;}
