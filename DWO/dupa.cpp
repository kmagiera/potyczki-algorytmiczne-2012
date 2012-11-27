#include <map>
#include <cstdio>
using namespace std;

typedef unsigned long long llu;

map<llu,int> G;

int oblicz(llu v) {
    if (G.find(v) != G.end()) {
        return G[v];
    }
    llu gr = 0;
    llu blink = v ^ (v & 1);
    for (int i = 2; blink != 0; i*= 2) {
        if ((v & i) != 0) {
            for (int j = i/2; j != 0; j/=2) {
                int x = oblicz(v ^ i ^ j);
                gr |= (1<<x);
            }
        }
        blink = blink ^ (blink & i);
    }
    int g = 0;
    int mask = 1;
    while ((gr & mask) != 0) {
        g++; mask *= 2;
    }
    G[v] = g;
    return g;
}

int main() {
    G[0] = 0;
    G[1] = 0;
    int vv = 0;
    for (int i = 0; i < 20; i++) {
        printf("G[%d] = %d\n", i, oblicz(vv));
        vv = 2*vv+1;
    }
}
