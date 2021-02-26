#include <iostream>
using namespace std;
//do Kadence Algo
#define BARN_SIDE 201
int main(void)
{
    /*FILE *junk;
    junk = freopen("paintbarn.in", "r", stdin);
    junk = freopen("paintbarn.out", "w", stdout);*/

    //set the side
    int wall[BARN_SIDE][BARN_SIDE];
    for (int i = 0; i < BARN_SIDE; i++)
        for (int j = 0; j < BARN_SIDE; j++)
            wall[i][j] = 0;

    //read input
    int rects, bestVal;
    cin >> rects >> bestVal;
    int p1x, p1y, p2x, p2y;
    for (int i = 0; i < rects; i++)
    {
        cin >> p1x >> p1y >> p2x >> p2y;
        // x x x x x x x
        // x + o o o - x
        // x o o o o o x
        // x - o o o + x
        // x x x x x x x
        wall[p1x][p2y]++; //top left
        wall[p2x][p2y]--; //top right
        wall[p1x][p1y]--; //bottem left
        wall[p2x][p1y]++; //bottem right
    }

    //add values for the sides
    for (int i = 1; i < BARN_SIDE; i++)
    {
        wall[0][i] += wall[0][i - 1];
        wall[i][0] += wall[i - 1][0];
    }
    for (int i = 1; i < BARN_SIDE; i++)
        for (int j = 1; j < BARN_SIDE; j++)
            wall[i][j] += wall[i - 1][j] + wall[i][j - 1] - wall[i - 1][j - 1];

    //compute the prefix sum
    int pre_sum[BARN_SIDE][BARN_SIDE];
    pre_sum[0][0] = 0;
    for (int i = 1; i < BARN_SIDE; i++)
    {
        pre_sum[0][i] = pre_sum[0][i - 1] + (pre_sum[0][i] == bestVal - 1) - (pre_sum[0][i] == bestVal);
        pre_sum[i][0] = pre_sum[i - 1][0] + (pre_sum[i][0] == bestVal - 1) - (pre_sum[i][0] == bestVal);
    }
    for (int i = 1; i < BARN_SIDE; i++)
        for (int j = 1; j < BARN_SIDE; j++)
            pre_sum[i][j] = pre_sum[i - 1][j] + pre_sum[i][j - 1] - pre_sum[i - 1][j - 1] +
                            ((pre_sum[i][j] == bestVal - 1) - (pre_sum[i][j] == bestVal));
    return 0;
}