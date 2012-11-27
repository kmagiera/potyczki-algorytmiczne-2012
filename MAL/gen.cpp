#include <cstdio>

int main() {
    int n = 500000;
    printf("%d\n", n);
    int size = 1000000000;
    for (int i = 0; i < n; i++) {
        printf("%d %d %d %d\n", i, i, size, size);
        size--;
    }
}