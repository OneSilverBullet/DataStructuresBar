#pragma once
#include <iostream>

//�ڲ�ȷ������������ʱ��ʹ�����ӽڵ����ֵܵķ�ʽ���������ڵ�Ķ���
struct TreeNode
{
	int val;
	TreeNode* firstChild;
	TreeNode* nextSilbling;
};

//֪ʶ��1�����ʽ����ʹ��ջ����������Ͻ��б��ʽ�ı��

template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& rhs);
	~BinarySearchTree();

	//��װ�õ�API
	const Comparable& FindMax() const;
	const Comparable& FindMin() const;
	bool Contains(const Comparable& a) const;
	bool IsEmpty() const;
	void PrintTree() const;
	void MakeEmpty();
	void Insert(const Comparable& x);
	void Remove(const Comparable& x);

	const BinarySearchTree& operator=(const BinarySearchTree& rhs)
	{
		if (this != nullptr)
		{
			makeEmpty(root);
			root = clone(rhs.root);
		}
		return *this;
	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt) :
			element(theElement), left(lt), right(rt) {}
	};

	BinaryNode* root;

	//�������ĵĴ���
	void insert(const Comparable& x, BinaryNode* & t) const;
	void remove(const Comparable& x, BinaryNode* & t)const;
	const BinaryNode* findMax(BinaryNode* t)const
	{
		if (t != nullptr)
		{
			while (t->right != nullptr)
			{
				t = t->right;
			}
		}
		return t;
	}

	const BinaryNode* findMin(BinaryNode* t)const
	{
		if (t == nullptr)return nullptr;
		if (t->left == nullptr)return t;
		return findMin(t->left);
	}
	bool contains(const Comparable& x, BinaryNode *t)const;
	void makeEmpty(BinaryNode* & t);
	void printTree(BinaryNode* t)const;
	BinaryNode* clone(BinaryNode* t) const
	{
		if (t == nullptr)return nullptr;
		return new BinaryNode(t->element, clone(t->left), clone(t->right));
	}

};


template<typename Comparable>
inline BinarySearchTree<Comparable>::BinarySearchTree()
{
	root = nullptr;
}

template<typename Comparable>
inline BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree & rhs)
{
	return operator=(rhs);
}

template<typename Comparable>
inline BinarySearchTree<Comparable>::~BinarySearchTree()
{
	makeEmpty(root);
}

template<typename Comparable>
inline const Comparable & BinarySearchTree<Comparable>::FindMax() const
{
	return findMax(root)->element;
}

template<typename Comparable>
inline const Comparable & BinarySearchTree<Comparable>::FindMin() const
{
	return findMin(root)->element;
}

template<typename Comparable>
inline bool BinarySearchTree<Comparable>::Contains(const Comparable & a) const
{
	return contains(a, root);
}

template<typename Comparable>
inline bool BinarySearchTree<Comparable>::IsEmpty() const
{
	return (root==nullptr);
}

template<typename Comparable>
inline void BinarySearchTree<Comparable>::PrintTree() const
{
	printTree(root);
}

template<typename Comparable>
inline void BinarySearchTree<Comparable>::MakeEmpty()
{
	makeEmpty(root);
}

template<typename Comparable>
inline void BinarySearchTree<Comparable>::Insert(const Comparable & x)
{
	insert(x, root);
}

template<typename Comparable>
inline void BinarySearchTree<Comparable>::Remove(const Comparable & x)
{
	remove(x, root);
}

//���룺Ѱ��һ���ʺϵ�λ�ý����½��������ڵ�
template<typename Comparable>
inline void BinarySearchTree<Comparable>::insert(const Comparable & x, BinaryNode *& t) const
{
	if (t == nullptr)
	{
		t = new BinaryNode(x, nullptr, nullptr);
	}
	else if (x < t->element)
	{
		insert(x, t->left);
	}
	else if (x > t->element)
	{
		insert(x, t->right);
	}
	//�ظ�Ԫ��
}

//��Ϊ��֦�ɾ���뵥֦�ɾ��
template<typename Comparable>
inline void BinarySearchTree<Comparable>::remove(const Comparable & x, BinaryNode *& t) const
{
	if (t == nullptr)
	{
		return;
	}
	if (x < t->element)
	{
		remove(x, t->left);
	}
	else if (x > t->element)
	{
		remove(x, t->right);
	}
	else if (t->left != nullptr&&t->right != nullptr)
	{
		//������ҷ�֧���У���ô���Ҳ���Сֵ��Ϊt�ڵ��ֵ��Ȼ��ɾ���Ҳ���Сֵ��
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		//����һ����֧����ôֱ�ӽ��ǿշ�֧��ֵ��t������ɾ��t
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

//���Ҷ��������������Ƿ���ڶ�ӦԪ��x
template<typename Comparable>
inline bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * t) const
{
	if (t == nullptr)return false;
	else if (x < t->element)return contains(x, t->left);
	else if (x > t->element)return contains(x, t->right);
	return true;
}

//�Զ���ڵ�t�����ÿ�
template<typename Comparable>
inline void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *& t)
{
	if (t != nullptr)
	{
		makeEmpty(t->right);
		makeEmpty(t->left);
		delete t;
	}
	t = nullptr;//ע��ָ�븳ֵΪ�ձ���Ұָ��
}

//һ��˳�����������ȫ���ڵ�
template<typename Comparable>
inline void BinarySearchTree<Comparable>::printTree(BinaryNode * t) const
{
	if (t != nullptr)
	{
		std::cout << t->element << std::endl;
		printTree(t->left);
		printTree(t->right);
	}
}