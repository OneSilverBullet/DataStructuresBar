#pragma once
#include <string>
#include <vector>
using namespace std;

//KMP算法的算法函数对象
//用于快速匹配字符串
class KMP
{
public:

	int operator()(string t, string o)
	{
		Intialise(t, o);//首先进行初始化
		KMPPreprocess();//计算target的辅助数组
		return KMPComputation();//依据辅助数组来计算origin字符串
	}


private:
	string target;
	vector<int> pre;
	string origin;


	void Intialise(string t, string o)
	{
		target = t;
		origin = o;
		pre.resize(t.size());
		for (int i = 0; i < pre.size(); ++i)
		{
			pre[i] = -1;
		}
	}

	void KMPPreprocess()
	{
		for (int i = 1; i < target.size(); ++i)
		{
			int j = pre[i - 1];
			while ((target[j + 1] != target[i]) && (j >= 0))
			{
				j = pre[j];
			}
			if (target[j + 1] == target[i])
			{
				pre[i] = j + 1;
			}
			else
			{
				pre[i] = -1;
			}
		}
	}

	int KMPComputation()
	{
		int n = origin.size();
		int m = target.size();
		int i = 0;
		int j = 0;
		while (i < n)
		{
			if (origin[i] == target[j])
			{
				i++;
				j++;
				if (j == m)
				{
					return i - m + 1;//返回匹配的第一个字符的index
					j = pre[j - 1] + 1;//这里是下一个匹配的模式串
				}
			}
			else {
				if (j == 0)//当第一位就没匹配上，那么直接后移
				{
					i++;
				}
				else
				{
					j = pre[j - 1] + 1;//不重新开始，而是从target之前的位置进行匹配
				}
			}
		}
		return -1; //没有匹配
	}

};
