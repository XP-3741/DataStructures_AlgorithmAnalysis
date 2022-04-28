#pragma once

// ����������Ľ��ṹ
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,			// ������
					 * rightChild;			// ������

	binaryTreeNode() { leftChild = rightChild = NULL; }
	binaryTreeNode(const T& theElement)
	{
		element(theElement);
		leftChild = rightChild = NULL;
	}
	binaryTreeNode(const T& theElement,
					binaryTreeNode* theLeftChild,
					binaryTreeNode* theRightChild)
	{
		element(theElement);
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

// ����������

template<class T>
void visit(binaryTreeNode<T>* x)
{// ���ʽ�� *x,����� element ��
	std::cout << x->element << ' ';
}

template<class T>
void preOrder(binaryTreeNode<T>* t)
{// ǰ����������� *t
	if (t != NULL)
	{
		visit(t);					// ��������
		preOrder(t->leftChild);		// ǰ�����������
		preOrder(t->rightChild);	// ǰ�����������
	}
}

template<class T>
void inOrder(binaryTreeNode<T>* t)
{// ������������� *t
	if (t != NULL)
	{
		inOrder(t->leftChild);		// �������������
		visit(t);					// ��������
		inOrder(t->rightChild);		// �������������
	}
}

template<class T>
void postOrder(binaryTreeNode<T>* t)
{// ������������� *t
	if (t != NULL)
	{
		postOrder(t->leftChild);	// �������������
		postOrder(t->rightChild);	// �������������
		visit(t);					// ��������
	}
}

template<class T>
void levelOrder(binaryTreeNode<T>* t)
{// ������������� *t
	std::queue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		visit(t);

		// �� t �ĺ��Ӳ������
		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);

		// ��ȡ��һ��Ҫ���ʵĽ��
		try { t = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}
