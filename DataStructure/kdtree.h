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


vector<double> searchNearestNeighbor(vector<double> goal, KDTree* tree)
{
	/*
	首先在KD树当中找出包含目标点的叶子节点：
	从根节点出发，递归向下访问kd树，若目标点的当前维度的坐标
	小于切分点的坐标，则移动到左子节点，否则移动到右子节点。
	直到子节点为叶节点为止。
	否则移动到右子节点，知道子节点为叶子节点为止， 以此叶子节
	点为“当前最近点”。
	*/
	unsigned k = tree->root.size();//计算出数据的维度
	unsigned d = 0;//维度初始化为0，即从第1维开始
	KDTree* currentTree = tree;
	vector<double> currentNearest = currentTree->root;
	while (!currentTree->isLeaf())
	{
		unsigned index = d % k;//计算当前堆
		if (currentTree->rightChild->isEmpty() || goal[index] < currentNearest[index])
		{
			currentTree = currentTree->leftChild;
		}
		else
		{
			currentTree = currentTree->rightChild;
		}
		++d;
	}
	currentNearest = currentTree->root;

	/*
	递归的向上回退，在每一个节点都进行如下的操作：
	1、如果该节点保存的实例比当前最近点距离目标点更近，那么用该点为“当前最近点”
	2、当前最近点一定存在于某结点一个子结点对应的区域，检查该子结点的父节点的
	另一子结点对应对应区域是否有更近的点。
	*/

	//当前最近邻与目标点的距离
	double currentDistance = measureDistance(goal, currentNearest, 0);

	//如果当前子kd树的根节点是其父节点的左孩子，搜索其父节点的右孩子。
	KDTree* searchDistrict;
	if (currentTree->isLeft())
	{
		if (currentTree->parent->rightChild == NULL)
		{
			searchDistrict = currentTree;
		}
		else
		{
			searchDistrict = currentTree->parent->rightChild;
		}
	}
	else
	{
		searchDistrict = currentTree->parent->leftChild;
	}

	while (searchDistrict->parent != NULL)
	{
		double districtDistance = abs(goal[(d + 1) % k] - searchDistrict->parent->root[(d + 1) % k]);

		if (districtDistance < currentDistance)
		{
			double parentDistance = measureDistance(goal, searchDistrict->parent->root, 0);

			if (parentDistance < currentDistance)
			{
				currentDistance = parentDistance;
				currentTree = searchDistrict->parent;
				currentNearest = currentTree->root;
			}

			if (!searchDistrict->isEmpty())
			{
				double rootDistance = measureDistance(goal, searchDistrict->root, 0);
				if (rootDistance < currentDistance)
				{
					currentDistance = rootDistance;
					currentTree = searchDistrict;
					currentNearest = currentTree->root;
				}
			}

			if (searchDistrict->leftChild != NULL)
			{
				double leftDistance = measureDistance(goal, searchDistrict->leftChild->root, 0);
				if (leftDistance < currentDistance)
				{
					currentDistance = leftDistance;
					currentTree = searchDistrict;
					currentNearest = currentTree->root;
				}
			}

			if (searchDistrict->rightChild != NULL)
			{
				double rightDistance = measureDistance(goal, searchDistrict->rightChild->root, 0);
				if (rightDistance < currentDistance)
				{
					currentDistance = rightDistance;
					currentTree = searchDistrict;
					currentNearest = currentTree->root;
				}
			}
		}

		if (searchDistrict->parent->parent != NULL)
		{
			searchDistrict = searchDistrict->parent->isLeft() ?
				searchDistrict->parent->parent->rightChild :
				searchDistrict->parent->parent->leftChild;
		}
		else
		{
			searchDistrict = searchDistrict->parent;
		}
		++d;
	}//end wguke

	return currentNearest;
}