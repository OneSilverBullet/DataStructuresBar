#pragma once
#include <vector>
using namespace std;


//插入排序
template<typename Comparable>
void insertion(vector<Comparable>& target)
{
	int j;
	for (int i = 1; i < target.size(); ++i)
	{
		Comparable tmp = target[i];
		for (j = i; j > 0 && tmp < target[j-1]; --j)
		{
			target[j] = target[j - 1];
		}
		target[j] = tmp;
	}
}


//希尔排序
template<typename Comparable>
void shellsort(vector<Comparable>& target)
{
	for (int gap = target.size() / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < target.size(); ++i)
		{
			int j = i;
			Comparable tmp = target[i];
			for (; j > 0 && tmp < target[j - gap]; j -= gap)
			{
				target[j] = target[j-gap];
			}
			target[j] = tmp;
		}
	}
}

//堆排序
//找到左孩子
int leftchild(int i)
{
	return i * 2 + 1;
}

//下滤操作
template<typename Comparable>
void percDown(vector<Comparable>& vec, int i, int n)
{
	int child;
	Comparable tmp;
	for (tmp = a[i]; leftchild(i) < n; i = child)
	{
		child = leftchild(i);
		if (child + 1 < n&&vec[child] > vec[child + 1])
		{
			child++;
		}
		if (tmp < target[child])
		{
			target[i] = target[child];
		}
		else
		{
			break;
		}
	}
	target[i] = tmp;
}

//堆操作
template<typename Comparable>
void heapsort(vector<Comparable>& vec)
{
	//首先将当前vec的数据排列成堆序
	for (int i = vec.size / 2; i >= 0; --i)
	{
		percDown(vec, i, vec.size());
	}
	//然后将最大值放到最后一位，继续将前面的排列成堆序
	for (int i = vec.size()-1; i >0; ++i)
	{
		swap(vec[0], vec[i]);
		percDown(vec, 0, i);
	}
}

//归并排序
//一次递归循环，针对当前范围内进行递归操作
template<typename Comparable>
void merge(vector<Comparable>& vec, vector<Comparable>& tmp, int leftpos, int rightpos, int rightend)
{
	int leftend = rightpos - 1;
	int tmppos = leftpos;
	int numelements = rightend - leftpos + 1;
	while (leftpos <= leftend && rightpos <= rightend)
	{
		if (vec[leftpos] <= vec[rightpos])
		{
			tmp[tmppos++] = vec[leftpos++];
		}
		else
		{
			tmp[tmppos++] = vec[rightpos++];
		}
	}
	while (leftpos <= leftend)
	{
		tmp[tmppos++] = vec[leftpos++];
	}
	while (rightpos<=rightend)
	{
		tmp[tmppos++] = vec[rightpos++];
	}

	for (int i = 0; i < numelements; i++, rightend--)
	{
		vec[rightend] = tmp[rightend];
	}
}

//进行主要的递归过程
template<typename Comparable>
void mergeSort(vector<Comparable>& vec, vector<Comparable>& tmp, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(vec, tmp, left, center);
		mergeSort(vec, tmp, center + 1, right);
		merge(vec, tmp, left, center + 1, right);
	}
}

//创建tmp并且作为一个良好的封装而存在
template<typename Comparable>
void mergeSort(vector<Comparable>& vec)
{
	vector<Comparable> tmp(vec.size());
	mergeSort(vec, tmp, 0, vec.size() - 1);
}