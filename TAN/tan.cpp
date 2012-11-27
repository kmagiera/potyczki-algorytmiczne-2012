#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <functional>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back
#define triple(a,b,c) triple(a, make_pair(b,c))

typedef long long int lli;
typedef pair<lli, int> para;
typedef pair<lli, pair<int,int> > triple;
typedef map<int, para> mapa;
bool removed[2000000];

lli oblicz(int n, int k, const vector<int>& data) {
    int siz = 0;
    int used = 0;
    lli res = 0, last = 0, a;
    mapa M;
    REP(i,n) {
        a = data[i];
        if ((last < 0 && a > 0) || (last > 0 && a < 0)) {
            if (last > 0 || M.size() > 0) {
                M[siz] = para(last, siz);
                removed[siz] = false;
                siz++;
            }
            last = a;
        } else {
            last += a;
        }
    }
    if (last > 0) {
        M[siz] = para(last, siz);
        removed[siz] = false;
        siz++;
    }
    priority_queue<triple, vector<triple>, greater<triple> > Q;
    FOREACH(it, M) {
        if (it->second.first > 0) {
            used++;
            res += it->second.first;
//            printf("PUSH %lld @ %d\n", it->second.first, it->second.second);
            Q.push(triple(it->second.first, it->second.second, it->second.second));
        } else {
//            printf("PUSH %lld @ %d\n", it->second.first, it->second.second);
            Q.push(triple(-it->second.first, it->second.second, it->second.second));
        }
    }
//    printf("Used %d -> %lld\n", used, res);
    while (used > k) {
        triple v = Q.top(); Q.pop();
        int id = v.second.second;
        int pos = v.second.first;
        lli val = v.first;
        if (removed[id]) {
            continue;
        }
//        printf("JOINING %lld pos %d\n", val, pos);
        mapa::iterator it,tit;
        it = M.lower_bound(pos);
        lli vv = it->second.first;
        removed[it->second.second] = true;
        if (it != M.begin()) {
            tit = it;
            tit--;
            vv += tit->second.first;
            removed[tit->second.second] = true;
            M.erase(tit);
        }
        tit = it;
        tit++;
        if (tit != M.end()) {
            vv += tit->second.first;
            removed[tit->second.second] = true;
            M.erase(tit);
        }
        M.erase(it);
        
        it = M.lower_bound(pos);
        bool border = ((it == M.begin()) || (it == M.end()));

        if (vv > 0 || !border) {
            M[pos] = para(vv, siz);
            Q.push(triple(abs(vv), pos, siz));
            removed[siz] = false;
            siz++;
        }
        used--;
        res -= val;
    }
    return res;
}

//lli best[1000000];
//lli end[1000000];
//int tab[1000000];
//
//lli brut(int n, int k, const vector<int>& data) {
//    REP(i,k+1) best[i] = end[i] = 0;
//    REP(i,n) {
//        int a = data[i];
//        for (int j = k; j > 0; j--) {
//            end[j] = max(end[j], best[j-1]) + a;
//            best[j] = max(best[j], end[j]);
//        }
//    }
//    return best[k];
//}
//
//int main() {
//    int n,k,l;
//    scanf("%d%d%d", &n, &k, &l);
//    srand(time(NULL));
//    while (true) {
//        vector<int> data;
//        REP(i,n) {
//            data.PB(rand()%(2*l+1)-l);
//        }
//        lli w1 = oblicz(n,k,data);
//        lli w2 = brut(n,k,data);
//        printf("%lld %lld\n", w1, w2);
//        if (w1 != w2) {
//            puts("------------");
//            printf("%d %d\n", n, k);
//            REP(i,n) printf("%d ", data[i]);
//            puts("");
//            return 0;
//        }
//    }
//}

int main() {
    int n,k,a;
    vector<int> data;
    scanf("%d%d", &n, &k);
    REP(i,n) {
        scanf("%d", &a);
        data.PB(a);
    }
    printf("%lld\n", oblicz(n,k,data));
    return 0;
}
