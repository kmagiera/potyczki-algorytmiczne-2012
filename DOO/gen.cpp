#include <cstdio>

const int LNG_MAX = 360 * 60 * 60;

int main() {
    int n = 100000;
    int val = 5000;
    int start = 416288 % LNG_MAX;
    printf("%d %d\n", n, n);
    for (int i = 0; i < n; i++) printf("%d ", (start + i)%LNG_MAX);
    puts("");
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d\n", i%n+1, (i+1)%n+1, val, 1);
    }
}