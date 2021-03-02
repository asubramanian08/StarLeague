#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<int, int> pii;
#define NA -1
#define BIG_NUM 1000000000
vector<pii> *conns;
int *level;
int **parent_tbl;
int **min_tbl;
int sqrtCalc;
void parentLevels(int node, int parent, int wt)
{
    if (parent != NA)
        level[node] = level[parent] + 1;
    else
        level[node] = 0;

    //set parent table
    parent_tbl[node][0] = parent;
    for (int i = 1; (i <= sqrtCalc) && (parent_tbl[node][i - 1] != NA); i++)
        parent_tbl[node][i] = parent_tbl[parent_tbl[node][i - 1]][i - 1];

    //set min table
    min_tbl[node][0] = wt;
    for (int i = 1; (i <= sqrtCalc) && (parent_tbl[node][i - 1] != NA); i++)
        min_tbl[node][i] = min(min_tbl[node][i - 1], min_tbl[parent_tbl[node][i - 1]][i - 1]);

    //call children
    for (int i = 0; i < conns[node].size(); i++)
        if (conns[node][i].first != parent)
            parentLevels(conns[node][i].first, node, conns[node][i].second);
}

int main(void)
{
    /*FILE *junk;
    junk = freopen("mootube.in", "r", stdin);
    junk = freopen("mootube.out", "w", stdout);*/
    int vids, queries;
    cin >> vids >> queries;
    conns = new vector<pii>[vids];
    int v1, v2, wt;
    for (int i = 1; i < vids; i++)
    {
        cin >> v1 >> v2 >> wt;
        v1--;
        v2--;
        conns[v1].push_back(make_pair(v2, wt));
        conns[v2].push_back(make_pair(v1, wt));
    }

    //set up and go - for the LCA
    level = new int[vids];
    sqrtCalc = sqrt(vids);
    parent_tbl = new int *[vids];
    for (int i = 0; i < vids; i++)
    {
        parent_tbl[i] = new int[sqrtCalc];
    }
    parentLevels(0, NA, NA);

    //answer queries
    int n1, n2, min1, min2, temp, levUp;
    for (int i = 0; i < queries; i++)
    {
        //start vars
        cin >> n1 >> n2;
        n1--;
        n2--;
        min1 = min2 = BIG_NUM;

        //fix level
        if (level[n1] < level[n2])
        {
            temp = n1;
            n1 = n2;
            n2 = temp;
        }
        for (int i = sqrtCalc; i >= 0; i--)
            if (level[n1] - (1 << i) >= level[n2])
            {
                min1 = min(min1, min_tbl[n1][i]);
                n1 = parent_tbl[n1][i];
            }

        levUp = n1 != n2;
        while (levUp != 0)
        {
            for (levUp = sqrtCalc; (levUp >= 0) && (parent_tbl[n1][levUp] != parent_tbl[n2][levUp]); levUp++)
                ;
            levUp--;
            min1 = min(min1, min_tbl[n1][levUp]);
            min2 = min(min2, min_tbl[n2][levUp]);
            n1 = parent_tbl[n1][levUp];
            n2 = parent_tbl[n2][levUp];
        }

        cout << min(min1, min2) << '\n';
    }

    return 0;
}