#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Union-Find算法

概念：用于解决动态连接性相关问题。动态连通性这个场景而言，我们需要解决的问题可能是：
给出两个节点，判断它们是否连通，如果连通，不需要给出具体的路径。

*/

//首先是基于vector的并查集实现
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

//通过将每一个vector元素都初始化成-1。刚开始每一元素都是单独的树。
//-1代表他们的深度为1。
UnionSet::UnionSet(int elementNum) :s(elementNum)
{
	for (int i = 0; i < elementNum; ++i)
	{
		s[i] = -1;
	}
}

//使用路径压缩的搜索，搜索x节点隶属的set是什么。
//路径压缩：搜索的时候，将其父亲节点设置为其根节点。
int UnionSet::find(int x)
{
	if (s[x] < 0)
	{
		return x;
	}
	return s[x]=find(s[x]);
}

//根节点处记录的是每一个集合当中的深度
//将两个集合进行合并。优先将深度浅的作为深度深的集合的子树。
void UnionSet::unionSets(int root1, int root2)
{
	//先找到两者的根节点
	root1 = find(root1);
	root2 = find(root2);
	//将根节点进行合并
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

//非基于vector的并查集实现，当应用场景不仅仅是简单的数字作为节点的时候。
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
	//如果可以找到对应节点p
	if (data_set.find(p) != data_set.end())
	{
		//如果当前节点是根节点就直接返回。
		if (data_set[p].parent_ == nullptr)
		{
			return data_set[p];
		}
		//如果不是根节点，那么就递归查找其根节点
		else
		{
			return find(data_set[p].parent_->val_);
		}
	}
	//如果找不到节点p，那么创建新节点并且返回
	else
	{
		data_set[p] = UFNode(p);
		return data_set[p];
	}
}

//对p与q进行搜索与合并
bool UFSet::Union(int p, int q)
{
	UFNode& p_root = find(p);
	UFNode& q_root = find(q);
	//如果两者的根值一样，那么返回false，查找失败
	if (p_root.val_ == q_root.val_)
	{
		return false;
	}
	else
	{
		//依据两者rank的级别不同来进行合并
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