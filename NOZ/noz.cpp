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

#define UP (1<<0)
#define DOWN (1<<1)
#define LEFT (1<<2)
#define RIGHT (1<<3)
#define X first
#define Y second
#define XX first.first
#define YY first.second
#define DIR second.first
#define ID second.second
#define corner(pt, dir) corner(pt, make_pair(dir, -1))
typedef pair<int,int> pt;
typedef pair<pt, pt> corner;
typedef pair<pt, int> segment;
typedef map<int,int> mapa;

vector<corner> corners, corners2;
vector<segment> segh, segv;
vector<int> G[200000];
bool visited[200000];

int getdir(const pt& a, const pt& b) {
    return (a.Y == b.Y) ? ((a.X < b.X) ? RIGHT : LEFT) : ((a.Y < b.Y) ? UP : DOWN);
}

void add(const pt& a, const pt& b, const pt& c) {
    int d1 = getdir(a,b), d2 = getdir(b,c);
    if (d1 == UP && d2 == RIGHT) {
        corners2.PB(corner(b, UP | LEFT));
    } else if (d1 == UP && d2 == LEFT) {
        corners.PB(corner(b, UP | RIGHT));
    } else if (d1 == DOWN && d2 == RIGHT) {
        corners.PB(corner(b, DOWN | LEFT));
    } else if (d1 == DOWN && d2 == LEFT) {
        corners2.PB(corner(b, DOWN | RIGHT));
    } else if (d1 == RIGHT && d2 == UP) {
        corners.PB(corner(b, DOWN | RIGHT));
    } else if (d1 == RIGHT && d2 == DOWN) {
        corners2.PB(corner(b, RIGHT | UP));
    } else if (d1 == LEFT && d2 == UP) {
        corners2.PB(corner(b, DOWN | LEFT));
    } else if (d1 == LEFT && d2 == DOWN) {
        corners.PB(corner(b, UP | LEFT));
    }
    if (d1 == UP || d1 == DOWN) {
        segv.PB(segment(min(a,b), abs(a.Y-b.Y)));
    } else {
        segh.PB(segment(min(a,b), abs(a.X-b.X)));
    }
}

bool refcross(const pt& ref, const pt &a, const pt &b) {
    bool r = min(a.X, b.X) <= ref.X && max(a.X, b.X) > ref.X && min(a.Y, b.Y) <= ref.Y;
//    if (r) printf("Cross %d,%d-%d,%d\n", a.X, a.Y, b.X, b.Y);
    return r;
}

bool sortX(const corner& a, const corner& b) {
    if (a.XX == b.XX) {
        if (a.ID == -1 && b.ID == -1) return a.YY < b.YY;
        if (a.ID == -1 || b.ID == -1) return a.ID == -1;
        return a.YY < b.YY;
    }
    return a.XX < b.XX;
}

bool sortY(const corner& a, const corner& b) {
    if (a.YY == b.YY) {
        if (a.ID == -1 && b.ID == -1) return a.XX < b.XX;
        if (a.ID == -1 || b.ID == -1) return a.ID == -1;
        return a.XX < b.XX;
    }
    return a.YY < b.YY;
}

int dfs(int v) {
    visited[v] = true;
    int c = 1;
    FOREACH(it, G[v]) {
        if (!visited[*it]) c += dfs(*it);
    }
    return c;
}

int main() {
    int n;
    pt f,s,p,pp,a;
    scanf("%d%d%d%d%d", &n, &f.X, &f.Y, &s.X, &s.Y);
    int fdir = getdir(f, s);
    pt ref;
    switch (fdir) {
        case UP:
            ref = f;
            break;
        case DOWN:
            ref = pt(f.X-1, f.Y-1);
            break;
        case LEFT:
            ref = pt(f.X - 1, f.Y);
            break;
        case RIGHT:
            ref = pt(f.X, f.Y - 1);
            break;
    }
//    printf("Ref %d %d\n", ref.X, ref.Y);
    int cnt = refcross(ref, f, s);
    pp = f; p = s;
    for (int i = 2; i < n; i++) {
        scanf("%d%d", &a.X, &a.Y);
        add(pp, p, a);
        cnt += refcross(ref, p, a);
        pp = p;
        p = a;
    }
    add(pp, p, f);
    add(p, f, s);
    cnt += refcross(ref, p, f);
    
    if (cnt % 2 == 0) {
        corners = corners2;
    }
    int m = corners.size();
    REP(i,m) {
        corners[i].ID = i;
//        printf(" + %d %d (%d,%d)\n", corners[i].XX, corners[i].YY, corners[i].DIR, corners[i].ID);
    }
    corners2 = corners;
    // dodajemy segmenty do corners (listy eventow)
    // format: pt = pt DIR = height ID = -1
    FOREACH(seg, segv) corners.PB(corner(seg->first,seg->second));
    sort(corners.begin(), corners.end(), sortX);
    mapa M;
    FOREACH(c, corners) {
//        printf("POZIOM %d,%d %d %d\n", c->XX, c->YY, c->ID, c->DIR);
        if (c->ID < 0) {
            //segment
            mapa::iterator a,b;
            a = M.upper_bound(c->YY);
            b = M.lower_bound(c->YY + c->DIR);
            M.erase(a, b);
            continue;
        }
        int prev = M[c->YY];
        if (prev > 0 && (c->DIR & LEFT) != 0) {
            int previd = prev - 1;
            G[previd].PB(c->ID);
            G[c->ID].PB(previd);
        }
        if (c->DIR & LEFT) {
            M[c->YY] = -c->ID - 1;
        } else {
            M[c->YY] = c->ID + 1;
        }
    }
    corners = corners2;
    // dodajemy segmenty poziome
    // fotmat: pt = pt DIT = width ID = -1
    FOREACH(seg, segh) corners.PB(corner(seg->first,seg->second));
    sort(corners.begin(), corners.end(), sortY);
    M.clear();
    FOREACH(c, corners) {
//        printf("PION %d,%d %d %d\n", c->XX, c->YY, c->ID, c->DIR);
        if (c->ID < 0) {
            // segment
            mapa::iterator a,b;
            a = M.upper_bound(c->XX);
            b = M.lower_bound(c->XX + c->DIR);
            M.erase(a, b);
            continue;
        }
        int prev = M[c->XX];
        if (prev > 0 && (c->DIR & DOWN) != 0) {
            int previd = prev - 1;
            G[previd].PB(c->ID);
            G[c->ID].PB(previd);
        }
        if (c->DIR & DOWN) {
            M[c->XX] = -c->ID - 1;
        } else {
            M[c->XX] = c->ID + 1;
        }
    }
    
//    FOREACH(c, corners) {
//        if (c->ID < 0) continue;
//        printf("%d,%d[%d]: ", c->XX, c->YY, c->ID);
//        FOREACH(it, G[c->ID]) {
//            printf("%d ", *it);
//        }puts("");
//    }
    int res = 0;
    REP(i,m) {
        if (!visited[i]) {
            int w = dfs(i);
            res += (w/2) + (w%2);
        }
    }
    printf("%d\n", res);
    
    return 0;
}