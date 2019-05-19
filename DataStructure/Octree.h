#pragma once
#include <iostream>

/*
定义:用于描述三维空间的一种树状高级数据结构。每个节点相当于一个体素。八个体素的体积之和等于父节点体
积。

原理思想：
1.设定最大递归深度。找出当前场景的最大尺寸，并且以此建立八叉树。
2.依次将单位元元素丢入能被包含但是没有子节点的立方体当中。
3.若没有达到最大递归深度，那么就进行细分八等分，将立方体当中所装的单位元元素全部分担给八个子空间。
4.若分配到的元素不为0且总量与父节点相同。那么就停止分割，因为这一块立方体全都是体素。不必继续分割造
成无限分割。

节点分类：
灰色节点：部分空间被形体占据。
白色节点：没有空间被形体占据。
黑色节点：全部空间被形体占据。

*/

using namespace std;


template<typename T>
struct OctreeNode
{
	T data;
	double xmin, xmax;
	double ymin, ymax;
	double zmin, zmax;
	OctreeNode<T>* bottome_left_front;
	OctreeNode<T>* bottome_left_back;
	OctreeNode<T>* bottome_right_front;
	OctreeNode<T>* bottome_right_back;
	OctreeNode<T>* up_left_front;
	OctreeNode<T>* up_left_back;
	OctreeNode<T>* up_right_front;
	OctreeNode<T>* up_right_back;

	OctreeNode() {}
	OctreeNode(T d, double xmi, double xma, double ymi, double yma, double zmi, double zma,
		OctreeNode<T>* bottome_left_front_val = nullptr,
		OctreeNode<T>* bottome_left_back_val = nullptr,
		OctreeNode<T>* bottome_right_front_val = nullptr,
		OctreeNode<T>* bottome_right_back_val = nullptr,
		OctreeNode<T>* up_left_front_val = nullptr,
		OctreeNode<T>* up_left_back_val = nullptr,
		OctreeNode<T>* up_right_front_val = nullptr,
		OctreeNode<T>* up_right_back_val = nullptr
	) :data(d), xmin(xmi), xmax(xma), ymin(ymi), ymax(yma), zmin(zmi), zmax(zma),
		bottome_left_back(bottome_left_back_val),
		bottome_left_front(bottome_left_front_val),
		bottome_right_front(bottome_right_front_val),
		bottome_right_back(bottome_right_back_val),
		up_left_back(up_left_back_val),
		up_left_front(up_left_front_val),
		up_right_back(up_right_back_val),
		up_right_front(up_right_front_val)
	{
		cout << "Create OcTree" << endl;
	}
};


template<typename T>
void CreateOctree(OctreeNode<T>* & root, int maxdepth, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
	maxdepth--;
	if (maxdepth >= 0)
	{
		root = new OctreeNode<T>();
		root->data = 9; //此处简单赋值

		root->xmin = xmin;
		root->xmax = xmax;
		root->ymin = ymin;
		root->ymax = ymax;
		root->zmin = zmin;
		root->zmax = zmax;

		double xm = (xmax - xmin) / 2;
		double ym = (ymax - ymin) / 2;
		double zm = (zmax - zmin) / 2;

		CreateOctree(root->bottome_left_front, maxdepth, xmin, xmin + xm, ymin, ymin + ym, zmax - zm, zmax);
		CreateOctree(root->bottome_left_back, maxdepth, xmin, xmin + xm, ymin, ymin + ym, zmin, zmin + zm);
		CreateOctree(root->bottome_right_front, maxdepth, xmin + xm, xmax, ymin, ymin + ym, zmax - zm, zmax);
		CreateOctree(root->bottome_right_back, maxdepth, xmin + xm, xmax, ymin, ymin + ym, zmin, zmin + zm);
		
		CreateOctree(root->up_left_front, maxdepth, xmin, xmin + xm, ymin+ym, ymax, zmax - zm, zmax);
		CreateOctree(root->up_left_back, maxdepth, xmin, xmin + xm, ymin+ym, ymax, zmin, zmin + zm);
		CreateOctree(root->up_right_front, maxdepth, xmin + xm, xmax, ymin+ym, ymax, zmax - zm, zmax);
		CreateOctree(root->up_right_back, maxdepth, xmin + xm, xmax, ymin+ym, ymax, zmin, zmin + zm);

	}
	else
	{
		//递归结束
		cout << "End the recall" << endl;
	}
}

template<typename T>
void PreOrder(OctreeNode<T>* root)
{
	if (root != nullptr)
	{
		cout << "preorder of the octree" << endl;
		cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
		cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
		cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;

		if(root->up_left_front!=nullptr)PreOrder(root->up_left_front);
		if (root->up_left_back != nullptr)PreOrder(root->up_left_back);
		if (root->up_right_front != nullptr)PreOrder(root->up_right_front);
		if (root->up_right_back != nullptr)PreOrder(root->up_right_back);
		if (root->bottome_left_front != nullptr)PreOrder(root->bottome_left_front);
		if (root->bottome_left_back != nullptr)PreOrder(root->bottome_left_back);
		if (root->bottome_right_front != nullptr)PreOrder(root->bottome_right_front);
		if (root->bottome_right_back != nullptr)PreOrder(root->bottome_right_back);
		cout << endl;
	}
}

template<typename T>
int GetDepth(OctreeNode<T>* root)
{
	if (root == nullptr)return -1;
	int d = GetDepth(root->up_left_back);
	return d + 1;
}

template<typename T>
void Find(OctreeNode<T>* root, double x, double y, double z, int times)
{
	if (root == nullptr)
	{
		return;
	}
	else
	{
		times++;
		double xm = (root->xmax - root->xmin) / 2;
		double ym = (root->ymax - root->ymin) / 2;
		double zm = (root->zmax - root->zmin) / 2;

		if (x > root->xmax || x<root->xmin || y>root->ymax || y<root->ymin || z>root->zmax || z < root->zmin)
		{
			cout << "Not in the scene" << endl;
			return;
		}
		if (x <= (root->xmin + xm) && x >= (root->xmax - xm) && y <= (root->ymin + ym)
			&& y >= (root->ymax - ym) && z <= (root->zmin + zm) && z >= (root->zmax - zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
		}
		else if (x < (root->xmin + xm) && y < (root->ymin + ym) && z < (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->bottome_left_back, x, y, z, times);
		}
		else if (x < (root->xmin + xm) && y < (root->ymin + ym) && z > (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->bottome_left_front, x, y, z, times);
		}
		else if (x > (root->xmin + xm) && y < (root->ymin + ym) && z < (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->bottome_right_back, x, y, z, times);
		}
		else if (x > (root->xmin + xm) && y < (root->ymin + ym) && z > (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->bottome_right_front, x, y, z, times);
		}
		else if (x < (root->xmin + xm) && y > (root->ymin + ym) && z < (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->up_left_back, x, y, z, times);
		}
		else if (x < (root->xmin + xm) && y > (root->ymin + ym) && z >(root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->up_left_front, x, y, z, times);
		}
		else if (x > (root->xmin + xm) && y > (root->ymin + ym) && z < (root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->up_right_back, x, y, z, times);
		}
		else if (x > (root->xmin + xm) && y > (root->ymin + ym) && z >(root->zmin + zm))
		{
			cout << "Has Find Point" << endl;
			cout << "Times: " << times << endl;
			cout << " xmin " << root->xmin << " xmax " << root->xmax << endl;
			cout << " ymin " << root->ymin << " ymax " << root->ymax << endl;
			cout << " zmin " << root->zmin << " zmax " << root->zmax << endl;
			cout << endl;
			Find(root->up_right_front, x, y, z, times);
		}
	}
}