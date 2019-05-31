#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Union-Find�㷨

������ڽ����̬������������⡣��̬��ͨ������������ԣ�������Ҫ�������������ǣ�
���������ڵ㣬�ж������Ƿ���ͨ�������ͨ������Ҫ���������·����

*/

//�����ǻ���vector�Ĳ��鼯ʵ��
class UnionSet
{
public:
	explicit UnionSet(int elementNum);
	int find(int x);
	void unionSets(int root1, int root2);
	void show()
	{
		for (int i = 0; i < s.size(); ++i)
		{
			cout << s[i] << " ";
		}cout << endl;
	}
private:
	vector<int> s;
};

//ͨ����ÿһ��vectorԪ�ض���ʼ����-1���տ�ʼÿһԪ�ض��ǵ���������
//-1�������ǵ����Ϊ1��
UnionSet::UnionSet(int elementNum) :s(elementNum)
{
	for (int i = 0; i < elementNum; ++i)
	{
		s[i] = -1;
	}
}

//ʹ��·��ѹ��������������x�ڵ�������set��ʲô��
//·��ѹ����������ʱ�򣬽��丸�׽ڵ�����Ϊ����ڵ㡣
int UnionSet::find(int x)
{
	if (s[x] < 0)
	{
		return x;
	}
	return s[x]=find(s[x]);
}

//���ڵ㴦��¼����ÿһ�����ϵ��е����
//���������Ͻ��кϲ������Ƚ����ǳ����Ϊ�����ļ��ϵ�������
void UnionSet::unionSets(int root1, int root2)
{
	//���ҵ����ߵĸ��ڵ�
	root1 = find(root1);
	root2 = find(root2);
	//�����ڵ���кϲ�
	if (s[root2] < s[root1])
	{
		s[root1] = root2;
	}
	else
	{
		if (s[root2] == s[root1])
		{
			s[root1]--;
		}
		s[root2] = root1;
	}
}

void UnionSetTestCase()
{
	UnionSet a(10);
	a.unionSets(1, 2);
	a.unionSets(3, 7);
	a.unionSets(5, 3);
	a.unionSets(2, 7);
	a.unionSets(9, 0);
	a.show();
	cout << "find 5's root: "<< a.find(5) << endl;
	cout << "find 5's root: "<< a.find(7) << endl;
	a.show();
}

//�ǻ���vector�Ĳ��鼯ʵ�֣���Ӧ�ó����������Ǽ򵥵�������Ϊ�ڵ��ʱ��
class UFNode
{
public:
	int val_;
	UFNode* parent_;
	int rank_;
	explicit UFNode(int value):val_(value), rank_(0), parent_(nullptr){}
};

class UFSet
{
public:
	unordered_map<int, UFNode> data_set;
	UFSet(int n);
	UFNode& find(int p);
	bool Union(int p, int q);
};


UFSet::UFSet(int n)
{
	data_set.reserve(n);
}

UFNode& UFSet::find(int p)
{
	//��������ҵ���Ӧ�ڵ�p
	if (data_set.find(p) != data_set.end())
	{
		//�����ǰ�ڵ��Ǹ��ڵ��ֱ�ӷ��ء�
		if (data_set[p].parent_ == nullptr)
		{
			return data_set[p];
		}
		//������Ǹ��ڵ㣬��ô�͵ݹ��������ڵ�
		else
		{
			return find(data_set[p].parent_->val_);
		}
	}
	//����Ҳ����ڵ�p����ô�����½ڵ㲢�ҷ���
	else
	{
		data_set[p] = UFNode(p);
		return data_set[p];
	}
}

//��p��q����������ϲ�
bool UFSet::Union(int p, int q)
{
	UFNode& p_root = find(p);
	UFNode& q_root = find(q);
	//������ߵĸ�ֵһ������ô����false������ʧ��
	if (p_root.val_ == q_root.val_)
	{
		return false;
	}
	else
	{
		//��������rank�ļ���ͬ�����кϲ�
		if (p_root.rank_ > q_root.rank_)
		{
			q_root.parent_ = &p_root;
		}
		else if (p_root.rank_ < q_root.rank_)
		{
			p_root.parent_ = &q_root;
		}
		else
		{
			q_root.parent_ = &p_root;
			q_root.rank_++;
		}
	}
	return true;
}