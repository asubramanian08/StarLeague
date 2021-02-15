#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> point;
#define MAX_SIDE 21
#define NP -1
struct instra
{
    int cost;
    point regular;
    point flipped;
};

int main(void)
{
    /*FILE *junk;
    junk = freopen("cownav.in", "r", stdin);
    junk = freopen("cownav.out", "w", stdout);*/

    int sideLen;
    cin >> sideLen;
    bool **grid = new bool *[sideLen];
    char ch;
    for (int i = 0; i < sideLen; i++)
    {
        grid[i] = new bool[sideLen];
        for (int j = 0; j < sideLen; j++)
        {
            cin >> ch;
            grid[i][j] = ch == 'H';
        }
    }

    int DP[MAX_SIDE][MAX_SIDE][MAX_SIDE][MAX_SIDE];
    for (int i = 0; i < MAX_SIDE; i++)
        for (int j = 0; j < MAX_SIDE; j++)
            for (int k = 0; k < MAX_SIDE; k++)
                for (int l = 0; l < MAX_SIDE; l++)
                    DP[i][j][k][l] = NP;

    //DP[0][0][0][0] = 0;
    priority_queue<instra> p_queue;
    p_queue.push({0, make_pair(0, 0), make_pair(0, 0)});
    instra val;
    while (DP[sideLen - 1][sideLen - 1][sideLen - 1][sideLen - 1] == NP)
    {
        val = p_queue.top();
        p_queue.pop();
    }

    return 0;
}