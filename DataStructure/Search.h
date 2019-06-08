#pragma once
#include <vector>
using namespace std;


//��������
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


//ϣ������
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

//������
//�ҵ�����
int leftchild(int i)
{
	return i * 2 + 1;
}

//���˲���
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

//�Ѳ���
template<typename Comparable>
void heapsort(vector<Comparable>& vec)
{
	//���Ƚ���ǰvec���������гɶ���
	for (int i = vec.size / 2; i >= 0; --i)
	{
		percDown(vec, i, vec.size());
	}
	//Ȼ�����ֵ�ŵ����һλ��������ǰ������гɶ���
	for (int i = vec.size()-1; i >0; ++i)
	{
		swap(vec[0], vec[i]);
		percDown(vec, 0, i);
	}
}

//�鲢����
//һ�εݹ�ѭ������Ե�ǰ��Χ�ڽ��еݹ����
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

//������Ҫ�ĵݹ����
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

//����tmp������Ϊһ�����õķ�װ������
template<typename Comparable>
void mergeSort(vector<Comparable>& vec)
{
	vector<Comparable> tmp(vec.size());
	mergeSort(vec, tmp, 0, vec.size() - 1);
}