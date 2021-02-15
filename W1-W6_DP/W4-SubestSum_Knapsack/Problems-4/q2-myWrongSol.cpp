#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int numCows;
int *cows;
bool *inSub;
vector<int> sums[2];
int subset(int depth, int sum, int sumLen1, int sumLen2, bool sumTo)
{
    int sumLen[2];
    sumLen[0] = sumLen1;
    sumLen[1] = sumLen2;
    if (depth == numCows)
    {
        if (sum % 2 != 0)
            return 0;
        sums[1].resize(sumLen[1]);
        sort(sums[1].begin(), sums[1].end());
        sums[0].resize(sumLen[0]);
        sort(sums[0].begin(), sums[0].end());
        int b = sumLen[1] - 1;
        for (int a = 0; a < sumLen[0]; a++)
        {
            while ((b > 0) && (sums[0][a] + sums[1][b] > sum / 2))
                b--;
            if (sums[0][a] + sums[1][b] == sum / 2)
            {
                /*for (int i = 0; i < numCows; i++)
                    cout << inSub[i] << ' ';
                cout << endl;*/
                return true;
            }
        }
        return false;
    }
    inSub[depth] = false;
    sums[sumTo].resize(sumLen[sumTo]);
    vector<int> temp1 = sums[sumTo];
    vector<int> temp2 = sums[!sumTo];
    int ans = subset(depth + 1, sum, sumLen[0], sumLen[1], sumTo);
    sums[sumTo] = temp1;
    sums[!sumTo] = temp2;
    for (int i = 0; i < sumLen[sumTo]; i++)
        sums[sumTo].push_back(sums[sumTo][i] + cows[depth]);
    sumLen[sumTo] *= 2;
    inSub[depth] = true;
    sort(sums[sumTo].begin(), sums[sumTo].end());
    sums[sumTo].resize(unique(sums[sumTo].begin(), sums[sumTo].end()) - sums[sumTo].begin());
    sumLen[sumTo] = sums[sumTo].size();
    ans += subset(depth + 1, sum + cows[depth], sumLen[0], sumLen[1], !sumTo);
    return ans;
}
int main(void)
{
    // FILE *junk;
    // junk = freopen("subsets.in", "r", stdin);
    // junk = freopen("subsets.out", "w", stdout);
    cin >> numCows;
    cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];
    inSub = new bool[numCows];
    sums[0].push_back(0);
    sums[1].push_back(0);
    int ans = subset(0, 0, 1, 1, true) - 1;
    cout << ans;
    return 0;
}