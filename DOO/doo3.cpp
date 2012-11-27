#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
using namespace std;

#define PB push_back
#define MP make_pair
#define FOREACH(it,X) for (__typeof(X.begin()) it = X.begin(); it != X.end(); ++it)

const int LNG_MAX = 360 * 60 * 60;
const int MAX_PRICE = 2 * 5000 * 200000 + 17;
typedef pair<int,int> para;
typedef long long int lld;
struct Edge {
    int to, price, dist;
    Edge(int a, int b, int c) : to(a), price(b), dist(c) {};
};

int n,m,root;
vector<Edge> G[100000];
int lng[100000];
bool used[100000];
lld len[100000];
int best[100000];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &lng[i]);
    }
    for (int i = 0; i < m; i++) {
        int a, b, price, dir;
        scanf("%d%d%d%d", &a, &b, &price, &dir);
        a--; b--;
        if (lng[a] > lng[b]) {
            swap(a,b); dir = -dir;
        }
        if (dir == 1) {
            G[a].PB(Edge(b,price,lng[b]-lng[a]));
            G[b].PB(Edge(a,price,lng[a]-lng[b]));
        } else {
            G[a].PB(Edge(b,price,lng[b]-lng[a]-LNG_MAX));
            G[b].PB(Edge(a,price,LNG_MAX-(lng[b]-lng[a])));
        }
    }
    
    priority_queue<para, vector<para>, greater<para> > Q;
    Q.push(para(0,0));
    fill(best,best+n,MAX_PRICE);
    best[0] = 0; len[0] = 0;
    int res = MAX_PRICE;
    
    while (!Q.empty()) {
        para u = Q.top(); Q.pop();
        int v = u.second;
        if (!used[v]) {
            used[v] = true;
            FOREACH (it, G[v]) {
                lld next_dist = len[v] + ((lld)it->dist);
                int next_price = best[v] + it->price;
                if (best[it->to] != MAX_PRICE && len[it->to] != next_dist) {
                    res = min(res, best[it->to] + next_price);
                }
                if (next_price < best[it->to]) {
                    best[it->to] = next_price;
                    len[it->to] = next_dist;
                    Q.push(para(next_price,it->to));
                }
            }
        }
    }
    
    printf("%d\n", res < MAX_PRICE ? res : -1);
    
    return 0;
}
