#pragma once

/*
二叉堆：实现优先队列的基本数据结构。
堆序性质：快速的找到最小元，将最小元放在根节点处。堆是一个完全二叉树。

主要技术操作细节：
1.insert。插入使用上滤保持堆的堆序排列。
2.remove。删除使用下滤保持堆的堆序排列。
3.findMin。找到当前最小的节点。
4.isEmpty。检查当前是否为正。
5.buildHeap。利用下滤操作，遍历前一半的堆节点，对每一个节点进行下滤操作。

主要的数据结构基础：vector。是因为堆的完全二叉树性质，所以选用vector。
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

//将对应的操作进行拷贝之后进行建堆。
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

//依据堆序性质，最小值即为index 1.
template<typename Comparable>
inline const Comparable& BinaryHeap<Comparable>::findMin()
{
	if (currentSize >= 1)
	{
		return heapVec[1];
	}
	return -1;
}

//查看当前是否为0
template<typename Comparable>
inline bool BinaryHeap<Comparable>::isEmpty()
{
	return currentSize==0;
}

//首先将x插入最后（++currentSize），然后使用上滤的操作，找到x的正确位置。
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

//将最后一位赋值给第一位，然后进行下滤
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

//相对于上面的操作，实现了一个引用传值
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

//简单的堆序实现，清空即将size清零
template<typename Comparable>
inline void BinaryHeap<Comparable>::makeEmpty()
{
	currentSize = 0;
}

//并非建树，而是在赋值之后，将整个堆使之符合堆序
template<typename Comparable>
inline void BinaryHeap<Comparable>::buildHeap()
{
	for (int i = currentSize/2; i >0 ; --i)//遍历除了完全二叉树的最后一层，进行下滤。
	{
		percolateDown(i);
	}
}

//为了删除最小值，我们将最后一位的数值替换到第一位，并且将第一位下滤，使其符合堆序。
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
