#pragma once

// 链表二叉树的结点结构
template<class T>
struct binaryTreeNode
{
	T element;
	binaryTreeNode<T>* leftChild,			// 左子树
					 * rightChild;			// 右子树

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

// 二叉树遍历

template<class T>
void visit(binaryTreeNode<T>* x)
{// 访问结点 *x,仅输出 element 域
	std::cout << x->element << ' ';
}

template<class T>
void preOrder(binaryTreeNode<T>* t)
{// 前序遍历二叉树 *t
	if (t != NULL)
	{
		visit(t);					// 访问树根
		preOrder(t->leftChild);		// 前序遍历左子树
		preOrder(t->rightChild);	// 前序遍历右子树
	}
}

template<class T>
void inOrder(binaryTreeNode<T>* t)
{// 中序遍历二叉树 *t
	if (t != NULL)
	{
		inOrder(t->leftChild);		// 中序遍历左子树
		visit(t);					// 访问树根
		inOrder(t->rightChild);		// 中序遍历右子树
	}
}

template<class T>
void postOrder(binaryTreeNode<T>* t)
{// 后序遍历二叉树 *t
	if (t != NULL)
	{
		postOrder(t->leftChild);	// 后序遍历左子树
		postOrder(t->rightChild);	// 后序遍历右子树
		visit(t);					// 访问树根
	}
}

template<class T>
void levelOrder(binaryTreeNode<T>* t)
{// 层序遍历二叉树 *t
	std::queue<binaryTreeNode<T>*> q;
	while (t != NULL)
	{
		visit(t);

		// 将 t 的孩子插入队列
		if (t->leftChild != NULL)
			q.push(t->leftChild);
		if (t->rightChild != NULL)
			q.push(t->rightChild);

		// 提取下一个要访问的结点
		try { t = q.front(); }
		catch (queueEmpty) { return; }
		q.pop();
	}
}
