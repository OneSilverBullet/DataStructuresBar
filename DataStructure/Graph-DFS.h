#pragma once
#include <iostream>
#include <queue>
#define nmax 110
#define inf 999999999
using namespace std;

int n, m, minPath, edge[nmax][nmax], mark[nmax];
int minvalue[nmax];

void dfs(int cur, int target, int dst)
{
	//当前路径比最小路径大那么直接返回
	if (minPath < dst)
	{
		return;
	}
	//如果当前路径与target一样的话，那么检测更新
	if (cur == target)
	{
		if (minPath > dst)
		{
			minPath = dst;
		}
		return;
	}
	else
	{
		//这里用回溯的方案依次找到对应的方案
		int i;
		for (i = 1; i <= n; ++i)
		{
			if (edge[cur][i] != inf && edge[cur][i] != 0 && mark[cur] == 0)
			{
				mark[i] = 1;
				dfs(i, target, dst + edge[cur][i]);
				mark[i] = 0;
			}
		}
	}
}


void GraphDFSTestCase()
{
	//n代表节点个数，m代表边的个数
	while (cin >> n >> m && n != 0)
	{
		//依据节点建图
		int i, j;
		for (i = 1; i <= n; ++i)
		{
			for (j = 1; j <= n; ++j)
			{
				edge[i][j] = inf;
			}
			edge[i][i] = 0;
		}
		//依据图来输入对应的边权值
		int a, b;
		while (m--)
		{
			cin >> a >> b;
			cin >> edge[a][b];
		}

		memset(mark, 0, sizeof(mark));
		minPath = inf;
		mark[1] = 1;
		dfs(2,5,0);
		cout << minPath;

	}


}

/*
Floyd算法是一种经典的动态规划算法。
主要思想：从任意顶点u到任意顶点v的最短路径一共有两种可能：1.直接从u到v。
2.从u经过若干顶点k到达v。所以，我们假设dist(u,v)为顶点u到顶点v的最短路
径距离。所以我们检查dist(u,k)+dist(k,v)<dist(u,v)是否成立。如果成立，
那么就更新dist(u,v)。当我们遍历完所有的值，dist(u,v)就是从u到v的最短距。

算法流程：
1.初始化。所有两点之间的距离都是边的权，如果两点之间没
有边相连，那么权值为无穷大。
2.如果对于节点u与v，存在一个顶点w使得从u到v比已知的路径更短，那么更新他。

算法效果：
Floyd算法的时间复杂度是O(n^3),空间复杂度是O(n^2)。可以获得任何顶点对之间
的最短路径。

应用：
Floyd算法在邻接矩阵和邻接表这两种图表现形式下都可以使用。用于解决多源最短
路径问题。

*/

void FloydTestCase()
{
	while (cin >> n >> m && n != 0)
	{
		int i, j;
		for (i = 1; i <= n; ++i)
		{
			for (j = 1; j <= n; ++j)
			{
				edge[i][j] = inf;
			}
			edge[i][i] = 0;
		}

		while (m--)
		{
			cin >> i >> j;
			cin >> edge[i][j];
			//是否为无向图
			//edge[j][i] = edge[i][j];
		}


		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				cout << edge[i][j] << " ";
			}cout << endl;
		}
		cout << endl;

		int k;
		for (k = 1; k <= n; ++k)
		{
			for (i = 1; i <= n; ++i)
			{
				for (j = 1; j <= n; ++j)
				{
					if (edge[i][k] < inf&&edge[k][j]<inf&&edge[i][j]>edge[i][k] + edge[k][j])
					{
						edge[i][j] = edge[i][k] + edge[k][j];
					}
				}
			}
		}

		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= n; ++j)
			{
				cout << edge[i][j] << " ";
			}cout << endl;
		}

		cout << " from 1 - n : " << edge[1][n] << endl;
		cout << " from 2 - n-1 : " << edge[2][n - 1] << endl;
	}
}

/*
Dijkstra算法
定义：典型的单源最短路径算法，用于计算某个顶点到其他所有顶点的最短路径。
要求图中不存在负值。

思想：从原点出发，每次选择离原点最近的一个顶点前进，然后以该顶点为中心
进行扩展。

算法流程：
1.已知最短路程的顶点集合P与未知最短路径的顶点几何Q。使用book来记录哪些
点在几何P当中。
2.在Q当中选择一个离原点最近的顶点u（dist最小）加入到P当中，并且考察所有
以点u为起点的边，对每一条边进行松弛操作。
4.重复3，如果Q为空，那么算法结束。dist数组的值就是源点到所有顶点的最小
路径。

算法效果：
如果使用最小堆进行维护（在2当中用到），算法的时间复杂度为O（nlogn）

示例问题：给出n个点，m条边，每条边都有长度d和花费p，给出起点s，终点t。
要求输出起点到终点的最短距离以及花费，如果最短路径有多条路线，那么就输
出花费最少的。
*/

struct Edge
{
	int len;
	int cost;
};

Edge e[nmax][nmax];//稀疏矩阵
int dst[nmax];//到达每一个点的路径长度
int spend[nmax];//到达每一个点的花费
int book[nmax];//是否已经访问结束
int stNode; //起始点
int enNode; //终点

void DijkstraTestCase()
{
	while (cin >> n >> m && n != 0 && m != 0)
	{
		int a, b, i, j;

		for (i = 1; i <= n; ++i)
		{
			for (j = 1; j <= n; ++j)
			{
				e[i][j].cost = inf;
				e[i][j].len = inf;
			}
			e[i][i].len = 0;
		}

		while (m--)
		{
			cin >> a >> b;
			cin >> e[a][b].len >> e[a][b].cost;
			//如果是双向边的话，需要添加相反的b,a的值。
			e[b][a].len = e[a][b].len;
			e[b][a].cost = e[a][b].len;
		}
		cin >> stNode >> enNode;
		//将临近初始点的值加进去
		for (i = 1; i <= n; ++i)
		{
			dst[i] = e[stNode][i].len;
			spend[i] = e[stNode][i].cost;
		}
		int k;
		//遍历n-1次，因为初始节点不用遍历
		for (k = 1; k < n; ++k)
		{
			//首先第一步，找到对应的最小值，这里可以用优先队列（堆）来进行优化。
			int minNode, min = inf;
			for (i = 1; i <= n; ++i)
			{
				//这里增加条件，如果节点i还没有被访问，同时小于min
				//如果与min相同，那么比min的cost小也可以。
				if ((book[i] == 0 && min > dst[i]) || (book[i] == 0 && min == dst[i] && e[stNode][min].cost > e[stNode][i].cost))
				{
					min = dst[i];
					minNode = i;
				}
			}

			book[minNode] = 1;//当前节点被访问
			//以minNode为中心，作为转折点来更新数组
			for (i = 1; i <= n; ++i)
			{
				//如果当前中转节点没有被访问过，那么更新当前值
				if ((book[i] == 0 && dst[i] > dst[minNode] + e[minNode][i].len)
					|| (book[i] == 0 && dst[i] == dst[minNode] + e[minNode][i].len &&
						spend[i] > spend[minNode] + e[minNode][i].cost))
				{
					dst[i] = dst[minNode] + e[minNode][i].len;
					spend[i] = spend[minNode] + e[minNode][i].cost;
				}
			}

			cout << dst[enNode] << " " << spend[enNode] << endl;
		}
	}
}



/*
SPFA(shortest path faster algorithm)
定义：是求单源最短路径的一种算法，是Bellman-ford算法的队列优化。

用途：很多时候给定的图当中存在负权边，此时Dijkstra这种算法就失去
了作用。

算法思想：建立一个队列，初始队列当中仅仅有一个起始点，在建立表格
记录起始点到所有点的最短路径。(该表格的初始值要赋为极大值)然后进
行松弛操作，用队列当中的点去刷新起始点到所有点的最短路径。如果刷
新成功而且当前点不在队列，那么将当前点加入到队列最后。重复执行，
直到队列为空。

算法效果：O(kE) k为每个点的平均进队列次数。在稀疏图当中k<2。但是
算法的稳定性较差，在稠密图当中算法会退化。
*/

vector<vector<pair<int,int>>> graph;


void SPFATestCase()
{
	while (cin >> n >> m && m != 0&& n!=0)
	{
		int a, b, cost, i, j;

		graph.resize(n + 1);

		for (int i = 0; i < m; ++i)
		{
			//单向边
			cin >> a >> b >> cost;//从a点到b点的距离是cost
			graph[a].push_back(make_pair(b, cost));
		}
		cout << " the input graph: " << endl;
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 0; j < graph[i].size(); ++j)
			{
				cout << graph[i][j].first << " ";
			}
			cout << endl;
		}

		int start, end;
		cout << "input the origin :" << endl;
		cin >> start;
		queue<int> q;
		
		//将dst全部更新为inf
		for (int i = 0; i <= n; ++i)
		{
			dst[i] = inf;
		}
		dst[start] = 0;
		q.push(start);
		book[start] = 1;
		while (!q.empty())
		{
			int cur = q.front();
			q.pop();
			book[cur] = 0;
			//遍历当前节点cur的所有临近节点
			for (int i = 0; i < graph[cur].size(); ++i)
			{
				int v = graph[cur][i].first;//得到与cur相连的另一个点
				if (dst[v] > dst[cur] + graph[cur][i].second)
				{
					dst[v] = dst[cur] + graph[cur][i].second;
					if (book[v] == 0)//如果当前节点不在队列q当中，那么直接加入到q中。
					{
						q.push(v);
						book[v] = 1;
					}
				}
				
			}
		}

		//经过操作之后,输出单源最短路径的结果
		cout << " The result: ";
		for (int i = 1; i <= n; ++i)
		{
			cout << dst[i] << " ";
		}cout << endl;


	}


}