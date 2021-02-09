#include <iostream>
#include <vector>
using namespace std;

struct node
{
    vector<int> conns;
    bool state;
};
int *inArr;
int *outArr;
bool *toggle;
node *lights;
void calcNode(int pos, int parent)
{
    for (int i = 0; i < lights[pos].conns.size(); i++)
        if (lights[pos].conns[i] != parent)
            calcNode(lights[pos].conns[i], pos);
    int flip = 1;
    int stay = 0;
    bool flipLit = !lights[pos].state;
    for (int i = 0; i < lights[pos].conns.size(); i++)
        if (lights[pos].conns[i] != parent)
        {
            flip += outArr[lights[pos].conns[i]];
            if (toggle[lights[pos].conns[i]])
                flipLit = !flipLit;
            stay += inArr[lights[pos].conns[i]];
        }
    if (!flipLit)
    {
        inArr[pos] = stay;
        outArr[pos] = flip;
        toggle[pos] = false;
    }
    else
    {
        inArr[pos] = flip;
        outArr[pos] = stay;
        toggle[pos] = true;
    }
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("christmas.in", "r", stdin);
    junk = freopen("christmas.out", "w", stdout);*/
    int bulbs;
    cin >> bulbs;
    lights = new node[bulbs];
    for (int i = 0; i < bulbs; i++)
        cin >> lights[i].state;
    int n1, n2;
    for (int i = 1; i < bulbs; i++)
    {
        cin >> n1 >> n2;
        n1--;
        n2--;
        lights[n1].conns.push_back(n2);
        lights[n2].conns.push_back(n1);
    }

    inArr = new int[bulbs];
    outArr = new int[bulbs];
    toggle = new bool[bulbs];
    calcNode(0, -1);
    cout << inArr[0];
    return 0;
}