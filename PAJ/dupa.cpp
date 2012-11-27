#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

#define SNG 0
#define DBL 1
#define ROOT 2

#define DEBUG
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

vector<int> types;
vector<int> rootno;
int rot;

const char * T(int t) {
    if (t == SNG) return "SINGLE";
    if (t == DBL) return "DOUBLE";
    if (t == ROOT) return "ROOT";
    return "UNKNOWN!";
}

int dodaj(int lvl = -1) {
    if (lvl == -1) lvl = types.size()-1;
    dbg("Dodaj lvl %d\n", lvl);
    if (lvl == 0) return ROOT;
    int rtype = types[lvl-1];
    int idx = rootno[lvl];
    if (rtype == ROOT) {
        return types[lvl] = SNG;
    }
    if ((rtype == DBL && idx == 2) || (rtype == SNG && idx == 3)) {
        int ntype = dodaj(lvl-1);
        rootno[lvl] = 1;
        dbg(" -> rootno[%d] %d\n", lvl, rootno[lvl]);
        return types[lvl] = SNG;
    } else {
        // wszystko ok, nie trzeba isc w gore
        rootno[lvl] = idx + 1;
        dbg(" -> rootno[%d] %d\n", lvl, rootno[lvl]);
        if (rtype == SNG && (idx+1) == 3) {
            return types[lvl] = DBL;
        } else if (rtype == SNG && (idx+1) < 3) {
            return types[lvl] = SNG;
        } else if (rtype == DBL && (idx+1) == 2) {
            return types[lvl] = DBL;
        } else if (rtype == DBL && (idx+1) == 1) {
            return types[lvl] = SNG;
        }
    }
    dbg("BUBA @ dodaj\n");
    return -1;
}

int odejmij(int lvl = -1) {
    if (lvl == -1) lvl = types.size()-1;
    dbg("Odejmij lvl %d\n", lvl);
    if (lvl == 0) return ROOT;
    int rtype = types[lvl-1];
    int idx = rootno[lvl];
    dbg(" - Rtype %s idx %d\n", T(rtype), idx);
    if (rtype == ROOT) {
        return types[lvl] = SNG;
    }
    if (idx == 0) {
        int ntype = odejmij(lvl-1);
        rootno[lvl] = (ntype != DBL) ? 2 : 1;
        dbg(" -> rootno[%d] %d\n", lvl, rootno[lvl]);
        return types[lvl] = SNG;
    } else {
        rootno[lvl] = idx - 1;
        dbg(" -> rootno[%d] %d\n", lvl, rootno[lvl]);
        if (rtype == SNG && (idx-1) == 0) {
            return types[lvl] = DBL;
        } else if (rtype == SNG && (idx-1) > 0) {
            return types[lvl] = SNG;
        } else if (rtype == DBL && (idx-1) == 0) {
            return types[lvl] = DBL;
        } else if (rtype == DBL && (idx-1) > 0) {
            return types[lvl] = SNG;
        }
    }
    dbg("BUBA @ odejmij idx %d roottype %s lvl %d\n", idx, T(rtype), lvl);
    return -1;
}

void pajac(int mv) {
    dbg(" --- MOVE %d\n", mv);
    if (rootno.size() == 0) {
        rootno.PB(0);
        types.PB(ROOT);
        rootno.PB(1);
        types.PB(SNG);
        rot = 1;
    }
    int realdir = (mv+rot)%7;
    int type = types.back();
    int rtype = types[types.size()-2];
    int idx = rootno.back();
    
    dbg("Pajacuje %d rot %d realdir %d type %s roottypr %s idx %d\n",
        (int)types.size(), rot, realdir, T(type), T(rtype), idx);
    
    if (type == SNG && realdir == 1) {
        // drapiemy sie do gory
        types.pop_back();
        rootno.pop_back();
        if (rtype == SNG) {
            rot = 3 + idx;
        } else {
            rot = 5;
        }
    } else if (type == DBL && realdir == 1) {
        // drapiemy sie do gory
        types.pop_back();
        rootno.pop_back();
        if (idx == 0) {
            rot = (rtype == SNG) ? 3 : 4;
        } else {
            rtype = odejmij();
            if (rtype == SNG) {
                rot = 3;
            } else {
                rot = 4;
            }
        }
    } else if (type == DBL && realdir == 2) {
        // drapiemy sie do gory
        types.pop_back();
        rootno.pop_back();
        if (idx == 0) {
            rtype = odejmij();
        }
        rot = 6;
    } else if (realdir == 0) {
        // lecimy w prawo
        if (dodaj() == SNG) {
            rot = 2;
        } else {
            rot = 3;
        }
    } else if ((type == SNG && realdir == 2) || (type == DBL && realdir == 3)) {
        odejmij();
        rot = 0;
    } else if (type == DBL && realdir > 3) {
        // idziemy w dol
        if (realdir == 4) {
            types.PB(DBL);
            rootno.PB(0);
            rot = 1;
        } else if (realdir == 5) {
            types.PB(SNG);
            rootno.PB(1);
            rot = 1;
        } else if (realdir == 6) {
            types.PB(DBL);
            rootno.PB(2);
            rot = 2;
        }
    } else if (type == SNG && realdir > 2) {
        // idziemy w dol
        if (realdir == 3) {
            types.PB(DBL);
            rootno.PB(0);
            rot = 1;
        } else if (realdir == 4) {
            types.PB(SNG);
            rootno.PB(1);
            rot = 1;
        } else if (realdir == 5) {
            types.PB(SNG);
            rootno.PB(2);
            rot = 1;
        } else if (realdir == 6) {
            types.PB(DBL);
            rootno.PB(3);
            rot = 2;
        }
    }
    if (rootno.size() == 2) rootno[1] = 0;
    
    dbg("Koncze z lvl %d type %s rot %d idx %d\n", (int)types.size(), T(types.back()), rot, rootno.back());
}

int main() {
    int n,z;
    scanf("%d", &n);
    REP(i,n-1) {
        scanf("%d", &z);
        pajac(z);
    }
    scanf("%d", &z);
    printf("Jeszcze z %d\n", z);
    return 0;
}