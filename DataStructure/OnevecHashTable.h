#pragma once
#include <vector>
#include <iostream>
using namespace std;

/*
ͨ��ƽ��ɢ��ʵ�ֵĹ�ϣ��

����ϸ�ڣ�
1.ͨ��find����������xֵ�ҵ���Ӧ��λ�á�����ÿһ�εĲ������ӵ�ֵ����
�����ģ�Ҳ�������ӵ�ֵ��Խ��Խ��
2.�ؼ�����insert��remove����find�Ļ����ϣ���x���в��Ҷ�Ӧ��position
Ȼ���info�����޸ġ�ʹ������ɾ����ֻ�е�rehash��ʱ��Ż����ɾ����
3.�ؼ�����rehash����װ��ָ���ﵽ0.5���͵���rehash��ע�⣬���ŵ��ڴ�
��Ϊ��ǰ�ڴ�*2����һ������������ʹ��insert����װ�����ֱ��װ����
�п��ܻ�ʹ��ĳ������Զ���ʲ�����
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

//�ж�num�Ƿ�Ϊ����
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

//���ҵ�ǰnum����һ������
int nextPrime1(int num)
{
	while (!isPrime(num))
	{
		num++;
	}
	return num;
}

//��ʼ����ʱ��������ֵ�ÿ�
template<typename T>
inline OnevecHashTable<T>::OnevecHashTable(int size)
{
	hashvec.resize(nextPrime1(size));
	makeEmpty();
}

//��ѯ�Ƿ����x
template<typename T>
inline bool OnevecHashTable<T>::contains(const T & x) const
{
	return isActive(findPos(x));
}

//�����е�entry�ÿ�
template<typename T>
inline void OnevecHashTable<T>::makeEmpty()
{
	currentSize = 0;
	for (int i = 0; i < hashvec.size(); ++i)
	{
		hashvec[i].info = EMPTY;
	}
}

//��find�����ϣ������Ӧֵx
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

//����find���е�����ɾ��
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

//�жϵ�ǰ�ڵ��Ƿ��ǺõĴ洢�ڵ�
template<typename T>
inline bool OnevecHashTable<T>::isActive(int pos) const
{
	return hashvec[pos].info == ACTIVE;
}

//���Ĳ���������x�ҵ���Ӧ��λ�á�ƽ��ɢ�е�ʵ�֡�
template<typename T>
inline int OnevecHashTable<T>::findPos(const T & x) const
{
	int findin = 1;
	int curpos = myHash(x);
	//ע�������info�ǲ���empty�����ΪdeleteҲ���������������������
	//empty��˵��ǰ��û���ˡ�
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

//��װ������С��0.5ʱ�����пռ�����
template<typename T>
inline void OnevecHashTable<T>::rehash()
{
	vector<HashEntry<T>> old = hashvec;
	hashvec.resize(nextPrime1(2* old.size()));
	for (int i = 0; i < hashvec.size(); ++i)
	{
		hashvec[i].info = EMPTY;//���ｫ��ԭ�����еĶ���λΪ��
		//�п���hashvec���е�ֵ�����ڣ������߼����Ѿ������ڣ������ں�
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

//����hash���������Խ���������
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
