#include <cstdio>
#include <algorithm>
using namespace std;

int tab[2][1000000];
int res[2];
int beg, end;
int n;

void mov(bool mini) {
    for (int k = 0; k < 2; k++) {
        int a = tab[k][beg];
        int b = tab[k][(beg + 1) % n];
        res[k] = min(a,b);
        if (!mini) res[k] = max(a,b);
        //printf("MOV[%d,%d] %s -> %d\n", a, b, mini ? "min" : "max", res[k]);
    }
    tab[0][end] = res[1];
    tab[1][end] = res[0];
    beg = (beg + 2) % n;
    end = (end + 1) % n;
}

int main() {
    scanf("%d", &n);
    for (int k = 0; k < 2; k++)
        for (int i = 0 ; i < n; i++)
            scanf("%d", &tab[k][i]);
    
    int pw = 1, pi;
    for (pi = 0; 2 * pw <= n; pi++) pw *= 2;
    
    int size = n;
    int limit = n - pw;
    for (int i = 0; i < limit; i++) {
        mov(pi % 2 == 0);
        size--;
    }
    while (size > 1) {
        if (size == pw / 2) {
            pw /= 2;
            pi--;
        }
        mov(pi % 2 == 1);
        size--;
    }
    end = (end + n - 1) % n;
    printf("%d\n", tab[0][end] - tab[1][end]);
    return 0;
}
