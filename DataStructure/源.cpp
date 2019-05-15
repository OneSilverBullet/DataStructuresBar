#include "Trie.h"
#include "KMP.h"
#include "vector.h"
#include "List.h"
#include "Tree.h"
#include "AVL.h"
#include "HashTable.h"
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


int main()
{
	//TrieTestCase();
	//KMPTestCase();
	//VectorTestCase();
	//ListTestCase();
	//BSTTestCase();
	//AVLTestCase();
	HashTableTestCase();
}