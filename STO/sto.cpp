#include <cstdio>
#include <algorithm>
using namespace std;

typedef unsigned long long int llu;

int main() {
    llu a,b,k;
    scanf("%llu %llu %llu", &a, &b, &k);
    llu mini = min(a/k, b/k);
    llu maxi = max(a/k, b/k);
    if (mini == 0) {
        puts("0");
        return 0;
    }
    if (mini == 1) {
        printf("%llu\n", maxi);
        return 0;
    }
    printf("%llu\n", 2 * mini + 2 * maxi - 4);
    return 0;
}