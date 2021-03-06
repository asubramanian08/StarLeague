//A pie for a pie. Reverse BFS
//Osman Ay. Oct 2019, Aydin

#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <fstream>

#define INF 1000000010

using namespace std;

int main() 
{
	ifstream cin("piepie.in");
	ofstream cout("piepie.out");

	//input
	int n, d; cin >> n >> d;
	vector<int> X(2 * n), Y(2 * n), dist(2*n);

	for (int i = 0; i < 2 * n; i++)
		cin >> X[i] >> Y[i];

	//processing
	queue<int> q; //indices
	set<pair<int,int>> bes, elsie;

	for (int i = 0; i < 2 * n; i++)
	{
		if (i >= n) //Elsie's pies
		{
			if (X[i] == 0)
			{
				dist[i] = 1;
				q.push(i);
			}
			else
			{
				dist[i] = INF;
				elsie.insert({ X[i], i });
			}
		}
		else //Bessie's pies
		{
			if (Y[i] == 0) 
			{
				dist[i] = 1;
				q.push(i);
			}
			else 
			{
				dist[i] = INF;
				bes.insert({ Y[i], i });
			}
		}
	}

	while (!q.empty()) 
	{
		int next = q.front(); 
		q.pop();
		if (next >= n) //Elsie
		{
			auto it = bes.lower_bound({ Y[next] - d, -1 });

			while (it != bes.end() && Y[it->second] <= Y[next]) 
			{
				dist[it->second] = dist[next] + 1;
				q.push(it->second);
				it = bes.erase(it); //erase and point to the next element.
			}
		}
		else //Bessie
		{
			auto it = elsie.lower_bound({ X[next] - d, -1 });
			while (it != elsie.end() && X[it->second] <= X[next]) 
			{
				dist[it->second] = dist[next] + 1;
				q.push(it->second);
				it = elsie.erase(it);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (dist[i] == INF) 
			cout << "-1" << endl;
		else 
			cout << dist[i] << endl;
	}

	return 0;
}