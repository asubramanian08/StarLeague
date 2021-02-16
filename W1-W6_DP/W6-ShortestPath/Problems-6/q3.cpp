#include <iostream>
#include <vector>
using namespace std;

#define BIG_NUM 1000000
struct pie
{
    int bVal;
    int eVal;
    int orgLoc;
};

int bCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->bVal - ((pie *)p2)->bVal;
}
int eCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->eVal - ((pie *)p2)->eVal;
}
int orgCompare(const void *p1, const void *p2)
{
    return ((pie *)p1)->orgLoc - ((pie *)p2)->orgLoc;
}

//initialization
pie *bPies;
pie *ePies;
vector<int> *bConns;
vector<int> *eConns;
int *bCost;
int *eCost;
void findB_Cost(int node, int parent);
void findE_Cost(int node, int parent);

void findB_Cost(int node, int parent)
{
    if (bCost[node] != BIG_NUM)
        return;
    for (int i = 0; i < bConns[node].size(); i++)
        if (bConns[node][i] != parent)
            findB_Cost(bConns[node][i], node);

    if (bPies[node].eVal == 0)
    {
        bCost[node] = 1;
        return;
    }
    bCost
}
void findE_Cost(int node, int parent)
{
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("piepie.in", "r", stdin);
    junk = freopen("piepie.out", "w", stdout);*/
    //get pies
    int numPies, range;
    cin >> numPies >> range;
    bPies = new pie[numPies];
    for (int i = 0; i < numPies; i++)
    {
        cin >> bPies[i].bVal;
        cin >> bPies[i].eVal;
        bPies[i].orgLoc = i;
    }
    qsort(bPies, numPies, sizeof(pie), bCompare);
    ePies = new pie[numPies];
    for (int i = 0; i < numPies; i++)
    {
        cin >> ePies[i].bVal;
        cin >> ePies[i].eVal;
        ePies[i].orgLoc = i;
    }
    qsort(ePies, numPies, sizeof(pie), eCompare);

    //find graph
    bConns = new vector<int>[numPies];
    for (int i = 0; i < numPies; i++)
    {
        int low = 0;
        int high = numPies;
        int goal = bPies[i].eVal - range;
        while (high - low > 1)
        {
            if (ePies[(high + low) / 2].eVal < goal)
                low = (high + low) / 2;
            else
                high = (high + low) / 2;
        }
        for (int j = high; (j < numPies) && (j < bPies[i].eVal + range); j++)
            bConns[i].push_back(ePies[j].orgLoc);
    }
    eConns = new vector<int>[numPies];
    for (int i = 0; i < numPies; i++)
    {
        int low = 0;
        int high = numPies;
        int goal = ePies[i].bVal - range;
        while (high - low > 1)
        {
            if (bPies[(high + low) / 2].bVal < goal)
                low = (high + low) / 2;
            else
                high = (high + low) / 2;
        }
        for (int j = high; (j < numPies) && (j < ePies[i].bVal + range); j++)
            bConns[i].push_back(bPies[j].orgLoc);
    }
    qsort(bPies, numPies, sizeof(pie), orgCompare);
    qsort(ePies, numPies, sizeof(pie), orgCompare);

    bCost = new int[numPies];
    eCost = new int[numPies];
    return 0;
}