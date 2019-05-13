#pragma once
#include <iostream>

template<typename Object>
class AVLTree
{
public:
	AVLTree() {
		root = nullptr;
	}

	void insert(const Object& x)
	{
		insert(x, root);
	}

	void remove(const Object& x)
	{
		remove(x, root);
	}

	void PrintT()
	{
		PrintT(root);
	}



private:
	struct AVLNode 
	{
		Object val;
		AVLNode* left;
		AVLNode* right;
		int height;
		AVLNode(const Object& ob, AVLNode* l, AVLNode* r) :
			val(ob), left(l), right(r){}
	};

	AVLNode* root;


	void insert(const Object& x, AVLNode* & t);
	void remove(const Object& x, AVLNode* & t);

	void leftSingleRotation(AVLNode* &t);
	void rightSingleRotation(AVLNode* &t);

	void leftDoubleRotation(AVLNode* &t);
	void rightDoubleRotation(AVLNode* &t);

	int height(AVLNode* &t)
	{
		return t == nullptr ? -1 : t->height;
	}

	int max(int a, int b)
	{
		return a > b ? a : b;
	}

	int powerOf2(int x)
	{
		if (x == 0)return 1;
		int m = 1;
		while (--x >= 0)
		{
			m *= 2;
		}
		return m;
	}

	//ʹ�õݹ�ķ�ʽȥ�����ڵ�t���µ����ڵ�
	AVLNode* max_node(AVLNode* t)
	{
		if (!t)
		{
			return nullptr;
		}
		if (t->right)
		{
			return max_node(t);
		}
		else
		{
			return t;
		}
	}

	AVLNode* min_node(AVLNode* t)
	{
		if (!t)
		{
			return nullptr;
		}
		else
		{
			while (t->left != nullptr)
			{
				t = t->left;
			}
		}
		return t;
	}


	void PrintT(AVLNode* t)
	{
		if (t != nullptr)
		{
			std::cout << t->val << std::endl;
			PrintT(t->left);
			PrintT(t->right);
		}
	}
};

//��x���뵽��Ӧ��t����
template<typename Object>
inline void AVLTree<Object>::insert(const Object & x, AVLNode *& t)
{
	if (t == nullptr)
	{
		t = new AVLNode(x, nullptr, nullptr);
	}
	else if (x < t->val)
	{
		insert(x, t->left);
		if (height(t->left) - height(t->right) == 2)
		{
			if (x < t->left->val)
			{
				leftSingleRotation(t);
			}
			else
			{
				leftDoubleRotation(t);
			}
		}
	}
	else if (t->val < x)
	{
		insert(x, t->right);
		if (height(t->right) - height(t->left) == 2)
		{
			if (t->right->val < x)
			{
				rightSingleRotation(t);
			}
			else
			{
				rightDoubleRotation(t);
			}
		}
	}
	else
	{
		//��t��ֵ���Ӧ���ظ����˴�����
	}
	t->height = max(height(t->left), height(t->right)) + 1;
}

template<typename Object>
inline void AVLTree<Object>::remove(const Object & x, AVLNode *& t)
{
	if (t == nullptr)
	{
		return;
	}
	if (x < t->val)
	{
		remove(x, t->left);
		if (height(t->right) - height(t->left) == 2)
		{
			AVLNode* s = t->right;
			if (height(s->right) < height(s->left))
			{
				rightDoubleRotation(t);
			}
			else
			{
				rightSingleRotation(t);
			}
		}
		else//�������Ҫ���µ�������ôֱ�Ӹ�����height�ͺ���
		{
			t->height = max(height(t->left), height(t->right)) + 1;
		}
	}
	else if(x>t->val)
	{
		remove(x, t->right);
		if (height(t->left) - height(t->right) == 2)
		{
			AVLNode* s = t->left;
			if (height(s->left) < height(s->right))
			{
				rightDoubleRotation(t);
			}
			else
			{
				rightSingleRotation(t);
			}
		}
		else
		{
			t->height = max(height(t->left), height(t->right)) + 1;
		}
	}
	else
	{
		//��������������ڣ�ȡheight�����������е�x��Ϊ��ǰt�Ľڵ�
		if (t->left&&t->right)
		{
			if (height(t->left) > height(t->right))
			{
				t->val = max_node(t->left)->val;
				remove(t->val, t->left);
			}
			else
			{
				t->val = min_node(t->right)->val;
				remove(t->val, t->right);
			}
		}
		else//ɾ���Ľڵ�����������һ��Ϊ��
		{
			AVLNode* oldnode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldnode;
		}
	}
}

//������ת���
template<typename Object>
inline void AVLTree<Object>::leftSingleRotation(AVLNode *& k2)
{
	AVLNode* k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
}

template<typename Object>
inline void AVLTree<Object>::rightSingleRotation(AVLNode *& k2)
{
	AVLNode* k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->right), height(k2->left)) + 1;
	k1->height = max(height(k1->right), k2->height) + 1;
	k2 = k1;
}

//˫��ת�������������
template<typename Object>
inline void AVLTree<Object>::leftDoubleRotation(AVLNode *& t)
{
	rightSingleRotation(t->left);
	leftSingleRotation(t);
}

template<typename Object>
inline void AVLTree<Object>::rightDoubleRotation(AVLNode *& t)
{
	leftSingleRotation(t->right);
	rightSingleRotation(t);
}
