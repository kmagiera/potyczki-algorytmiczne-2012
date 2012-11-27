#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <functional>
#include <cmath>
#include <ctime>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

//#define DEBUG 
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

typedef unsigned long long int llu;

llu brut(const vector<int>& data);
void main_brut();
llu read(vector<int>& data);

llu sum[1000000];
vector<int> data;

llu glupek() {
    if (data.size() == 1) return data[0];
    sum[0] = data[0];
    sum[1] = data[1];
    int n = data.size();
    FOR(i,2,n) {
        sum[i] = sum[i-2]+data[i];
    }
    if (n % 2 == 1) return sum[n-1];
    
    llu best = data[n/2-1] + data[n/2];
    int a = n/2-2, b = n/2+1;
    for (;a >= 0; a--, b++) {
        llu w1 = sum[b-1] - (a>1?sum[a-2]:0);
        llu w2 = sum[b] - (a>0?sum[a-1]:0);
        best = max(max(w1,w2), w1+w2-best);
    }
    return best;
}

void main_glupek() {
    data.clear();
    llu sum = read(data);
    llu w1 = glupek();
    printf("%llu %llu\n", w1, sum - w1);
}

void main_tester() {
    srand(time(NULL));
    int n,mod;
    scanf("%d%d", &n, &mod);
    data.clear();
    int v = 0;
    while (true) {
        data.clear();
        REP(i,n) data.PB(rand()%mod+1);
        llu sum = 0;
        REP(i,n) sum += data[i];
        llu w1 = glupek();
        llu w2 = brut(data);
        if (w1 != w2) {
            dbg("BUBA!----\n");
            REP(i,n) dbg("%d ", data[i]); puts("");
            dbg(" -> %llu powinno byc %llu\n", w1, w2);
            return;
        } else {
            v++;
            if (v % 1000 == 0) {
            dbg("OK x 1000\n");
            }
        }
    }
}

int main() {
//    main_brut();
    main_glupek();
//    main_tester();
    return 0;
}

llu read(vector<int>& data) {
    llu sum = 0;
    int n,a;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &a);
        sum += a;
        data.PB(a);
    }
    return sum;
}

vector<int> dane;
llu dp[200][200];
llu suma[200][200];

llu dynamik(int a, int b) {
    if (b < a) return 0;
    if (a == b) return dane[a];
    if (dp[a][b] > 0) return dp[a][b];
    dp[a][b] = suma[a][b] - min(dynamik(a+1,b), dynamik(a,b-1));
//    printf("db[%d][%d] = %d\n", a,b,dp[a][b]);
    if (b - a > 1) {
        dp[a][b] = max(dp[a][b], suma[a][b] - dynamik(a+1, b-1));
    } else dp[a][b] = max(dp[a][b], suma[a][b]);
//    printf("db[%d][%d] = %d\n", a,b,dp[a][b]);
    return dp[a][b];
    
}

llu brut(const vector<int>& data) {
    dane = data;
    int n = data.size();
    REP(i,n) {
        suma[i][i] = dane[i];
        dp[i][i] = 0;
        FOR(j,i+1,n) {
            dp[i][j] = 0;
            suma[i][j] = suma[i][j-1] + dane[j];
        }
    }
    return dynamik(0, data.size()-1);
}

void main_brut() {
    vector<int> data;
    llu sum = read(data);
    llu w1 = brut(data);
    printf("%llu %llu\n", w1, sum - w1);
}

