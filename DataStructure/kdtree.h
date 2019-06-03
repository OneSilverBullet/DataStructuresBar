#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

struct KDTree
{
	vector<double> root;
	KDTree* parent;
	KDTree* leftChild;
	KDTree* rightChild;

	KDTree() :parent(nullptr), leftChild(nullptr), rightChild(nullptr){}

	bool isEmpty()
	{
		return root.empty();
	}

	bool isLeaf()
	{
		return (!root.empty()) && rightChild == nullptr&&leftChild == nullptr;
	}

	bool isRoot()
	{
		return (!isEmpty()) && parent == nullptr;
	}

	bool isLeft()
	{
		return parent->leftChild->root == root;
	}

	bool isRight()
	{
		return parent->rightChild->root == root;
	}

};

//矩阵转置函数
template<typename T>
vector<vector<T>> Transpose(const vector<vector<T>>& matrix)
{
	unsigned cow = matrix.size();
	unsigned row = matrix[0].size();
	vector<vector<T>> m2(row, vector<int>(cow, 0));
	for (unsigned i = 0; i < cow; ++i)
	{
		for (unsigned j = 0; j < row; ++j)
		{
			m2[j][i] = matrix[i][j];
		}
	}
	return m2;
}

//找到中值
template <typename T>
T findMiddleValue(vector<T>& vec)
{
	sort(vec.begin(), vec.end());
	auto pos = vec.size() / 2;
	return vec[pos];
}

//开始创建kd树
void buildKDTree(KDTree* tree, vector<vector<double>>& data, unsigned depth)
{
	unsigned sampleNum = data.size();
	
	if (sampleNum == 0)
	{
		return;
	}
	if (sampleNum == 1)
	{
		tree->root = data[0];
		return;
	}
	//样本的维度
	unsigned k = data[0].size();
	vector<vector<double>> transData = Transpose(data);
	//选择切分的属性
	unsigned splitAttribute = depth % k;//当前节点的深度与属性数量的模就是最终的属性值
	vector<double> splitAttributeValues = transData[splitAttribute];
	//选择切分值
	double splitValue = findMiddleValue(splitAttributeValues);

	//依据切分值将数据分成两个子集
	vector<vector<double>> subset1;
	vector<vector<double>> subset2;
	for (unsigned i = 0; i < sampleNum; ++i)
	{
		if (splitAttributeValues[i] == splitValue && tree->root.empty())
		{
			tree->root = data[i];
		}
		else
		{
			if (splitAttributeValues[i] < splitValue)
			{
				subset1.push_back(data[i]);
			}
			else
			{
				subset2.push_back(data[i]);
			}
		}
	}
	//子集进行递归进行建树
	tree->leftChild = new KDTree();
	tree->leftChild->parent = tree;
	tree->rightChild = new KDTree();
	tree->rightChild->parent = tree;
	buildKDTree(tree->leftChild, subset1, depth + 1);
	buildKDTree(tree->rightChild, subset2, depth + 2);
}

//逐层打印KD树
void printKDTree(KDTree* tree, unsigned depth)
{
	for (unsigned i = 0; i < depth; ++i)
	{
		cout << "\t";
	}
	for (vector<double>::size_type j = 0; j < tree->root.size(); ++j)
	{
		cout << tree->root[j] << ",";
	}
	cout << endl;
	if (tree->leftChild == nullptr&&tree->rightChild == nullptr)
	{
		return;
	}
	else
	{
		if (tree->leftChild != nullptr)
		{
			for (unsigned i = 0; i < depth + 1; ++i)
			{
				cout << "\t";
			}
			cout << "left: ";
			printKDTree(tree->leftChild, depth + 1);
		}
		cout << endl;
		if(tree->rightChild!=nullptr)
		{
			for (unsigned i = 0; i < depth + 1; ++i)
			{
				cout << "\t";
			}
			cout << "right: ";
			printKDTree(tree->rightChild, depth + 1);
		}
		cout << endl;
	}
}

//依据不同的方式（欧式距离与曼哈顿距离）求解两个点的距离
double measureDistance(vector<double> point1, vector<double> point2, unsigned method)
{
	if (point1.size() != point2.size())
	{
		cerr << "the dimensions not match";
		exit(1);
	}

	switch (method)
	{
	case 0://欧氏距离
	{
		double res = 0;
		for (vector<double>::size_type i = 0; i < point1.size(); ++i)
		{
			res += pow((point1[i] - point2[i]), 2);
		}
		return sqrt(res);
	}
	case 1://曼哈顿距离
	{
		double res = 0;
		for (vector<double>::size_type i = 0; i < point1.size(); ++i)
		{
			res += abs(point1[i] - point2[i]);
		}
		return res;
	}
	default:
		cerr << "Invalid Method" << endl;
		return -1;
	}
}


vector<double> searchNearestNeighbor(vector<int> goal, KDTree* tree)
{
	unsigned k = tree->root.size();//计算出数据的维度
	unsigned d = 0;//维度初始化为0，即从第1维开始
	KDTree* currentTree = tree;
	vector<double> currentNearest = currentTree->root;
	while (!currentTree->isLeaf())
	{

	}




}