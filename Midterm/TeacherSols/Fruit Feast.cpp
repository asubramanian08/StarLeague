// Fruit Feast.cpp : Usaco 2015 Dec Gold
// Osman Ay. Nov 2019, Aydin.

#include "pch.h"
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream cin("1.in");
ofstream cout("1.out");

int T, A, B, res = 0;
queue<int> q;
//--------------------------------
void bfs(vector<bool> &found)
{
	while (!q.empty())
	{
		int x = q.front();
		q.pop();

		if (x == T)
		{
			return;
		}

		int y = x + A;
		if (y <= T && !found[y])
		{
			found[y] = true;
			res = max(res, y);
			q.push(y);
		}

		y = x + B;
		if (y <= T && !found[y])
		{
			found[y] = true;
			res = max(res, y);
			q.push(y);
		}
	}
}
//--------------------------------
void go()
{
	vector<bool> found(T + 1, false);

	q.push(0);
	found[0] = true;

	bfs(found);

	for (int i = 0; i <= T; i++)
	{
		if (!found[i])
			continue;
		int start = i / 2;
		if (found[start])
			continue;

		q.push(start);

		vector<bool> found2 = found;
		found2[start] = true;

		bfs(found2);
	}
}
//--------------------------------
int main()
{
	cin >> T >> A >> B;
	go();
	cout << res << endl;
}

