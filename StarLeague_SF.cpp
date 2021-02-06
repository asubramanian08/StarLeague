#include <iostream>
using namespace std;

int main(void)
{
    FILE *junk;
    junk = freopen(".in", "r", stdin);
    junk = freopen(".out", "w", stdout);
    return 0;
}