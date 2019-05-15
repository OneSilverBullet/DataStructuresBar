#pragma once
#include <vector>
#include <list>
#include <string.h>
using namespace std;
template<typename HashObj>
class HashTable
{
public:
	explicit HashTable(int size = 10);
	bool contains(const HashObj& x)const;
	void makeEmpty();
	bool insert(const HashObj& x);
	bool remove(const HashObj& x);
	void show();

private:
	vector<list<HashObj>> theLists;
	int currentSize;
	void rehash();
	int myHash(const HashObj& x)const;
};


int hash1(const std::string& key, int size)
{
	int hashVal = 0;
	for (int i = 0; i < key.length(); ++i)
	{
		hashVal = 37 * hashVal + key[i];
		hashVal%=size;
	}
	if (hashVal < 0)
	{
		hashVal += size;
	}
	return hashVal;
}

int hash1(int key, int size)
{
	return key % size;
}

int nextPrime(int a)
{
	while (true)
	{
		int i = 2;
		for (; i < a; ++i)
		{
			if (a % 2 == 0)
			{
				break;
			}
		}
		if (i == a)
		{
			return a;
		}
		a++;
	}
	return 0;
}


template<typename HashObj>
inline HashTable<HashObj>::HashTable(int size)
{
	theLists.resize(size);
}

//通过x的哈希值求得对应的list，然后搜索对应的值。
template<typename HashObj>
inline bool HashTable<HashObj>::contains(const HashObj & x) const
{
	const list<HashObj>& which = theLists[myHash(x)];
	return find(which.begin(), which.end(), x) != which.end();
}

template<typename HashObj>
inline void HashTable<HashObj>::makeEmpty()
{
	for (int i = 0; i < theLists.size(); ++i)
	{
		theLists[i].clear();
	}
}

//注意这个哈希表不能够重复插入，其插入x就是找到对应的list然后push进x
template<typename HashObj>
inline bool HashTable<HashObj>::insert(const HashObj & x)
{
	list<HashObj>& which = theLists[myHash(x)];
	if (find(which.begin(), which.end(), x) != which.end())
	{
		return false;
	}
	which.push_back(x);
	if (++currentSize > theLists.size())
	{
		rehash();
	}
	return true;
}

//依据x的哈希值找到对应的list，然后搜索对应的值，并且erase
template<typename HashObj>
inline bool HashTable<HashObj>::remove(const HashObj & x)
{
	list<HashObj>& which = theLists[myHash(x)];
	list<HashObj>::iterator iter = find(which.begin(), which.end(), x);
	if (iter == which.end())
	{
		return false;
	}
	which.erase(iter);
	--currentSize;
	return true;
}

template<typename HashObj>
inline void HashTable<HashObj>::show()
{
	cout << "the hash table: " << endl;
	for (int i = 0; i < theLists.size(); ++i)
	{
		list<HashObj>::iterator iter = theLists[i].begin();
		while (iter != theLists[i].end())
		{
			cout << (*iter++) << " ";
			
		}cout << endl;
	}

}

//当hash表的大小与装的元素一样多的时候，就进行rehash。
template<typename HashObj>
inline void HashTable<HashObj>::rehash()
{
	vector<list<HashObj>> oldLists = theLists;
	theLists.resize(nextPrime(2 * theLists.size()));
	for (int j = 0; j < theLists.size(); ++j)
	{
		theLists[j].clear();
	}
	currentSize = 0;
	for (int i = 0; i < oldLists.size(); ++i)
	{
		list<HashObj>::iterator iter = oldLists[i].begin();
		while (iter != oldLists[i].end())
		{
			insert(*iter++);
		}
	}
}

//这里调用了非成员函数，相当于对非成员hash函数作了一层封装
template<typename HashObj>
inline int HashTable<HashObj>::myHash(const HashObj & x) const
{
	int hashVal = hash1(x, theLists.size());

	hashVal %= theLists.size();
	if (hashVal < 0)
	{
		hashVal += theLists.size();
	}
	return hashVal;
}
