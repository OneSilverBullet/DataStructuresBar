#include "Trie.h"
#include "KMP.h"
#include "vector.h"
#include "List.h"
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


int main()
{
	//TrieTestCase();
	//KMPTestCase();
	//VectorTestCase();
	ListTestCase();
}