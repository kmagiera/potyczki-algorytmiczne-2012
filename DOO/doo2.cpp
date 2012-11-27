//
//  doo2.cpp
//  Potyczki
//
//  Created by Krzysztof Magiera on 22.11.2012.
//  Copyright (c) 2012 Krzysztof Magiera. All rights reserved.
//

#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

#define PB(a,b) push_back(make_pair(a,b))
#define MP make_pair
#define FOREACH(it,X) for (__typeof(X.begin()) it = X.begin(); it != X.end(); ++it)

const int LNG_MAX = 360 * 60 * 60;
const int MAX_PRICE = 2 * 5000 * 200000 + 1;
typedef pair<int,int> para;

int n,m,root;
vector<para> G[200000];
int lng[100000];
bool used[200000];
int best[200000];

int main() {
    scanf("%d%d%d", &n, &m, &root);
    for (int i = 1; i < n; i++) {
        scanf("%d", &lng[i]);
        lng[i] = (lng[i] - root + LNG_MAX) % LNG_MAX;
    }
    for (int i = 0; i < m; i++) {
        int a, b, price, dir;
        scanf("%d%d%d%d", &a, &b, &price, &dir);
        a--;
        b--;
        
        if (lng[a] > lng[b]) {
            swap(a,b);
            dir = -dir;
        }
        
        if (a == 0) {
            if (dir == -1) {
                G[0].PB(b+n,price);
            } else {
                G[0].PB(b,price);
            }
        } if (dir == -1) {
            G[a].PB(b+n,price);
            G[a+n].PB(b+n,price);
            G[b].PB(a,price);
            G[b+n].PB(a,price);
        } else {
            G[a].PB(b,price);
            G[a+n].PB(b+n,price);
            G[b].PB(a,price);
            G[b+n].PB(a+n,price);
        }
        
    }
    
    priority_queue<para, vector<para>, greater<para> > Q;
    Q.push(para(0,0));
    fill(best, best + 2*n, MAX_PRICE);
    best[0] = 0;
    used[n] = true;
    
    while (!Q.empty()) {
        para p = Q.top(); Q.pop();
        if (!used[p.second]) {
            used[p.second] = true;
            FOREACH (it, G[p.second]) {
                printf("[%d z %s] -> [%d z %s] (%d)\n", (p.second%n)+1, (p.second>=n)?"prawej":"lewej",(it->first%n)+1, (it->first>=n)?"prawej":"lewej", it->second);
                int nprice = p.first + it->second;
                if (nprice < best[it->first] && !used[it->first]) {
                    best[it->first] = nprice;
                    printf("best[%d z %s] = %d\n", (it->first%n)+1, (it->first>=n)?"prawej":"lewej", nprice);
                    Q.push(para(nprice, it->first));
                }
            }
        }
    }
    
    int res = MAX_PRICE;
    for (int i = 1; i < n; i++) {
        if (best[i] < MAX_PRICE && best[i+n] < MAX_PRICE) {
            res = min(res, best[i] + best[i+n]);
        }
    }
    printf("%d\n", res < MAX_PRICE ? res : -1);
    
    return 0;
}

