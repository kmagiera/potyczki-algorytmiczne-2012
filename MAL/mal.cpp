#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long int llu;

struct Rect {
    int ax,ay,bx,by;
};

Rect zero = {0,0,0,0};

Rect intersect(const Rect& a, const Rect& b) {
    Rect r;
    r.ax = max(a.ax, b.ax);
    r.ay = max(a.ay, b.ay);
    r.bx = min(a.bx, b.bx);
    r.by = min(a.by, b.by);
    if (r.ax >= r.bx || r.ay >= r.by) {
        return zero;
    }
    return r;
}

llu area(const Rect &a) {
    return ((llu)(a.bx-a.ax)) * ((llu)(a.by-a.ay));
}

int n;
Rect data[500000];
Rect cross[500000];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Rect x;
        scanf("%d%d%d%d", &x.ax, &x.ay, &x.bx, &x.by);
        data[i] = x;
        if (i == 0) {
            cross[0] = x;
        } else {
            cross[i] = intersect(cross[i-1], x);
        }
    }
    llu full = area(cross[n-1]);
    llu result = area(cross[n-2]);
    Rect decross = data[n-1];
    for (int i = n - 2; i >= 0; i--) {
        if (i != 0) {
            result = result + area(intersect(cross[i-1], decross)) - full;
        } else {
            result = result + area(decross) - full;
        }
        decross = intersect(decross, data[i]);
    }
    printf("%llu\n", result);
    return 0;
}
