#include <iostream>
#include <vector>
using namespace std;

#define NP -1
struct point
{
    int x, y, orig;
};
struct post
{
    int up, down, left, right;
};

int xCompare(const void *p1, const void *p2)
{
    int returnVal = ((point *)p1)->x - ((point *)p2)->x;
    if (returnVal == 0)
        returnVal = ((point *)p1)->y - ((point *)p2)->y;
    return returnVal;
}
int yCompare(const void *p1, const void *p2)
{
    int returnVal = ((point *)p1)->y - ((point *)p2)->y;
    if (returnVal == 0)
        returnVal = ((point *)p1)->x - ((point *)p2)->x;
    return returnVal;
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("lasers.in", "r", stdin);
    junk = freopen("lasers.out", "w", stdout);*/
    point start, end;
    int numPoles;
    cin >> numPoles >> start.x >> start.y >> end.x >> end.y;
    point *poles = new point[numPoles];
    for (int i = 0; i < numPoles; i++)
    {
        cin >> poles[i].x >> poles[i].y;
        poles[i].orig = i;
    }

    point *by_x = new point[numPoles];
    memcpy(by_x, poles, numPoles * sizeof(poles));
    qsort(by_x, numPoles, sizeof(poles), xCompare);
    point *by_y = new point[numPoles];
    memcpy(by_y, poles, numPoles * sizeof(poles));
    qsort(by_y, numPoles, sizeof(poles), yCompare);

    point *comesFrom = new point[numPoles];
    for (int i = 0; i < numPoles; i++)
    {
        comesFrom[by_x[i].orig].x = i;
        comesFrom[by_y[i].orig].y = i;
    }
    post *graph = new post[numPoles];
    for (int i = 0; i < numPoles; i++)
    {
        if (comesFrom[i].x + 1 != numPoles)
        {
            graph[i].up = by_x[comesFrom[i].x + 1].x;
            if (poles[graph[i].up].x != poles[i].x)
                graph[i].up = NP;
        }
        else
            graph[i].up = NP;

        if (comesFrom[i].x - 1 != -1)
        {
            graph[i].down = by_x[comesFrom[i].x - 1].x;
            if (poles[graph[i].down].x != poles[i].x)
                graph[i].up = NP;
        }
        else
            graph[i].up = NP;

        if (comesFrom[i].y - 1 != -1)
        {
            graph[i].left = by_y[comesFrom[i].y - 1].y;
            if (poles[graph[i].left].y != poles[i].y)
                graph[i].left = NP;
        }
        else
            graph[i].left = NP;

        if (comesFrom[i].y + 1 != numPoles)
        {
            graph[i].right = by_y[comesFrom[i].y + 1].y;
            if (poles[graph[i].right].y != poles[i].y)
                graph[i].right = NP;
        }
        else
            graph[i].right = NP;
    }

    for (int i = 0; i < numPoles; i++)
    {
    }
    return 0;
}