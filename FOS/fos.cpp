#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <functional>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back
#define X first
#define Y second
#define PT first
#define ID second
#define DIR second

#define INF 2000000000

#define ILEFT 0
#define IRIGHT 1
#define IUP 2
#define IDOWN 3
#define LEFT 400000000
#define RIGHT -2
#define DOWN 500000000
#define UP -4

//#define DEBUG
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

typedef pair<int,int> pt;
typedef pair<pt,pt> line;
typedef pair<pt, int> triple;

#define MAX_CROSS 14500000

int n;
line lines[5000];
triple cross[MAX_CROSS];
int k;

bool horizontal(const line& a) {
    return a.first.Y == a.second.Y;
}

bool online(const pt& p, const line& l) {
    return l.first.X <= p.X && l.second.X >= p.X && l.first.Y <= p.Y && l.second.Y >= p.Y;
}

bool ysort(const triple& a, const triple& b) {
    return a.PT.Y < b.PT.Y || (a.PT.Y == b.PT.Y && a.PT.X < b.PT.X)
    || (a.PT.Y == b.PT.Y && a.PT.X == b.PT.X && a.ID < b.ID);
}

bool skossort(const triple& a, const triple& b) {
    int difa = a.PT.X - a.PT.Y;
    int difb = b.PT.X - b.PT.Y;
    return difa < difb || (difa == difb && a.PT.X < b.PT.X) || (difa == difb && a.PT.X == b.PT.X && a.ID > b.ID);
}

void generuj() {
    k = 0;
    REP(i,n) {
        bool hor = false;
        if (horizontal(lines[i])) {
            cross[k++] = triple(lines[i].first, RIGHT);
            cross[k++] = triple(lines[i].second, LEFT);
            hor = true;
        } else {
            cross[k++] = triple(lines[i].first, UP);
            cross[k++] = triple(lines[i].second, DOWN);
        }
        FOR(j,i+1,n) {
            if (horizontal(lines[j]) != hor) {
                pt c = pt(lines[j].first.X, lines[i].first.Y);
                if (!hor) c = pt(lines[i].first.X, lines[j].first.Y);
                if (online(c, lines[i]) && online(c, lines[j])) {
                    cross[k] = triple(c, k);
                    k++;
                }
            }
        }
    }
}

int maxy[4][MAX_CROSS];
int addX[MAX_CROSS];

void przeglad() {
    sort(cross, cross+k);
    REP(i,k) {
        pt start = cross[i].PT;
        int lastY = INF;
        int stack = 0;
        for (;i < k;i++) {
            if (cross[i].PT.X != start.X) {
                i--;
                break;
            }
//            dbg("CROSS %d @ %d,%d\n", cross[i].ID, cross[i].PT.X, cross[i].PT.Y);
//            dbg(" -- lastY %d\n", lastY);
            if (cross[i].ID >= 0 && cross[i].ID < k) {
                maxy[IDOWN][cross[i].ID] = (lastY != INF) ? (cross[i].PT.Y - lastY) : 0;
//                dbg(" -- Maxy %d\n", maxy[IDOWN][cross[i].ID]);
            } else if (cross[i].ID == UP) {
                stack++;
                if (lastY == INF) lastY = cross[i].PT.Y;
            } else if (cross[i].ID == DOWN) {
                stack--;
                if (stack == 0) lastY = INF;
            }
//            dbg(" -- Stack %d lastY %d\n", stack, lastY);
        }
    }
    for (int i = k-1; i >= 0; i--) {
        pt start = cross[i].PT;
        int lastY = INF;
        int stack = 0;
        for (;i >= 0;i--) {
            if (cross[i].PT.X != start.X) {
                i++;
                break;
            }
            if (cross[i].ID >= 0 && cross[i].ID < k) {
                maxy[IUP][cross[i].ID] = (lastY != INF) ? (lastY - cross[i].PT.Y) : 0;
            } else if (cross[i].ID == DOWN) {
                stack++;
                if (lastY == INF) lastY = cross[i].PT.Y;
            } else if (cross[i].ID == UP) {
                stack--;
                if (stack == 0) lastY = INF;
            }
        }
    }
    sort(cross, cross+k, ysort);
    REP(i,k) {
        pt start = cross[i].PT;
        int lastX = INF;
        int stack = 0;
        for (;i < k;i++) {
            if (cross[i].PT.Y != start.Y) {
                i--;
                break;
            }
            if (cross[i].ID >= 0 && cross[i].ID < k) {
                maxy[ILEFT][cross[i].ID] = (lastX != INF) ? (cross[i].PT.X - lastX) : 0;
            } else if (cross[i].ID == RIGHT) {
                stack++;
                if (lastX == INF) lastX = cross[i].PT.X;
            } else if (cross[i].ID == LEFT) {
                stack--;
                if (stack == 0) lastX = INF;
            }
        }
    }
    for (int i = k-1; i >= 0; i--) {
        pt start = cross[i].PT;
        int lastX = INF;
        int stack = 0;
        for (;i >= 0;i--) {
            if (cross[i].PT.Y != start.Y) {
                i++;
                break;
            }
//            dbg("CROSS %d @ %d,%d\n", cross[i].ID, cross[i].PT.X, cross[i].PT.Y);
//            dbg(" -- lastY %d\n", lastX);
            if (cross[i].ID >= 0 && cross[i].ID < k) {
                maxy[IRIGHT][cross[i].ID] = (lastX != INF) ? (lastX - cross[i].PT.X) : 0;
//                dbg(" -- Maxy %d\n", maxy[IRIGHT][cross[i].ID]);
            } else if (cross[i].ID == LEFT) {
                stack++;
                if (lastX == INF) lastX = cross[i].PT.X;
            } else if (cross[i].ID == RIGHT) {
                stack--;
                if (stack == 0) lastX = INF;
            }
//            dbg(" -- Stack %d lastY %d\n", stack, lastX);
        }
    }
#ifdef DEBUG
    REP(i,k) {
        if (cross[i].ID >= 0 && cross[i].ID < k) {
            int id = cross[i].ID;
//            printf("Cross %d @ %d,%d -> up %d down %d left %d right %d\n",
//                   id, cross[i].PT.X, cross[i].PT.Y,
//                   maxy[IUP][id], maxy[IDOWN][id], maxy[ILEFT][id], maxy[IRIGHT][id]);
        }
    }
#endif
}

int skosuj() {
    // wywalamy konce linii i duplikaty
    REP(i,k) {
        if (cross[i].ID == UP || cross[i].ID == DOWN || cross[i].ID == LEFT || cross[i].ID == RIGHT) {
            swap(cross[i], cross[k-1]);
            k--;
            i--;
        }
        if (i > 0 && i < k && cross[i-1].PT.X == cross[i].PT.X && cross[i-1].PT.Y == cross[i].PT.Y) {
            swap(cross[i], cross[k-1]);
            k--;
            i--;
        }
    }
    int kk = k;
    // dodajemy koncowki do tablicy
    REP(i,kk) {
        triple p = cross[i];
        if (p.ID >= 0) {
            int mini = min(maxy[IRIGHT][p.ID], maxy[IUP][p.ID]);
            cross[k++] = triple(pt(p.PT.X+mini, p.PT.Y+mini), -p.ID-1);
        }
    }
    int maxi = -1;
    // przystepujemy do dzialania
    sort(cross,cross+k,skossort);
#ifdef DEBUG
    dbg(" -- SKOSY -- \n");
    REP(i,k) dbg("%d,%d ", cross[i].PT.X, cross[i].PT.Y); dbg("\n");
#endif
    int lastdif = INF;
    set<int> S;
    REP(i,k) {
        triple c = cross[i];
        if (c.PT.X - c.PT.Y != lastdif) {
            // inicializacja wiersza
            dbg("Nowy wiersz\n");
            lastdif = c.PT.X - c.PT.Y;
            S.clear();
        }

        if (c.ID < 0) {
            // usuwamy rekord
            int id = -c.ID-1;
//            dbg("Konjec @ %d,%d - %d\n", c.PT.X, c.PT.Y, id);
            S.erase(addX[id]);
            continue;
        }
        
        int scan = c.PT.X - min(maxy[ILEFT][c.ID], maxy[IDOWN][c.ID]);
//        dbg("Skosuje @ %d %d,%d - scan %d\n", c.ID, c.PT.X, c.PT.Y, scan);
        
        set<int>::iterator it = S.lower_bound(scan);
        if (it != S.end()) {
            dbg(" - Znalazlem %d\n", c.PT.X - (*it));
            maxi = max(maxi, c.PT.X - (*it));
        }
        addX[c.ID] = c.PT.X;
        S.insert(c.PT.X);
    }
    return maxi;
}

int rozw() {
    generuj();
    przeglad();
    return skosuj();
}

int main() {
    scanf("%d", &n);
    REP(i,n) {
        scanf("%d%d%d%d", &lines[i].first.X, &lines[i].first.Y,
              &lines[i].second.X, &lines[i].second.Y);
        if (lines[i].second < lines[i].first) {
            swap(lines[i].first, lines[i].second);
        }
    }
    int r = rozw();
    if (r < 1) puts("NIE");
    else printf("%d\n", r);
    return 0;
}
