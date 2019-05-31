#include "Trie.h"
#include "KMP.h"
#include "vector.h"
#include "List.h"
#include "Tree.h"
#include "AVL.h"
#include "HashTable.h"
#include "Octree.h"
#include "OnevecHashTable.h"
#include "BinaryHeap.h"
#include "Graph-DFS.h"
#include "UnionSet.h"
#include <iostream>


using namespace std;

void TrieTestCase()
{
	Trie<26, Index<26> > t;
	t.Insert("hello");
	t.Insert("hello");
	t.Insert("h");
	t.Insert("h");
	t.Insert("he");
	t.Insert("hel");
	t.Insert("fuck");
	t.Insert("fucking");
	cout << "SizeALL:" << t.sizeAll(t.root) << endl;
	cout << "SizeALL:" << t.sizeAllWithoutRedundant(t.root) << endl;
	t.erase("hello");
	t.erase("hello");
	t.erase("fuck");
	cout << "SizeALL:" << t.sizeAll(t.root) << endl;
	cout << "SizeALL:" << t.sizeAllWithoutRedundant(t.root) << endl;
	system("pause");
}


void KMPTestCase()
{
	KMP kmpComputer;
	int test=kmpComputer("abcdabd","bbcabcdababcdabcdabde");
	cout << test << endl;
	system("pause");
}


void VectorTestCase()
{
	Vector<int> a;
	std::cout << a.Size() << " " << a.Capacity() << std::endl;
	a.Push_back(12);
	a.Push_back(13);
	a.Push_back(18);
	std::cout << a.Size() << " " << a.Capacity() << std::endl;
	for (Vector<int>::iterator ptr = a.Begin(); ptr != a.End(); ptr++)
	{
		std::cout << *ptr << std::endl;
	}
	a.Pop_Back();
	std::cout << a.Size() << " " << a.Capacity() << std::endl;
	system("pause");
}


void ListTestCase()
{
	List<int> a;
	a.Push_back(10);
	a.Push_back(20);
	a.Push_front(30);
	a.Push_front(40);
	for (List<int>::iterator i = a.Begin(); i != a.End(); ++i)
	{
		cout << *i << " ";
	}cout << endl;
	a.Pop_back();
	a.Pop_front();
	for (List<int>::iterator i = a.Begin(); i != a.End(); ++i)
	{
		cout << *i << " ";
	}cout << endl;
	a.Clear();
	for (List<int>::iterator i = a.Begin(); i != a.End(); ++i)
	{
		cout << *i << " ";
	}cout << endl;
	system("pause");
}


void BSTTestCase()
{
	BinarySearchTree<int> bst;
	bst.Insert(15);
	bst.Insert(5);
	bst.Insert(89);
	bst.Insert(99);
	bst.Insert(35);
	bst.Insert(28);
	bst.Insert(7);
	bst.PrintTree();
	bst.Remove(99);
	bst.Remove(5);
	bst.PrintTree();
	cout << endl;
	cout << bst.FindMax() << endl;
	cout << bst.FindMin() << endl;
	cout << bst.Contains(99) << endl;
	cout << bst.Contains(35) << endl;

	system("pause");
}

void AVLTestCase()
{
	AVLTree<int> myavl;
	myavl.insert(15);
	myavl.insert(8);
	myavl.insert(19);
	myavl.insert(87);
	myavl.insert(145);
	myavl.insert(1);
	myavl.insert(999);
	cout << "after insert" << endl;
	myavl.PrintT();
	myavl.remove(19);
	myavl.remove(15);
	cout << "after delete" << endl;
	myavl.PrintT();

	system("pause");
}

void HashTableTestCase()
{
	HashTable<int> a(13);
	a.insert(12);
	a.insert(124);
	a.insert(99);
	a.insert(3243);
	a.insert(62);
	a.insert(72);
	a.insert(13);
	a.insert(29);
	a.insert(362);
	a.insert(5763);
	a.show();

	a.remove(13);
	a.remove(5763);
	a.show();

	system("pause");
}


void OctreeTestCase()
{
	OctreeNode<double> *rootNode = NULL;
	int choiced = 0;
	int maxdepth;
	while (true)
	{
		system("cls");
		cout << "请选择操作：\n";
		cout << "1.创建八叉树 2.先序遍历八叉树\n";
		cout << "3.查看树深度 4.查找节点   \n";
		cout << "0.退出\n\n";
		cin >> choiced;
		if (choiced == 0)
			return;
		else if (choiced == 1)
		{
			system("cls");
			cout << "请输入最大递归深度：" << endl;
			cin >> maxdepth;//递归深度
			cout << "请输入外包盒坐标，顺序如下：xmin,xmax,ymin,ymax,zmin,zmax" << endl;
			int xmin, xmax, ymin, ymax, zmin, zmax;
			cin >> xmin >> xmax >> ymin >> ymax >> zmin >> zmax;
			if (maxdepth >= 0 || xmax > xmin || ymax > ymin || zmax > zmin || xmin > 0 || ymin > 0 || zmin > 0)
			{
				CreateOctree(rootNode, maxdepth, xmin, xmax, ymin, ymax, zmin, zmax);

				cout << "8叉树创建完毕, input the 'continue' to  \n" << endl; 
			}
			else
			{
				cout << "输入错误！";
				return;
			}
		}
		else if (choiced == 2)
		{
			system("cls");
			cout << "先序遍历八叉树结果：/n";
			PreOrder(rootNode);
			cout << endl;
			system("pause");
		}
		else if (choiced == 3)
		{
			system("cls");
			int dep = GetDepth(rootNode);
			cout << "此八叉树的深度为" << dep + 1 << endl;
			system("pause");
		}
		else if (choiced == 4)
		{
			system("cls");
			cout << "请输入您希望查找的点的坐标，顺序如下：x,y,z\n";
			double x, y, z;
			cin >> x >> y >> z;
			cout << endl << "开始搜寻该点……" << endl;
			Find(rootNode, x, y, z, 0);
			system("pause");
		}
		else
		{
			system("cls");
			cout << "\n\n错误选择！\n";
			system("pause");
		}
	}

	system("pause");
	return;
}

void OnevecHashTableTestCase()
{
	OnevecHashTable<int> a(11);
	//a.insert(123);
	a.insert(87);
	a.insert(22);
	a.insert(213);
	a.insert(265);
	a.insert(23);
	a.insert(64);
	a.show();
	a.remove(64);
	a.remove(23);
	a.remove(265);
	a.show();
	system("pause");
}

void BinaryHeapTestCase()
{
	BinaryHeap<int> a(11);
	a.insert(12);
	a.insert(24);
	a.insert(78);
	a.insert(3);
	a.insert(38);
	a.insert(17);
	a.insert(39);
	int x;
	a.removeMin(x);
	cout << x << endl;
	a.removeMin(x);
	cout << x << endl;
	a.removeMin(x);
	cout << x << endl;
	system("pause");
}



int main()
{
	//TrieTestCase();
	//KMPTestCase();
	//VectorTestCase();
	//ListTestCase();
	//BSTTestCase();
	//AVLTestCase();
	//HashTableTestCase();
	//OctreeTestCase();
	//OnevecHashTableTestCase();
	//BinaryHeapTestCase();
	//GraphDFSTestCase();
	//FloydTestCase();
	//DijkstraTestCase();
	//SPFATestCase();
	UnionSetTestCase();
	system("pause");
}