#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

#define PB push_back
#define MP make_pair
#define FOREACH(it,X) for (__typeof(X.begin()) it = X.begin(); it != X.end(); ++it)

const int LNG_MAX = 360 * 60 * 60;
const int MAX_PRICE = 2 * 5000 * 200000 + 1;
typedef pair<int,pair<int, int> > Item;
struct Edge {
    int to, price, dir;
    Edge(int _to, int _price, int _dir) : to(_to), price(_price), dir(_dir) {};
};

int n,m,root;
vector<Edge> G[100000];
int lng[100000];
bool used[100000][2];
int best[100000][2];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &lng[i]);
        best[i][0] = best[i][1] = MAX_PRICE;
    }
    for (int i = 0; i < m; i++) {
        int a, b, price, dir;
        scanf("%d%d%d%d", &a, &b, &price, &dir);
        G[a-1].PB(Edge(b-1,price,dir));
        G[b-1].PB(Edge(a-1,price,-dir));
    }
    
    priority_queue<Item, vector<Item>, greater<Item> > Q;
    Q.push(Item(0, make_pair(0, 0)));
    used[0][0] = used[0][1] = true;
    best[0][0] = best[0][1] = 0;
    
    while (!Q.empty()) {
        Item u = Q.top(); Q.pop();
        int v = u.second.first;
        int dist = u.second.second;
        int price = u.first;
        int dir = dist > 0 ? 0 : 1;
//        printf("Jestem w %d: price %d dist %d dir %d\n", v, price, dist, dir);
        if (!used[v][dir] || v == 0) {
            used[v][dir] = true;
            FOREACH (it, G[v]) {
                int next_dist = ((lng[it->to] - lng[v]) * it->dir + LNG_MAX) % LNG_MAX;
                next_dist = next_dist * it->dir + dist;
                int next_price = price + it->price;
                int next_dir = next_dist > 0 ? 0 : 1;
//                printf(" -> Chcialbym isc do %d: price %d dist %d dir %d\n", it->to, next_price, next_dist, next_dir);
                if (next_price < best[it->to][next_dir]) {
//                    printf(" ->  No i Siuup!\n");
                    best[it->to][next_dir] = next_price;
                    Q.push(Item(next_price, make_pair(it->to, next_dist)));
                }
            }
        }
    }
    
    int res = MAX_PRICE;
    for (int i = 1; i < n; i++) {
        if (best[i][0] < MAX_PRICE && best[i][1] < MAX_PRICE) {
            res = min(res, best[i][0] + best[i][1]);
//            printf("Dla %d <- %d + %d\n", i, best[i][0], best[i][1]);
        }
    }
    printf("%d\n", res < MAX_PRICE ? res : -1);
    
    return 0;
}
