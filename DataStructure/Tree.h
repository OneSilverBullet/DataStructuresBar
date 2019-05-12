#pragma once
#include <iostream>

//在不确定儿子数量的时候，使用首子节点与兄弟的方式来进行树节点的定义
struct TreeNode
{
	int val;
	TreeNode* firstChild;
	TreeNode* nextSilbling;
};

//知识点1：表达式树：使用栈与树进行配合进行表达式的表达

template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& rhs);
	~BinarySearchTree();

	//封装好的API
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

	//真正核心的代码
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

//插入：寻找一个适合的位置进行新建二叉树节点
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
	//重复元素
}

//分为二枝杈删除与单枝杈删除
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
		//如果左右分支都有，那么以右侧最小值作为t节点的值，然后删除右侧最小值。
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else
	{
		//若有一个分支，那么直接将非空分支赋值给t，并且删除t
		BinaryNode* oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
}

//查找二叉搜索树当中是否存在对应元素x
template<typename Comparable>
inline bool BinarySearchTree<Comparable>::contains(const Comparable & x, BinaryNode * t) const
{
	if (t == nullptr)return false;
	else if (x < t->element)return contains(x, t->left);
	else if (x > t->element)return contains(x, t->right);
	return true;
}

//对二叉节点t进行置空
template<typename Comparable>
inline void BinarySearchTree<Comparable>::makeEmpty(BinaryNode *& t)
{
	if (t != nullptr)
	{
		makeEmpty(t->right);
		makeEmpty(t->left);
		delete t;
	}
	t = nullptr;//注意指针赋值为空避免野指针
}

//一个顺序遍历二叉树全部节点
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