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
	//��ǰ·������С·������ôֱ�ӷ���
	if (minPath < dst)
	{
		return;
	}
	//�����ǰ·����targetһ���Ļ�����ô������
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
		//�����û��ݵķ��������ҵ���Ӧ�ķ���
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
	//n����ڵ������m����ߵĸ���
	while (cin >> n >> m && n != 0)
	{
		//���ݽڵ㽨ͼ
		int i, j;
		for (i = 1; i <= n; ++i)
		{
			for (j = 1; j <= n; ++j)
			{
				edge[i][j] = inf;
			}
			edge[i][i] = 0;
		}
		//����ͼ�������Ӧ�ı�Ȩֵ
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
Floyd�㷨��һ�־���Ķ�̬�滮�㷨��
��Ҫ˼�룺�����ⶥ��u�����ⶥ��v�����·��һ�������ֿ��ܣ�1.ֱ�Ӵ�u��v��
2.��u�������ɶ���k����v�����ԣ����Ǽ���dist(u,v)Ϊ����u������v�����·
�����롣�������Ǽ��dist(u,k)+dist(k,v)<dist(u,v)�Ƿ���������������
��ô�͸���dist(u,v)�������Ǳ��������е�ֵ��dist(u,v)���Ǵ�u��v����̾ࡣ

�㷨���̣�
1.��ʼ������������֮��ľ��붼�Ǳߵ�Ȩ���������֮��û
�б���������ôȨֵΪ�����
2.������ڽڵ�u��v������һ������wʹ�ô�u��v����֪��·�����̣���ô��������

�㷨Ч����
Floyd�㷨��ʱ�临�Ӷ���O(n^3),�ռ临�Ӷ���O(n^2)�����Ի���κζ����֮��
�����·����

Ӧ�ã�
Floyd�㷨���ڽӾ�����ڽӱ�������ͼ������ʽ�¶�����ʹ�á����ڽ����Դ���
·�����⡣

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
			//�Ƿ�Ϊ����ͼ
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
Dijkstra�㷨
���壺���͵ĵ�Դ���·���㷨�����ڼ���ĳ�����㵽�������ж�������·����
Ҫ��ͼ�в����ڸ�ֵ��

˼�룺��ԭ�������ÿ��ѡ����ԭ�������һ������ǰ����Ȼ���Ըö���Ϊ����
������չ��

�㷨���̣�
1.��֪���·�̵Ķ��㼯��P��δ֪���·���Ķ��㼸��Q��ʹ��book����¼��Щ
���ڼ���P���С�
2.��Q����ѡ��һ����ԭ������Ķ���u��dist��С�����뵽P���У����ҿ�������
�Ե�uΪ���ıߣ���ÿһ���߽����ɳڲ�����
4.�ظ�3�����QΪ�գ���ô�㷨������dist�����ֵ����Դ�㵽���ж������С
·����

�㷨Ч����
���ʹ����С�ѽ���ά������2�����õ������㷨��ʱ�临�Ӷ�ΪO��nlogn��

ʾ�����⣺����n���㣬m���ߣ�ÿ���߶��г���d�ͻ���p���������s���յ�t��
Ҫ�������㵽�յ����̾����Լ����ѣ�������·���ж���·�ߣ���ô����
���������ٵġ�
*/

struct Edge
{
	int len;
	int cost;
};

Edge e[nmax][nmax];//ϡ�����
int dst[nmax];//����ÿһ�����·������
int spend[nmax];//����ÿһ����Ļ���
int book[nmax];//�Ƿ��Ѿ����ʽ���
int stNode; //��ʼ��
int enNode; //�յ�

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
			//�����˫��ߵĻ�����Ҫ����෴��b,a��ֵ��
			e[b][a].len = e[a][b].len;
			e[b][a].cost = e[a][b].len;
		}
		cin >> stNode >> enNode;
		//���ٽ���ʼ���ֵ�ӽ�ȥ
		for (i = 1; i <= n; ++i)
		{
			dst[i] = e[stNode][i].len;
			spend[i] = e[stNode][i].cost;
		}
		int k;
		//����n-1�Σ���Ϊ��ʼ�ڵ㲻�ñ���
		for (k = 1; k < n; ++k)
		{
			//���ȵ�һ�����ҵ���Ӧ����Сֵ��������������ȶ��У��ѣ��������Ż���
			int minNode, min = inf;
			for (i = 1; i <= n; ++i)
			{
				//������������������ڵ�i��û�б����ʣ�ͬʱС��min
				//�����min��ͬ����ô��min��costСҲ���ԡ�
				if ((book[i] == 0 && min > dst[i]) || (book[i] == 0 && min == dst[i] && e[stNode][min].cost > e[stNode][i].cost))
				{
					min = dst[i];
					minNode = i;
				}
			}

			book[minNode] = 1;//��ǰ�ڵ㱻����
			//��minNodeΪ���ģ���Ϊת�۵�����������
			for (i = 1; i <= n; ++i)
			{
				//�����ǰ��ת�ڵ�û�б����ʹ�����ô���µ�ǰֵ
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
���壺����Դ���·����һ���㷨����Bellman-ford�㷨�Ķ����Ż���

��;���ܶ�ʱ�������ͼ���д��ڸ�Ȩ�ߣ���ʱDijkstra�����㷨��ʧȥ
�����á�

�㷨˼�룺����һ�����У���ʼ���е��н�����һ����ʼ�㣬�ڽ������
��¼��ʼ�㵽���е�����·����(�ñ��ĳ�ʼֵҪ��Ϊ����ֵ)Ȼ���
���ɳڲ������ö��е��еĵ�ȥˢ����ʼ�㵽���е�����·�������ˢ
�³ɹ����ҵ�ǰ�㲻�ڶ��У���ô����ǰ����뵽��������ظ�ִ�У�
ֱ������Ϊ�ա�

�㷨Ч����O(kE) kΪÿ�����ƽ�������д�������ϡ��ͼ����k<2������
�㷨���ȶ��Խϲ�ڳ���ͼ�����㷨���˻���
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
			//�����
			cin >> a >> b >> cost;//��a�㵽b��ľ�����cost
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
		
		//��dstȫ������Ϊinf
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
			//������ǰ�ڵ�cur�������ٽ��ڵ�
			for (int i = 0; i < graph[cur].size(); ++i)
			{
				int v = graph[cur][i].first;//�õ���cur��������һ����
				if (dst[v] > dst[cur] + graph[cur][i].second)
				{
					dst[v] = dst[cur] + graph[cur][i].second;
					if (book[v] == 0)//�����ǰ�ڵ㲻�ڶ���q���У���ôֱ�Ӽ��뵽q�С�
					{
						q.push(v);
						book[v] = 1;
					}
				}
				
			}
		}

		//��������֮��,�����Դ���·���Ľ��
		cout << " The result: ";
		for (int i = 1; i <= n; ++i)
		{
			cout << dst[i] << " ";
		}cout << endl;


	}


}