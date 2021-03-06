// Delivery Route.cpp : Solution with coordinate compression.
// Osman Ay, March 2021.

#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

ifstream cin("delivery.in");
ofstream cout("delivery.out");

const int BIGNUM = 1000000000;
int N, res, xSize, ySize;
vector<pair<int, int>> farms;
vector<vector<int>> grid;
vector<int> X, Y;           //real distance
vector<int> xVec, yVec;     //the input values
map<int, int> xMap, yMap;

struct QItem
{
    int x, y, preX, preY;
};
//--------------------------------------------
void readInput()
{
    cin >> N;
    farms.resize(N);
    for (auto& farm : farms)
    {
        cin >> farm.first >> farm.second;
        xVec.push_back(farm.first);
        yVec.push_back(farm.second);
    }
}
//--------------------------------------------
void initGrid()
{
    grid.resize(xSize, vector<int>(ySize, 0));

    for (auto farm : farms)
    {
        int x = xMap[farm.first];
        int y = yMap[farm.second];
        grid[x][y] = BIGNUM;
    }
}
//--------------------------------------------
//This function will be called twice: for x coordinates and for y  coordinates
int compressCoordinates(vector<int> &inputVec, vector<int> &distVec, map<int, int> &m)
{
    //sort and eliminate duplicates
    sort(inputVec.begin(), inputVec.end());
    inputVec.resize(unique(inputVec.begin(), inputVec.end()) - inputVec.begin());

    //border
    int pos = 0;
    distVec.push_back(1);   

    for (int i = 0; i < inputVec.size()-1; i++)
    {
        int x1 = inputVec[i], x2 = inputVec[i+1];

        pos++;
        distVec.push_back(1);   //accupied place
        m[x1] = pos;

        if (x2 - x1 > 1)
        {
            pos++;
            distVec.push_back(x2 - x1 - 1);
        }
    }

    //the last elements
    pos++;
    distVec.push_back(1);   
    m[inputVec.back()] = pos;
    
    //add border
    pos++;
    distVec.push_back(1); 

    return pos + 1;         
}
//--------------------------------------------
void createGrid()
{
    xSize = compressCoordinates(xVec, X, xMap);
    ySize = compressCoordinates(yVec, Y, yMap);
    initGrid();
}
//--------------------------------------------
bool valid(int x, int y)
{
    if (x < 0 || x >= xSize || y < 0 || y >= ySize)
        return false;
    return true;
}
// //--------------------------------------------
//bfs from the source farm to the target farm
int go(vector<vector<int>> grid, int source, int target)
{
    queue<QItem> q;    //current position on the grid and previous x and y

    //set the source pos to 1
    int x = farms[source].first, y = farms[source].second;
    x = xMap[x], y = yMap[y];
    grid[x][y] = 1;
    q.push({x, y, x, y});

    //set the target pos to 0.
    x = farms[target].first, y = farms[target].second;
    x = xMap[x], y = yMap[y];
    grid[x][y] = 0;

    while (!q.empty())
    {
        x = q.front().x;
        y = q.front().y;
        int preX = q.front().preX;
        int preY = q.front().preY;
        q.pop();

        //go upward, +y
        int xx = x;
        int yy = y + 1;
        if (valid(xx, yy) && grid[xx][yy] != BIGNUM)    //inside the grid and not a farm
        {
            if (yy == preY)
            {
                if (grid[xx][yy] == 0 || grid[x][y] + 1 < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + 1;
                    q.push({ xx, yy, preX, y });
                }
            }
            else
            {
                if (grid[xx][yy] == 0 || grid[x][y] + Y[y] < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + Y[y];
                    q.push({ xx, yy, preX, yy });
                }
            }
        }

        //go downward, -y
        xx = x;
        yy = y - 1;
        if (valid(xx, yy) && grid[xx][yy] != BIGNUM)
        {
            if (yy == preY)
            {
                if (grid[xx][yy] == 0 || grid[x][y] + 1 < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + 1;
                    q.push({ xx, yy, preX, y });
                }
            }
            else
            {
                if (grid[xx][yy] == 0 || grid[x][y] + Y[y] < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + Y[y];
                    q.push({ xx, yy, preX, y });
                }
            }
        }

        //go left, -x
        xx = x - 1;
        yy = y;
        if (valid(xx, yy) && grid[xx][yy] != BIGNUM)
        {
            if (xx == preX)
            {
                if (grid[xx][yy] == 0 || grid[x][y] + 1 < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + 1;
                    q.push({ xx, yy, x, preY });
                }
            }
            else
            {
                if (grid[xx][yy] == 0 || grid[x][y] + X[x] < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + X[x];
                    q.push({ xx, yy, x, preY });
                }
            }
        }

        //go right, +x
        xx = x + 1;
        yy = y;
        if (valid(xx, yy) && grid[xx][yy] != BIGNUM)
        {
            if (xx == preX)
            {
                if (grid[xx][yy] == 0 || grid[x][y] + 1 < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + 1;
                    q.push({ xx, yy, x, preY });
                }
            }
            else
            {
                if (grid[xx][yy] == 0 || grid[x][y] + X[x] < grid[xx][yy])
                {
                    grid[xx][yy] = grid[x][y] + X[x];
                    q.push({ xx, yy, x, preY });
                }
            }
        }

    }

    x = farms[target].first, y = farms[target].second;
    x = xMap[x], y = yMap[y];
    return grid[x][y] - 1;
}
//--------------------------------------------
int main()
{
    readInput();

    createGrid();

    int res = 0;

    for (int i = 0; i < N - 1; i++)
    {
        int temp = go(grid, i, i + 1);
        if (temp == -1)
        {
            cout << -1 << endl;
            return 0;
        }
        res += temp;
    }

    int temp = go(grid, N-1, 0);
    if (temp == -1)
        cout << -1 << endl;
    else
        cout << res + temp << endl;
}
