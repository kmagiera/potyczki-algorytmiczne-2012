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

typedef unsigned long long int llu;
typedef pair<llu,llu> frac;
typedef pair<int,int> ev;

llu gcd(llu a, llu b) {
    llu t;
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
    llu div = f.first == 0 ? f.second : gcd(f.first, f.second);
    return frac(f.first / div, f.second / div);
}

frac best[500000];
int ending[500000];
vector<int> from[500001];
vector<int> data;

void rbuduj(int from, int to) {
    int n = data.size();
    for (int i = from; i >= to; i--) {
        frac ff = frac(data[i], 1);
        int end = i+1;
        //        printf("I %d -> %llu/%llu end %d\n", i + 1, ff.first, ff.second, end + 1);
        while (end < n) {
            //            printf(" - end %d -> %llu/%llu ~ %llu/%llu\n", end + 1, ff.first, ff.second, best[end].first, best[end].second);
            if (comp(best[end], ff)) {
                // dodajemy sztucznie
                ff = frac(ff.first + best[end].first, ff.second + best[end].second);
                end = ending[end];
            } else break;
        }
        best[i] = ff;
        ending[i] = end;
    }
}

vector<frac> rozw(const vector<int>& cdata, const vector<ev>& evts) {
    // nie przejmujemy sie updateami
    data = cdata;
    
    int tfrom = data.size() - 1;
    vector<frac> res;
    FOREACH(ev, evts) {
        if (ev->first == QUERY) {
            if (ev->first <= tfrom) {
                rbuduj(tfrom, ev->first);
                tfrom = ev->first - 1;
            }
            res.PB(best[ev->second]);
        } else {
            if (data[ev->first] != ev->second) {
                data[ev->first] = ev->second;
                tfrom = max(tfrom, ev->first);
            }
        }
    }
    return res;
}

//#define DEBUG 1
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

vector<frac> przedzialy[2000];
llu sumy[2000];
int S,N;

void liczprzedzial(int p) {
    vector<frac> vals;
    int from = p*S, to  = min(N, (p+1)*S);
    llu l = 0;
    llu m = 0;
    FOR(i, from, to) {
        m++;
        l += data[i];
        vals.PB(frac(l,m));
    }
    sumy[p] = l;
    sort(vals.begin(), vals.end(), comp);
#ifdef DEBUG
    dbg("-- WARTOSCI %d\n", p);
    FOREACH(f,vals) dbg("%llu/%llu ", f->first, f->second); dbg("\n");
#endif

    // zostawiamy tylko wartosci przy rosnacej dlugosci
    przedzialy[p].clear();
    przedzialy[p].PB(vals[0]);
    llu lastlen = vals[0].second;
    FOR(i,1,vals.size()) {
        if (vals[i].second > lastlen) {
            przedzialy[p].PB(vals[i]);
            lastlen = vals[i].second;
        }
    }
#ifdef DEBUG
    dbg("-- PREDZIALY %d\n", p);
    FOREACH(f,przedzialy[p]) dbg("%llu/%llu ", f->first, f->second); dbg("\n");
#endif
}

void p_update(int p, llu v) {
    if (data[p] == v) return;
    data[p] = v;
    liczprzedzial(p/S);
}

inline frac fracdla(int p, int idx, llu l, llu m) {
    return frac(przedzialy[p][idx].first + l, przedzialy[p][idx].second + m);
}

bool comph(const frac& a, const frac& b) {
    bool r = comp(a,b);
    dbg(" - COMP  %llu/%llu, %llu/%llu - %s\n", a.first, a.second, b.first, b.second, r?"true":"false");
    return r;
}

frac p_szukaj(int id, llu p, llu q) {
    // narazie szukamy liniowo
    frac best = frac(p,q);
    FOREACH(f, przedzialy[id]) {
        best = max(best, frac(p+f->first,q+f->second));
    }
    return best;
}

frac p_query(int p) {
    frac maxi = frac(data[p],1);
    llu l = 0;
    llu m = 0;
    int end = min(N, (p/S + 1) * S);
    dbg("Query %d przedzial %d end %d\n", p, p/S, end);
    FOR(i,p,end) {
        m++;
        l+=data[i];
        maxi = max(maxi, frac(l,m));
    }
    dbg("Poczatkowe %llu/%llu\n", maxi.first, maxi.second);
    for (int i = end; i < N; i += S) {
        frac fy = p_szukaj(i/S, l, m);
        dbg("Na przedziale %d start z %llu/%llu -> %llu/%llu\n", i/S, l, m, fy.first, fy.second);
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
            dbg("Result %llu/%llu\n", res.back().first, res.back().second);
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
void main_rozw();
void main_brut();
void main_comparer();
void main_testgen();
void main_pierw();

int main() {
//    main_brut();
//    main_rozw();
    main_pierw();
//    main_hamowy();
    return 0;
}

/// ------------- i niewazne co bedzie dalej :)

void main_pierw() {
    vector<int> data;
    vector<ev> evts;
    readinput(data, evts);
    print(pierw(data, evts));
}

void main_rozw() {
    vector<int> data;
    vector<ev> evts;
    readinput(data, evts);
    print(rozw(data, evts));
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

void main_comparer() {
    vector<int> data;
    vector<ev> evts;
    readinput(data, evts);
    vector<frac> r1 = brut(data, evts);
//    print(r1);
//    puts(" -----------------");
    vector<frac> r2 = rozw(data, evts);
//    print(r2);
    puts(comp(r1, r2) ? "OK" : "BUBA!!!!!!");
}

// MISC
void readinput(vector<int>& data, vector<ev>& evts) {
    int n,z,a,b;
    char c;
    scanf("%d %d ", &n, &z);
    REP(i, n) {
        scanf("%d ", &a);
        data.PB(a);
    }
    REP(i, z) {
        scanf("%c ", &c);
        if (c == 'Z') {
            scanf("%d ", &a);
            evts.PB(ev(QUERY,a-1));
        } else {
            scanf("%d %d ", &a, &b);
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
        printf("%llu/%llu\n", r.first, r.second);
    }
}

vector<frac> brut(const vector<int>& cdata, const vector<ev>& evts) {
    vector<frac> res;
    vector<int> data = cdata;
    int n = data.size();
    FOREACH(ev, evts) {
        if (ev->first == QUERY) {
            frac maxi = frac(0,1);
            llu l = 0, m = 0;
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
