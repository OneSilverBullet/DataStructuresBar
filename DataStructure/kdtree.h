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

//����ת�ú���
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

//�ҵ���ֵ
template <typename T>
T findMiddleValue(vector<T>& vec)
{
	sort(vec.begin(), vec.end());
	auto pos = vec.size() / 2;
	return vec[pos];
}

//��ʼ����kd��
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
	//������ά��
	unsigned k = data[0].size();
	vector<vector<double>> transData = Transpose(data);
	//ѡ���зֵ�����
	unsigned splitAttribute = depth % k;//��ǰ�ڵ�����������������ģ�������յ�����ֵ
	vector<double> splitAttributeValues = transData[splitAttribute];
	//ѡ���з�ֵ
	double splitValue = findMiddleValue(splitAttributeValues);

	//�����з�ֵ�����ݷֳ������Ӽ�
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
	//�Ӽ����еݹ���н���
	tree->leftChild = new KDTree();
	tree->leftChild->parent = tree;
	tree->rightChild = new KDTree();
	tree->rightChild->parent = tree;
	buildKDTree(tree->leftChild, subset1, depth + 1);
	buildKDTree(tree->rightChild, subset2, depth + 2);
}

//����ӡKD��
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

//���ݲ�ͬ�ķ�ʽ��ŷʽ�����������پ��룩���������ľ���
double measureDistance(vector<double> point1, vector<double> point2, unsigned method)
{
	if (point1.size() != point2.size())
	{
		cerr << "the dimensions not match";
		exit(1);
	}

	switch (method)
	{
	case 0://ŷ�Ͼ���
	{
		double res = 0;
		for (vector<double>::size_type i = 0; i < point1.size(); ++i)
		{
			res += pow((point1[i] - point2[i]), 2);
		}
		return sqrt(res);
	}
	case 1://�����پ���
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
	������KD�������ҳ�����Ŀ����Ҷ�ӽڵ㣺
	�Ӹ��ڵ�������ݹ����·���kd������Ŀ���ĵ�ǰά�ȵ�����
	С���зֵ�����꣬���ƶ������ӽڵ㣬�����ƶ������ӽڵ㡣
	ֱ���ӽڵ�ΪҶ�ڵ�Ϊֹ��
	�����ƶ������ӽڵ㣬֪���ӽڵ�ΪҶ�ӽڵ�Ϊֹ�� �Դ�Ҷ�ӽ�
	��Ϊ����ǰ����㡱��
	*/
	unsigned k = tree->root.size();//��������ݵ�ά��
	unsigned d = 0;//ά�ȳ�ʼ��Ϊ0�����ӵ�1ά��ʼ
	KDTree* currentTree = tree;
	vector<double> currentNearest = currentTree->root;
	while (!currentTree->isLeaf())
	{
		unsigned index = d % k;//���㵱ǰ��
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
	�ݹ�����ϻ��ˣ���ÿһ���ڵ㶼�������µĲ�����
	1������ýڵ㱣���ʵ���ȵ�ǰ��������Ŀ����������ô�øõ�Ϊ����ǰ����㡱
	2����ǰ�����һ��������ĳ���һ���ӽ���Ӧ�����򣬼����ӽ��ĸ��ڵ��
	��һ�ӽ���Ӧ��Ӧ�����Ƿ��и����ĵ㡣
	*/

	//��ǰ�������Ŀ���ľ���
	double currentDistance = measureDistance(goal, currentNearest, 0);

	//�����ǰ��kd���ĸ��ڵ����丸�ڵ�����ӣ������丸�ڵ���Һ��ӡ�
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