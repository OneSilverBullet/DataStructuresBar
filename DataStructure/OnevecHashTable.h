#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*
通过平方散列实现的哈希表。

技术细节：
1.通过find函数来依据x值找到对应的位置。其中每一次的查找增加的值都是
递增的，也就是增加的值会越来越大。
2.关键函数insert与remove是在find的基础上，对x进行查找对应的position
然后对info进行修改。使用懒惰删除，只有当rehash的时候才会进行删除。
3.关键函数rehash，当装填指数达到0.5，就调用rehash。注意，扩张的内存
量为当前内存*2的下一个素数。并且使用insert进行装填。不能直接装填因
有可能会使得某数据永远访问不到。
*/

template<typename T>
class OnevecHashTable
{
public:
	explicit OnevecHashTable(int size=101);
	bool contains(const T& x)const;
	void makeEmpty();
	bool insert(const T& x);
	bool remove(const T& x);
	void show();

	enum EntryState {
		ACTIVE, DELETE, EMPTY
	};
private:
	template<typename T>
	struct HashEntry
	{
		T hashObj;
		EntryState info;
		HashEntry()
		{
			info = EMPTY;
		}
		HashEntry(const T& a, EntryState i) :
			hashObj(a), info(i){}

		friend ostream& operator<<(ostream& os, HashEntry& k)
		{
			os << k.hashObj << " " << k.info << endl;
			return os;
		}
		ostream& operator<<(ostream& os)
		{
			os << hashObj << " " << info << endl;
			return os;
		}
	};


	int currentSize;
	vector<HashEntry<T>> hashvec;
	
	bool isActive(int pos)const;
	int findPos(const T& x)const;
	void rehash();
	int myHash(const T& x)const;


};

//判断num是否为素数
bool isPrime(int num)
{
	for (int i = 2; i <= num/2; ++i)
	{
		if (num%i == 0)
		{
			return false;
		}
	}
	return true;
}

//查找当前num的下一个素数
int nextPrime1(int num)
{
	while (!isPrime(num))
	{
		num++;
	}
	return num;
}

//初始化的时候所有数值置空
template<typename T>
inline OnevecHashTable<T>::OnevecHashTable(int size)
{
	hashvec.resize(nextPrime1(size));
	makeEmpty();
}

//查询是否包含x
template<typename T>
inline bool OnevecHashTable<T>::contains(const T & x) const
{
	return isActive(findPos(x));
}

//将所有的entry置空
template<typename T>
inline void OnevecHashTable<T>::makeEmpty()
{
	currentSize = 0;
	for (int i = 0; i < hashvec.size(); ++i)
	{
		hashvec[i].info = EMPTY;
	}
}

//在find基础上，插入对应值x
template<typename T>
inline bool OnevecHashTable<T>::insert(const T & x)
{
	int currenPos = findPos(x);
	if (isActive(currenPos))
	{
		return false;
	}
	hashvec[currenPos] = HashEntry<T>(x, ACTIVE);
	if (++currentSize > hashvec.size() / 2)
	{
		rehash();
	}
	return true;
}

//利用find进行的懒惰删除
template<typename T>
inline bool OnevecHashTable<T>::remove(const T & x)
{
	int curpos = findPos(x);
	if (!isActive(curpos))
	{
		return false;
	}
	hashvec[curpos].info = DELETE;
	return true;
}

template<typename T>
inline void OnevecHashTable<T>::show()
{
	for (int i = 0; i < hashvec.size(); ++i)
	{
		cout << hashvec[i] << " ";
	}cout << endl;
}

//判断当前节点是否是好的存储节点
template<typename T>
inline bool OnevecHashTable<T>::isActive(int pos) const
{
	return hashvec[pos].info == ACTIVE;
}

//核心操作：依据x找到对应的位置。平方散列的实现。
template<typename T>
inline int OnevecHashTable<T>::findPos(const T & x) const
{
	int findin = 1;
	int curpos = myHash(x);
	//注意这里的info是不是empty，如果为delete也会继续进行搜索，但是是
	//empty就说明前面没有了。
	while (hashvec[curpos].info != EMPTY &&
		hashvec[curpos].hashObj != x)
	{
		curpos += findin;
		findin += 2;
		if (curpos >= hashvec.size())
		{
			curpos -= hashvec.size();
		}
	}
	return curpos;
}

//在装填因子小于0.5时，进行空间扩充
template<typename T>
inline void OnevecHashTable<T>::rehash()
{
	vector<HashEntry<T>> old = hashvec;
	hashvec.resize(nextPrime1(2* old.size()));
	for (int i = 0; i < hashvec.size(); ++i)
	{
		hashvec[i].info = EMPTY;//这里将其原来所有的都置位为空
		//有可能hashvec当中的值还存在，但是逻辑上已经不存在，不用在乎
	}
	currentSize = 0;
	for (int i = 0; i < old.size(); ++i)
	{
		if (old[i].info == ACTIVE)
		{
			insert(old[i].hashObj);
		}
	}
}

//基础hash函数，可以进行诸多设计
template<typename T>
inline int OnevecHashTable<T>::myHash(const T & x) const
{
	int hashVal = x % hashvec.size();

	if (hashVal < 0)
	{
		hashVal += hashvec.size();
	}
	return hashVal;
}
