// Splitting the Field Usaco 2016 US Open Gold.cpp : Disjoint rectangles, sweep Line, STL set
//

#include "pch.h"
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream cin("1.in");
ofstream cout("1.out");

int N;
vector<pair<long long, long long>> points;	//first is x and second is y
long long initArea;
//-----------------------------------------------------------
void readInput()
{
	cin >> N;
	points.resize(N);
	for (int i = 0; i < N; i++)
		cin >> points[i].first >> points[i].second;
	cin.close();
}
//-----------------------------------------------------------
long long go()
{
	sort(points.begin(), points.end());
	multiset<int> setL, setR; //y coordinates
	for (auto p : points)
		setR.insert(p.second);
	
	long long recL, recR;
	long long res = initArea = (points[N - 1].first - points[0].first) * (*setR.rbegin() - *setR.begin());;

	for (int i=0; i<N-1; i++)
	{
		auto p = points[i];
		setL.insert(p.second);
		setR.erase(setR.lower_bound(p.second));

		while (i < N-1 && p.first == points[i + 1].first)
		{
			i++;
			p = points[i];
			setL.insert(p.second);
			setR.erase(setR.lower_bound(p.second));
		}

		recL = (p.first - points[0].first) * (*setL.rbegin() - *setL.begin());
		recR = 0;
		if (i + 1 < N)
			recR = (points[N - 1].first - points[i+1].first) * (*setR.rbegin() - *setR.begin());

		res = min(res, recL + recR);
	}

	return res;
}
//-----------------------------------------------------------
void swapCoordinates()
{
	for (auto &p : points)
		swap(p.first, p.second);
}
//-----------------------------------------------------------
int main()
{
	readInput();
	long long totalArea = go();
	swapCoordinates();
	totalArea = min(totalArea, go());
	cout << initArea - totalArea << endl;
	cout.close();
	return 0;
}

