#pragma once

//Trie:字典树，用于快速检索的26叉树，典型的空间换时间
//应用：搜索引擎当中的词频统计
//原理：使用每一个字符串的前缀来建立树，从而达到快速搜索的目的。
//字典树++
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

	int sizeAll(pNode a=root);//统计所有的字符串，统计的是nodesize
	int sizeAllWithoutRedundant(pNode a=root);//统计所有的不重复字符串，统计的是terminateSize


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
		if (!cur->children[index[*beg]])//如果当前字符节点为空，那么创建新节点
		{
			cur->children[index[*beg]] = new Node();
			++cur->nodesize;
		}
		pre = cur;//pre记录cur之前每一个节点，当一个word结束之后更新pre的terminateNum
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



