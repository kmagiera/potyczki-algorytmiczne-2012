#include <map>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef unsigned long long llu;

int vals[1000];
llu counter[1000];
int maxxorek = -1;
vector<vector<llu> > dane;
vector<llu> sizy;
vector<llu> xorki;

int main() {
    int v = 0;
    for(int i = 0; i < 1000; i++) {
        vals[i] = v;
        v = v^i;
    }
    llu n;
    scanf("%llu", &n);
    llu total = 0;
    int xorek = 0;
    int maxcnt = 0;
    for (llu i = 1; i <= n; i++) {
        llu y = i;
        int cnt = 1;
        while (y % 2 == 0) {
            y /= 2;
            cnt++;
        }
        if (cnt > 0) xorek = xorek ^ vals[cnt-1] ^ vals[cnt];
        maxcnt = max(maxcnt, cnt);
        counter[xorek]++;
        maxxorek = max(xorek, maxxorek);
        if (y == 1) {
//            printf("%llu: ", i);
            vector<llu> yata;
            for (int i = 0; i <= maxxorek; i++) yata.push_back(counter[i]);
            dane.push_back(yata);
            sizy.push_back(i);
            xorki.push_back(xorek);
        }
//        if (xorek == 0) {
//            total++;
//            printf("%llu\n", i);
//        }
//        if (i % 1000000000LLU == 0) {
//            printf("JUŻ %llu -> %llu\n", i, total);
//        }
    }
//    printf("TOTAL %llu MAXCNT %d MAXXorek %d\n", total, maxcnt, maxxorek);
//    return 0;
    // liczymy dla 34359738369
    printf("#define MAGIC_X %d\n#define MAGIC_Y %d\n\n", (int)dane.size(), maxxorek+1);
    printf("llu size[MAGIC_X] = {");
    for (int i = 0; i < sizy.size(); i++) {
        if (i != 0) printf(",");
        printf("%lluLLU", sizy[i]);
    }
    printf("};\n\n");
    printf("llu xorki[MAGIC_X] = {");
    for (int i = 0; i < xorki.size(); i++) {
        if (i != 0) printf(",");
        printf("%lluLLU", xorki[i]);
    }
    printf("};\n\n");
    
    printf("llu magic[MAGIC_X][MAGIC_Y] = {\n");
    for (int i = 0; i < dane.size(); i++) {
        printf(" {");
        for (int j = 0; j <= maxxorek; j++) {
            if (j != 0) printf(",");
            if (dane[i].size()<=j) printf("0LLU");
            else printf("%lluLLU", dane[i][j]);
        }
        printf("},\n");
    }
    printf("};\n");
    printf("%d x %d\n", (int)dane.size(), maxxorek+1);
}
