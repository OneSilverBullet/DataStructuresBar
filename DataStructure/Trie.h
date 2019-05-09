#pragma once

//Trie:�ֵ��������ڿ��ټ�����26���������͵Ŀռ任ʱ��
//Ӧ�ã��������浱�еĴ�Ƶͳ��
//ԭ��ʹ��ÿһ���ַ�����ǰ׺�����������Ӷ��ﵽ����������Ŀ�ġ�
//�ֵ���++
#include <stdlib.h>
#include <string.h>
template<int SIZE>
class TrieNode
{
public:
	TrieNode() :terminateNum(0), nodesize(0)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			children[i] = nullptr;
		}
	}
	~TrieNode()
	{
		for (int i = 0; i < SIZE; ++i)
		{
			delete(children[i]);
			children[i] = nullptr;
		}
	}
	int terminateNum;
	int nodesize;
	TrieNode* children[SIZE];
};

template<int SIZE>
class Index
{
public:
	int operator[](char c)
	{
		return (c-'a');
	}
};

template<int SIZE, class Type>
class Trie
{
public:
	typedef TrieNode<SIZE> Node;
	typedef TrieNode<SIZE>* pNode;
	Trie():root(new Node){}

	template<class Iterator>
	void Insert(Iterator beg, Iterator end);
	void Insert(const char* str);

	template<class Iterator>
	bool Find(Iterator beg, Iterator end);
	bool Find(const char* str);



	template<class Iterator>
	bool erase(Iterator beg, Iterator end);
	bool erase(const char* str);

	int sizeAll(pNode a=root);//ͳ�����е��ַ�����ͳ�Ƶ���nodesize
	int sizeAllWithoutRedundant(pNode a=root);//ͳ�����еĲ��ظ��ַ�����ͳ�Ƶ���terminateSize


public:
	pNode root;
private:
	Type index;
};

template<int SIZE, class Type>
template<class Iterator>
inline void Trie<SIZE, Type>::Insert(Iterator beg, Iterator end)
{
	pNode cur = root;
	pNode pre;
	for (; beg != end; ++beg)
	{
		if (!cur->children[index[*beg]])//�����ǰ�ַ��ڵ�Ϊ�գ���ô�����½ڵ�
		{
			cur->children[index[*beg]] = new Node();
			++cur->nodesize;
		}
		pre = cur;//pre��¼cur֮ǰÿһ���ڵ㣬��һ��word����֮�����pre��terminateNum
		cur = cur->children[index[*beg]];
	}
	++pre->terminateNum;
}

template<int SIZE, class Type>
template<class Iterator>
inline bool Trie<SIZE, Type>::Find(Iterator beg, Iterator end)
{
	pNode cur = root;
	pNode pre;
	for (; beg != end; ++beg)
	{
		if (cur->children[index[*beg]]==nullptr)
		{
			return false;
		}
		pre = cur;
		cur = cur->children[index[*beg]];
	}
	if (pre->terminateNum > 0)
	{
		return true;
	}
	return false;
}



template<int SIZE, class Type>
template<class Iterator>
inline bool Trie<SIZE, Type>::erase(Iterator beg, Iterator end)
{
	if (Find(beg, end))
	{
		pNode cur = root;
		pNode pre;
		for (; beg != end; ++beg)
		{
			pre = cur;
			cur = cur->children[index[*beg]];
		}
		if (pre->terminateNum > 0)
		{
			--pre->terminateNum;
		}
		return true;
	}
	return false;
}

template<int SIZE, class Type>
inline void Trie<SIZE, Type>::Insert(const char * str)
{
	Insert(str, str + strlen(str));
}

template<int SIZE, class Type>
inline bool Trie<SIZE, Type>::Find(const char * str)
{
	return Find(str,str+strlen(str));
}

template<int SIZE, class Type>
inline bool Trie<SIZE, Type>::erase(const char * str)
{
	if (Find(str))
	{
		erase(str, str + strlen(str));
		return true;
	}
	return false;
}

template<int SIZE, class Type>
inline int Trie<SIZE, Type>::sizeAll(pNode a)
{
	if (a == nullptr)
		return 0;
	int res = a->terminateNum;
	for (int i = 0; i < SIZE; ++i)
	{
		res += sizeAll(a->children[i]);
	}
	return res;
}

template<int SIZE, class Type>
inline int Trie<SIZE, Type>::sizeAllWithoutRedundant(pNode a)
{
	if (a == nullptr)
	{
		return 0;
	}
	int rev = 0;
	if (a->terminateNum > 0)
	{
		rev = 1;
	}
	if (a->nodesize != 0)
	{
		for (int i = 0; i < SIZE; ++i)
		{
			rev += sizeAllWithoutRedundant(a->children[i]);
		}
	}
	return rev;
}



