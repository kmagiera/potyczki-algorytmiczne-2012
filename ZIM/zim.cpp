#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

typedef long long int lli;
typedef pair<int,int> para;
vector<para> G[500000];
int deg[500000];
lli bestend[500000];
lli bestall[500000];
lli beststart[500000];
lli bestsande[500000];

int main() {
    int n,a,b,d;
    scanf("%d", &n);
    REP(i,n-1) {
        scanf("%d%d%d", &a, &b, &d);
        G[a-1].PB(para(b-1, d));
        G[b-1].PB(para(a-1, d));
    }
    
    queue<int> q;
    REP(i,n) {
        deg[i] = G[i].size();
        if (deg[i] < 2) {
            q.push(i);
        }
    }
    
    int v;
    while (!q.empty()) {
        v = q.front(); q.pop();
        int parent = -1;
//        printf("V %d\n", v+1);
        
        FOREACH(it, G[v]) {
            if (deg[it->first] > 0) {
                deg[it->first]--;
                parent = it->first;
                if (deg[it->first] < 2) {
                    q.push(it->first);
                }
            }
        }
//        printf("PAR %d\n", parent+1);
        
        lli bsande = 0;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                bsande += bestsande[it->first] + it->second + (it->second%2);
            }
        }
        lli ebenefit = 0, ebenefit2 = 0;
        int ebenefitidx = -1;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = bestsande[it->first] - bestend[it->first] + ((it->second%2==0) ? -1 : 1);
                if (ebenefit == 0) {
                    ebenefit = benefit;
                    ebenefitidx = it->first;
                } else if (ebenefit <= benefit) {
                    ebenefit2 = ebenefit;
                    ebenefit = benefit;
                    ebenefitidx = it->first;
                }
            }
        }
        lli sbenefit = 0, sbenefit2 = 0;
        int sbenefitidx = -1;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = bestsande[it->first] - beststart[it->first] + ((it->second%2==0) ? -1 : 1);
                if (sbenefit == 0) {
                    sbenefit = benefit;
                    sbenefitidx = it->first;
                } else if (sbenefit <= benefit) {
                    sbenefit2 = sbenefit;
                    sbenefit = benefit;
                    sbenefitidx = it->first;
                }
            }
        }
        lli allbenefit = 0;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = bestsande[it->first] - bestall[it->first];
            }
        }

        lli ball = 0;
        if (sbenefitidx != ebenefitidx) {
            ball = sbenefit + ebenefit;
        } else {
            ball = max(sbenefit2 + ebenefit, ebenefit2 + sbenefit);
        }
        
        bestsande[v] = bsande;
        bestend[v] = min(bsande - ebenefit, bsande);
        beststart[v] = min(bsande - sbenefit, bsande);
        bestall[v] = min(min(bestsande[v], bestend[v]), min(beststart[v], bsande - ball));
        
//        printf("[%d] - bend %lld bst %lld s&e %lld all %lld\n", v+1, bestend[v], beststart[v], bestsande[v], bestall[v]);
        deg[v]--;
    }
    printf("%lld\n", min(min(bestend[v],beststart[v]), min(bestsande[v], bestall[v])));
    return 0;
}
