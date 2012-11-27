#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

typedef long long int lli;

lli best[1000000];
lli end[1000000];
int tab[1000000];

int main() {
    int n,k,a;
    scanf("%d%d", &n, &k);
    REP(i,k+1) best[i] = end[i] = 0;
    REP(i,n) {
        scanf("%d", &a);
        for (int j = k; j > 0; j--) {
            end[j] = max(end[j], best[j-1]) + a;
            best[j] = max(best[j], end[j]);
        }
    }
    printf("%lld\n", best[k]);
    return 0;
}