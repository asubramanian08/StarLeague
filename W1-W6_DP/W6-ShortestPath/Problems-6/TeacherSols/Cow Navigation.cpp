// Cow Navigation Usaco 2017 Jan Gold.cpp : BFS solution.
// Osman Ay. Sep 2019, Aydin

#include "pch.h"
#include <fstream>
#include <vector>
#include <String>
#include <queue>
#include <algorithm>

#define BIGNUM INT_MAX
#define SIZE 20 

using namespace std;

ifstream cin("7.in");
ofstream cout("1.out");

int N;
vector<vector<int>> grid;

//directions
vector<int> dx = { -1,0,1,0 }, dy = { 0,1,0,-1 };

struct QItem
{
	int x1, y1, d1, x2, y2, d2; //0:up, 1: left, 2:down, 3: right
};
//---------------------------------------
void readInput()
{
	cin >> N;
	grid.resize(N);
	for (int i = 0; i < N; i++)
	{
		grid[i].resize(N);
		for (int j = 0; j < N; j++)
		{
			char ch;
			cin >> ch;
			ch == 'E' ? grid[i][j] = 0 : grid[i][j] = 1;
		}
	}
}
//---------------------------------------
bool inBorder(int x, int y)
{
	return x >= 0 && x < N && y >= 0 && y < N;
}
//---------------------------------------
QItem goForward(QItem item)
{
	QItem newItem = item;

	//if target has not been reached
	if (item.x1 != 0 || item.y1 != N - 1)
	{
		newItem.x1 += dx[item.d1];
		newItem.y1 += dy[item.d1];
		if (!inBorder(newItem.x1, newItem.y1) || grid[newItem.x1][newItem.y1] == 1)
		{
			newItem.x1 = item.x1;
			newItem.y1 = item.y1;
		}
	}

	//if target has not been reached
	if (item.x2 != 0 || item.y2 != N - 1)
	{
		newItem.x2 += dx[item.d2];
		newItem.y2 += dy[item.d2];
		if (!inBorder(newItem.x2, newItem.y2) || grid[newItem.x2][newItem.y2] == 1)
		{
			newItem.x2 = item.x2;
			newItem.y2 = item.y2;
		}
	}
	return newItem;
}
//---------------------------------------
QItem turnLeft(QItem item)
{
	item.d1 = (item.d1 + 3) % 4;
	item.d2 = (item.d2 + 3) % 4;
	return item;
}
//---------------------------------------
QItem turnRight(QItem item)
{
	item.d1 = (item.d1 + 1) % 4;
	item.d2 = (item.d2 + 1) % 4;
	return item;
}
//--------------------------------------
int go()
{
	//0:up, 1:right, 2:down, 3:left
	int dp[SIZE][SIZE][4][SIZE][SIZE][4];
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			for (int k = 0; k < 4; k++)
				for (int l = 0; l < SIZE; l++)
					for (int m = 0; m < SIZE; m++)
						for (int n = 0; n < 4; n++)
							dp[i][j][k][l][m][n] = BIGNUM;

	dp[N - 1][0][0][N - 1][0][1] = 0; //Bessie may be facing up or right
	
	//start pos is [N-1][0], target pos is [0][N-1].

	QItem item = { N-1,0,0,N-1,0,1 }, newItem;
	queue<QItem> q;
	q.push(item);

	while (!q.empty())
	{
		item = q.front();
		q.pop();

		int x1 = item.x1, y1 = item.y1, d1 = item.d1, x2 = item.x2, y2 = item.y2, d2 = item.d2;

		if (x1 == 0 && y1 == N-1 && x2 == 0 && y2 == N-1)
			return dp[x1][y1][d1][x2][y2][d2];

		newItem = goForward(item);
		if (dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] == BIGNUM)
		{
			dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] = dp[x1][y1][d1][x2][y2][d2] + 1;
			q.push(newItem);
		}

		newItem = turnLeft(item);
		if (dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] == BIGNUM)
		{
			dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] = dp[x1][y1][d1][x2][y2][d2] + 1;
			q.push(newItem);
		}
		
		newItem = turnRight(item);
		if (dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] == BIGNUM)
		{
			dp[newItem.x1][newItem.y1][newItem.d1][newItem.x2][newItem.y2][newItem.d2] = dp[x1][y1][d1][x2][y2][d2] + 1;
			q.push(newItem);
		}
	}
	return -1; //Error
}
//---------------------------------------
int main()
{
    readInput(); 
	cout << go() << endl;
	return 0;
}

