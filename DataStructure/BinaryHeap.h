#pragma once

/*
����ѣ�ʵ�����ȶ��еĻ������ݽṹ��
�������ʣ����ٵ��ҵ���СԪ������СԪ���ڸ��ڵ㴦������һ����ȫ��������

��Ҫ��������ϸ�ڣ�
1.insert������ʹ�����˱��ֶѵĶ������С�
2.remove��ɾ��ʹ�����˱��ֶѵĶ������С�
3.findMin���ҵ���ǰ��С�Ľڵ㡣
4.isEmpty����鵱ǰ�Ƿ�Ϊ����
5.buildHeap���������˲���������ǰһ��Ķѽڵ㣬��ÿһ���ڵ�������˲�����

��Ҫ�����ݽṹ������vector������Ϊ�ѵ���ȫ���������ʣ�����ѡ��vector��
*/

#include <vector>
using namespace std;

template <typename Comparable>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100);
	explicit BinaryHeap(const vector<Comparable>& x);

	const Comparable& findMin();
	bool isEmpty();

	void insert(const Comparable& x);
	void removeMin();
	void removeMin(Comparable& x);
	void makeEmpty();

private:
	int currentSize;
	vector<Comparable> heapVec;

	void buildHeap();
	void percolateDown(int hole);
};

template<typename Comparable>
inline BinaryHeap<Comparable>::BinaryHeap(int capacity)
{
	currentSize = 0;
	heapVec.resize(capacity);
}

//����Ӧ�Ĳ������п���֮����н��ѡ�
template<typename Comparable>
inline BinaryHeap<Comparable>::BinaryHeap(const vector<Comparable>& x)
{
	heapVec.resize(x.size() * 2);
	currentSize = x.size();
	for (int i = 0; i < x.size(); ++i)
	{
		heapVec[i + 1] = x[i];
	}
	buildHeap();
}

//���ݶ������ʣ���Сֵ��Ϊindex 1.
template<typename Comparable>
inline const Comparable& BinaryHeap<Comparable>::findMin()
{
	if (currentSize >= 1)
	{
		return heapVec[1];
	}
	return -1;
}

//�鿴��ǰ�Ƿ�Ϊ0
template<typename Comparable>
inline bool BinaryHeap<Comparable>::isEmpty()
{
	return currentSize==0;
}

//���Ƚ�x�������++currentSize����Ȼ��ʹ�����˵Ĳ������ҵ�x����ȷλ�á�
template<typename Comparable>
inline void BinaryHeap<Comparable>::insert(const Comparable & x)
{
	if (currentSize == heapVec.size() - 1)
	{
		heapVec.resize(currentSize * 2);
	}
	int hole = ++currentSize;
	for (; hole > 1 && x < heapVec[hole / 2]; hole /= 2)
	{
		heapVec[hole] = heapVec[hole / 2];
	}
	heapVec[hole] = x;
}

//�����һλ��ֵ����һλ��Ȼ���������
template<typename Comparable>
inline void BinaryHeap<Comparable>::removeMin()
{
	if (isEmpty())
	{
		throw underflow_error;
	}
	heapVec[1] = heapVec[currentSize--];
	percolateDown(1);
}

//���������Ĳ�����ʵ����һ�����ô�ֵ
template<typename Comparable>
inline void BinaryHeap<Comparable>::removeMin(Comparable & x)
{
	if (isEmpty())
	{
		return;
	}
	x = heapVec[1];
	heapVec[1] = heapVec[currentSize--];
	percolateDown(1);
}

//�򵥵Ķ���ʵ�֣���ռ���size����
template<typename Comparable>
inline void BinaryHeap<Comparable>::makeEmpty()
{
	currentSize = 0;
}

//���ǽ����������ڸ�ֵ֮�󣬽�������ʹ֮���϶���
template<typename Comparable>
inline void BinaryHeap<Comparable>::buildHeap()
{
	for (int i = currentSize/2; i >0 ; --i)//����������ȫ�����������һ�㣬�������ˡ�
	{
		percolateDown(i);
	}
}

//Ϊ��ɾ����Сֵ�����ǽ����һλ����ֵ�滻����һλ�����ҽ���һλ���ˣ�ʹ����϶���
template<typename Comparable>
inline void BinaryHeap<Comparable>::percolateDown(int hole)
{
	int child;
	Comparable tmp = heapVec[hole];

	for (; hole * 2 <= currentSize; hole = child)
	{
		child = hole * 2;
		if (child != currentSize && heapVec[child] > heapVec[child + 1])
		{
			child++;
		}
		if (heapVec[child] < tmp)
		{
			heapVec[hole] = heapVec[child];
		}
		else
		{
			break;
		}
	}
	heapVec[hole] = tmp;
}
