// Milk Visits Usaco 2109 Dec Gold.cpp : Tarjan's offline LCA
//

#include "pch.h"
#include <fstream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>

using namespace std;

ifstream cin("5.in");
ofstream cout("1.out");

int N, M;
vector<int> types;
vector<vector<int>> adjList;

struct Query
{
	int v, type, index;
};

vector<vector<Query>> queries;
vector<bool> visited;
vector<bool> result;
vector<map<int, int>> nodeTypes;


//********************************************
//DSU

vector<int> parents;

void createSet(int n)
{
	parents.resize(n);
	iota(parents.begin(), parents.end(), 0);
}

int findSet(int a)
{
	if (parents[a] == a)
		return a;
	return parents[a] = findSet(parents[a]);
}

void unionSets(int a, int b)
{
	a = findSet(a);
	b = findSet(b);
	parents[b] = parents[a];
}
//END DSU
//********************************************
void readInput()
{
	cin >> N >> M;
	types.resize(N);
	for (int i = 0; i < N; i++)
		cin >> types[i];
	adjList.resize(N);
	for (int i = 0; i < N - 1; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; v--;
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}

	queries.resize(N);
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		queries[a].push_back({ b, c, i });
		queries[b].push_back({ a, c, i });
	}
}//--------------------------------------------
void dfs(int u)
{
	visited[u] = true;
	parents[u] = u;
	for (int v: adjList[u]) {
		if (!visited[v]) 
		{
			dfs(v);
			unionSets(u, v);
			parents[findSet(u)] = u;
		}
	}

	for (auto x : queries[u]) 
	{
		if (visited[x.v])
		{
			int lca = parents[findSet(x.v)];

			int temp1 = nodeTypes[u][x.type] - nodeTypes[lca][x.type];
			int temp2 = nodeTypes[x.v][x.type] - nodeTypes[lca][x.type];
			int res = temp1 + temp2 + (types[lca] == x.type ? 1 : 0);
			
			result[x.index] = result[x.index] || res;
		}
	}
}
//--------------------------------------------
void go() 
{
	result.resize(M);
	parents.resize(N);
	visited.assign(N, 0);
	createSet(N);
	dfs(0);
}
//--------------------------------------------
//Calculate the types of each node together with its all ancessors.
void dfs1(int u)
{
	visited[u] = true;
	nodeTypes[u][types[u]]++;
	for (int v : adjList[u])
	{
		if (visited[v])
			continue;
		nodeTypes[v] = nodeTypes[u];
		dfs1(v);
	}
}
//--------------------------------------------
int main()
{
    readInput(); 
	visited.resize(N, false);
	nodeTypes.resize(N);

	dfs1(0);
	go();
	for (int x : result)
		cout << x;
}
