#include <cstdio>

typedef unsigned long long int llu;

llu tab[40000];
int order[40000];
int tmp[40000];
int n, m, x;

int main() {
    scanf("%d%d", &n, &m);
    int half = n / 2;
    for (int i = 0; i < n; i++) order[i] = i;
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            tab[x-1] = tab[x-1] * 2 + (i >= half);
        }
        int lptr = 0, rptr = half;
        for (int i = 0; i < n; i++) {
            if (tab[order[i]] % 2 == 0) {
                tmp[lptr++] = order[i];
            } else {
                tmp[rptr++] = order[i];
            }
        }
        for (int i = 0; i < n; i++) order[i] = tmp[i];
        bool fail = false;
        for (int i = 1; i < n; i++) {
            if (tab[order[i-1]] == tab[order[i]]) {
                fail = true;
                break;
            }
        }
        if (!fail) {
            puts("TAK");
            return 0;
        }
    }
    puts("NIE");
    return 0;
}