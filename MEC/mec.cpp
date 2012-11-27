#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long int llu;

int n,m;
llu tab[400000];

int main() {
    scanf("%d %d", &n, &m);
    int half = n/2, x;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &x);
            tab[x-1] = tab[x-1] * 2 + (j >= half ? 1 : 0);
        }
    }
    sort(tab, tab+n);
    for (int i = 1; i < n; i++) {
        if (tab[i] == tab[i-1]) {
            puts("NIE");
            return 0;
        }
    }
    puts("TAK");
    return 0;
}