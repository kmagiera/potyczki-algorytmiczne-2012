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
#define triple(a,b,c) triple(a, make_pair(b,c))

#define QUERY -1

typedef long long int lld;
typedef pair<lld,lld> frac;
typedef pair<int,int> ev;

lld gcd(lld a, lld b) {
    lld t;
    while (b != 0) {
        t = b; b = a % b; a = t;
    }
    return a;
}

bool comp(const frac &a, const frac& b) {
    return a.first*b.second > b.first*a.second;
}

frac max(const frac& a, const frac& b) {
    if (comp(a,b)) {
        return a;
    }
    return b;
}

frac reduce(const frac& f) {
    lld div = f.first == 0 ? f.second : gcd(f.first, f.second);
    return frac(f.first / div, f.second / div);
}

//#define DEBUG 1
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

vector<int> data;
vector<frac> przedzialy[2000];
lld sumy[2000];
int S,N;

lld det(const frac& a, const frac& b, const frac& c) {
    return (b.first-a.first)*(c.second-a.second) - (b.second-a.second)*(c.first-a.first);
}

bool onLeft(const frac& a, const frac& b, const frac& c) {
    return det(a,b,c) > 0LL;
}

void liczprzedzial(int p) {
    int from = p*S, to  = min(N, (p+1)*S);
    lld l = 0;
    lld m = 0;
    vector<frac> res;
    res.PB(frac(0,0));
    FOR(i, from, to) {
        m++;
        l += data[i];
        frac f = frac(l,m);
        while (res.size() > 1
               && !onLeft(res[res.size()-2], res[res.size()-1], f)) {
            res.pop_back();
        }
        if (f.first > res[res.size()-1].first) {
            res.PB(f);
        }
    }
    sumy[p] = l;
    res.erase(res.begin());
    przedzialy[p] = res;
    
#ifdef DEBUG
    dbg("-- OTOCZKA %d\n", p);
    FOREACH(f,res) dbg("%lld/%lld ", f->first, f->second); dbg("\n");
#endif
}

void p_update(int p, lld v) {
    if (data[p] == v) return;
    data[p] = v;
    liczprzedzial(p/S);
}

inline frac fracdla(int p, int idx, lld l, lld m) {
    return frac(przedzialy[p][idx].first + l, przedzialy[p][idx].second + m);
}

frac p_szukaj(int id, lld p, lld q) {
    // narazie szukamy liniowo
    frac best = frac(p,q);
    FOREACH(f, przedzialy[id]) {
        best = max(best, frac(p+f->first,q+f->second));
    }
    return best;
}

frac log_szukaj(int id, lld p, lld q) {
    // szukamy logarytmicznie!!!!!
#ifdef DEBUG
    dbg("Szukamy dla %lld/%lld wsrod: ", p, q);
    FOREACH(f, przedzialy[id]) dbg("%lld/%lld ", f->first, f->second); dbg("\n");
#endif
    
    frac pt = frac(-p,-q);
    if (przedzialy[id].size() == 0) {
        return frac(p,q);
    }
    if (przedzialy[id].size() == 1) {
        return frac(p+przedzialy[id][0].first, q+przedzialy[id][0].second);
    }
    int l = 0, r = przedzialy[id].size()-1, mid;
    if (!onLeft(przedzialy[id][r-1], przedzialy[id][r], pt)) {
        return frac(p+przedzialy[id][r].first, q+przedzialy[id][r].second);
    }
    while (l < r) {
        mid = (l+r)/2;
        dbg("L=%d R=%d MID=%d %lld/%lld - %lld/%lld\n",
            l,r,mid,przedzialy[id][mid].first, przedzialy[id][mid].second,
            przedzialy[id][mid+1].first,przedzialy[id][mid+1].second);
        if (onLeft(przedzialy[id][mid], przedzialy[id][mid+1], pt)) {
            dbg("po lewej\n");
            r = mid;
        } else {
            dbg("po prwej\n");
            l = mid + 1;
        }
    }
    return frac(p+przedzialy[id][l].first, q+przedzialy[id][l].second);
}

frac p_query(int p) {
    frac maxi = frac(data[p],1);
    lld l = 0;
    lld m = 0;
    int end = min(N, (p/S + 1) * S);
    dbg("Query %d przedzial %d end %d\n", p, p/S, end);
    FOR(i,p,end) {
        m++;
        l+=data[i];
        maxi = max(maxi, frac(l,m));
    }
    dbg("Poczatkowe %lld/%lld\n", maxi.first, maxi.second);
    for (int i = end; i < N; i += S) {
//        frac fy = p_szukaj(i/S, l, m);
        frac fy = log_szukaj(i/S, l, m);
        dbg("Na przedziale %d start z %lld/%lld -> %lld/%lld\n", i/S, l, m, fy.first, fy.second);
        maxi = max(maxi, fy);
        l += sumy[i/S];
        m += S;
    }
    return maxi;
}

vector<frac> pierw(const vector<int>& cdata, const vector<ev>& evts) {
    // nie przejmujemy sie updateami
    data = cdata;
    vector<frac> res;

    N = data.size();
    S = sqrt(N);
    
    /* inicjalizacja */
    for (int i  = 0; i < N; i+= S) liczprzedzial(i/S);
    
    FOREACH(e, evts) {
        if (e->first == QUERY) {
            res.PB(p_query(e->second));
            dbg("Result %lld/%lld\n", res.back().first, res.back().second);
        } else {
            p_update(e->first, e->second);
        }
    }
    
    return res;
}

vector<frac> brut(const vector<int>& cdata, const vector<ev>& evts);
void print(const vector<frac>& res);
bool comp(const vector<frac>& r1, const vector<frac>& r2);
void genrandom(int n, int q, int u, int r, vector<int>& data, vector<ev>& evts);
void printtest(const vector<int>& data, const vector<ev>& evts);
void readinput(vector<int>& data, vector<ev>& evts);

void main_hamowy();
void main_brut();
void main_testgen();
void main_pierw();
void main_heureza();

int main() {
//    main_brut();
//    main_rozw();
//    main_pierw();
//    main_heureza();
    main_hamowy();
    return 0;
}

/// ------------- i niewazne co bedzie dalej :)

void main_heureza() {
    vector<int> data;
    vector<ev> evts;
    // gdy n,z < 200 to brutforce, wpp
    // rozwiazanie n^3/2log(n^1/2);
    readinput(data, evts);
    if (((int)data.size()) < 200 && ((int)evts.size()) < 200) {
        print(brut(data, evts));
    } else {
        print(pierw(data, evts));
    }
}

void main_pierw() {
    vector<int> data;
    vector<ev> evts;
    readinput(data, evts);
    print(pierw(data, evts));
}

void main_brut() {
    vector<int> data;
    vector<ev> evts;
    readinput(data, evts);
    print(brut(data, evts));
}

void main_testgen() {
    int n,q,u,r;
    srand(time(NULL));
    scanf("%d%d%d%d", &n, &q, &u, &r);
    int coile = 100000/n + 1;
    int ok = 1;
    vector<int> data;
    vector<ev> evts;
    genrandom(n,q,u,r,data,evts);
    printtest(data, evts);
}

void main_hamowy() {
    int n,q,u,r;
    srand(time(NULL));
    scanf("%d%d%d%d", &n, &q, &u, &r);
    int coile = 100000/n + 1;
    int ok = 1;
    
    while (true) {
        vector<int> data;
        vector<ev> evts;
        genrandom(n,q,u,r,data,evts);
        vector<frac> r1 = pierw(data, evts);
        vector<frac> r2 = brut(data, evts);
        if (!comp(r1, r2)) {
            puts(" ---- BUBA ---- ");
            printtest(data, evts);
            puts(" ---- BRUT ---- ");
            print(r2);
            puts(" ---- rozw ---- ");
            print(r1);
            return;
        }
        if (--ok <= 0) {
            printf("OK x %d\n", coile);
            ok = coile;
        }
    }
}

// MISC
void readinput(vector<int>& data, vector<ev>& evts) {
    int n,z,a,b;
    char c;
    scanf("%d%d", &n, &z);
    REP(i, n) {
        scanf("%d", &a);
        data.PB(a);
    }
    REP(i, z) {
        scanf(" %c ", &c);
        if (c == 'Z') {
            scanf("%d", &a);
            evts.PB(ev(QUERY,a-1));
        } else {
            scanf("%d%d", &a, &b);
            evts.PB(ev(a-1,b));
        }
    }
}

void printtest(const vector<int>& data, const vector<ev>& evts) {
    printf("%d %d\n", (int)data.size(), (int)evts.size());
    FOREACH(it, data) printf("%d ", *it);
    puts("");
    FOREACH(e, evts) {
        if (e->first < 0) {
            printf("Z %d\n", e->second+1);
        } else {
            printf("P %d %d\n", e->first+1, e->second);
        }
    }
}

void genrandom(int n, int q, int u, int r, vector<int>& data, vector<ev>& evts) {
    REP(i, n) {
        data.PB(rand()%r);
    }
    REP(i, q) {
        evts.PB(ev(QUERY, rand()%n));
    }
    REP(i, u) {
        evts.PB(ev(rand()%n, rand()%r));
    }
    random_shuffle(evts.begin(), evts.end());
}

bool comp(const vector<frac>& r1, const vector<frac>& r2) {
    REP(i, r1.size()) {
        frac f1 = reduce(r1[i]);
        frac f2 = reduce(r2[i]);
        if (f1 != f2) {
            return false;
        }
    }
    return true;
}

void print(const vector<frac>& res) {
    FOREACH(f, res) {
        frac r = reduce(*f);
        printf("%lld/%lld\n", r.first, r.second);
    }
}

vector<frac> brut(const vector<int>& cdata, const vector<ev>& evts) {
    vector<frac> res;
    vector<int> data = cdata;
    int n = data.size();
    FOREACH(ev, evts) {
        if (ev->first == QUERY) {
            frac maxi = frac(0,1);
            lld l = 0, m = 0;
            FOR(i,ev->second,n) {
                l += data[i];
                m += 1;
                maxi = max(maxi, frac(l, m));
            }
            res.PB(maxi);
        } else {
            data[ev->first] = ev->second;
        }
    }
    return res;
}
