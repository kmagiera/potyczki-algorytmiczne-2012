#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    int n,k,l;
    scanf("%d%d%d", &n, &k, &l);
    srand(time(NULL));
    printf("%d %d\n", n, k);
    for (int i = 0; i < n; i++) {
        int r;
        r = (rand()%(2*l+1)-l);
        printf("%d ", r);
    }
    puts("");
    return 0;
}
