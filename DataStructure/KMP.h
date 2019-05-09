#pragma once
#include <string>
#include <vector>
using namespace std;

//KMP�㷨���㷨��������
//���ڿ���ƥ���ַ���
class KMP
{
public:

	int operator()(string t, string o)
	{
		Intialise(t, o);//���Ƚ��г�ʼ��
		KMPPreprocess();//����target�ĸ�������
		return KMPComputation();//���ݸ�������������origin�ַ���
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
					return i - m + 1;//����ƥ��ĵ�һ���ַ���index
					j = pre[j - 1] + 1;//��������һ��ƥ���ģʽ��
				}
			}
			else {
				if (j == 0)//����һλ��ûƥ���ϣ���ôֱ�Ӻ���
				{
					i++;
				}
				else
				{
					j = pre[j - 1] + 1;//�����¿�ʼ�����Ǵ�target֮ǰ��λ�ý���ƥ��
				}
			}
		}
		return -1; //û��ƥ��
	}

};
