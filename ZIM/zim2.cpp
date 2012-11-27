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
typedef pair<int,lli> para;
vector<para> G[500000];
int deg[500000];

lli bestboth[500000];
lli beststart[500000];
lli bestend[500000];
lli bestall[500000];
lli both[500000];

lli niepa(lli v) {
    if (v % 2 == 0) v++;
    return v;
}
lli parz(lli v) {
    if (v % 2 == 1) v++;
    return v;
}

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
                if (deg[it->first] == 1) {
                    q.push(it->first);
                }
            }
        }
//        printf("PAR %d\n", parent+1);
        
        lli suma = 0;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                both[it->first] = bestboth[it->first] + parz(it->second);
                suma += both[it->first];
            }
        }
        
        lli startbenefit = 0, startbenefit2 = 0;
        int startbenefitidx = -1;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = both[it->first] - (beststart[it->first] + niepa(it->second));
                if (startbenefit <= benefit) {
                    startbenefit2 = startbenefit;
                    startbenefit = benefit;
                    startbenefitidx = it->first;
                } else if (startbenefit2 <= benefit) {
                    startbenefit2 = benefit;
                }
            }
        }
        
        lli endbenefit = 0, endbenefit2 = 0;
        int endbenefitidx = -1;
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = both[it->first] - (bestend[it->first] + niepa(it->second));
                if (endbenefit <= benefit) {
                    endbenefit2 = endbenefit;
                    endbenefit = benefit;
                    endbenefitidx = it->first;
                } else if (endbenefit2 <= benefit) {
                    endbenefit2 = benefit;
                }
            }
        }
        
        lli allbenefit = max(endbenefit, startbenefit);
        FOREACH(it, G[v]) {
            if (it->first != parent) {
                lli benefit = both[it->first] - (bestall[it->first] + parz(it->second));
                allbenefit = max(allbenefit, benefit);
            }
        }
        if (endbenefitidx != startbenefitidx) {
            allbenefit = max(allbenefit, endbenefit + startbenefit);
        } else {
            allbenefit = max(allbenefit, max(endbenefit + startbenefit2, startbenefit + endbenefit2));
        }
//        printf(" - sum %lld\n", suma);
//        printf(" - startbenefit %lld endbenefit %lld\n", startbenefit, endbenefit);
//        printf(" - startidx %d endind %d\n", startbenefitidx, endbenefitidx);
//        printf(" - benef2 start %lld end %lld\n", startbenefit2, endbenefit2);
        bestboth[v] = suma;
        beststart[v] = suma - startbenefit;
        bestend[v] = suma - endbenefit;
        bestall[v] = suma - allbenefit;
        
//        printf("[%d] - end %lld start %lld both %lld all %lld\n", v+1, bestend[v], beststart[v], bestboth[v], bestall[v]);
        deg[v] = 0;
    }
    printf("%lld\n", bestall[v]);
    return 0;
}
