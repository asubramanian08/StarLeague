// Square Overlap Gold.cpp : Sweep line + set
// Osman Ay. Dec 2010, Aydin.

#include "pch.h"
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream cin("1.in");
ofstream cout("1.out");

int N, K;
struct VSide //vetical side of a square
{
	bool friend operator < (const VSide &side1, const VSide &side2)
	{
		return side1.y1 < side2.y1;
	}
	int x, y1, y2;
	bool isLeft;
};

bool cmpX(const VSide &side1, const VSide &side2)
{
	return side1.x < side2.x;
}

vector<VSide> sideVec;
//------------------------------------------------------
void readInput()
{
	cin >> N >> K;

	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;

		VSide side;
		side.x = x - K / 2;
		side.y1 = y - K / 2;
		side.y2 = y + K / 2;
		side.isLeft = true;

		sideVec.push_back(side);

		side.x = x + K / 2;
		side.isLeft = false;
		sideVec.push_back(side);
	}
}
//------------------------------------------------------
int go()
{
	int res = 0, count = 0;
	set<VSide> s;
	sort(sideVec.begin(), sideVec.end(), cmpX);

	for (int i = 0; i < sideVec.size() && count < 2; i++)
	{
		VSide curSide = sideVec[i];
		if (curSide.isLeft)
		{
			s.insert(curSide);
			continue;
		}

		//CurSide is a right side of a square.
		//Test if it overlap any of the active sides (sides in the set)
		auto it = s.lower_bound(curSide); //it points to the left side of the same square
		
		//check upper square
		auto nextIt = next(it);
		if (nextIt != s.end() && curSide.x > nextIt->x &&  nextIt->y1 < curSide.y2)
		{
			res = (curSide.x - nextIt->x)*(curSide.y2 - nextIt->y1);
			count++;
		}

		//check lower square
		auto prevIt = prev(it);
		if (prevIt != s.end() && curSide.x > prevIt->x && prevIt->y2 > curSide.y1)
		{
			res = (curSide.x - prevIt->x)*(prevIt->y2 - curSide.y1);
			count++;
		}
	
		s.erase(curSide);
	}

	return (count <= 1 ? res : -1);
}
//------------------------------------------------------
int main()
{
    readInput(); 
	cout <<go()<<endl;
}


