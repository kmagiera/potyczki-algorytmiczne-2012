#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

typedef pair<int,int> para;
para tab[500000];
vector<para> ev;

void insert(int a, int b, int v);
int maxi();
void init(int size);

int main() {
    int n;
    scanf("%d", &n);
    REP(i,n) {
        scanf("%d%d", &tab[i].first, &tab[i].second);
        ev.PB(para(tab[i].first, i + 1));
        ev.PB(para(tab[i].second, -i - 1));
    }
    sort(ev.begin(), ev.end());
    int xx = 0;
    int last = ev[0].first;
    for (int i = 0; i < ev.size(); i++) {
        if (last != ev[i].first) {
            last = ev[i].first;
            xx++;
        }
        ev[i].first = xx;
        if (ev[i].second < 0) {
            tab[-ev[i].second-1].second = xx;
        } else {
            tab[ev[i].second-1].first = xx;
        }
    }
//    for (int i = 0; i < n; i++) printf("%d %d\n", tab[i].first, tab[i].second);
    init(xx+1);
    for (int i = 0; i < n; i++) {
        insert(tab[i].first, tab[i].second - 1, 1);
    }
//    printf(" ----------- Maxi %d\n", maxi());
//    return 0;
    int stack = 0;
    int res = 0;
    for (int i = 0; i < ev.size(); i++) {
        if (ev[i].second < 0) {
            // zamkniecie
            int id = -ev[i].second - 1;
            insert(tab[id].first, tab[id].second - 1, 1);
            stack--;
        } else {
            // otwarcie
            int id = ev[i].second - 1;
            insert(tab[id].first, tab[id].second - 1, -1);
            stack++;
        }
        if (i != ev.size() - 1 && ev[i+1].first == ev[i].first) {
            continue;
        }
//        printf("Dla %d -> %d+%d\n", i, stack, maxi());
        res = max(res, stack + maxi());
    }
    printf("%d\n", res);
    return 0;
}

struct Node {
    int x,y;
    int w,W;
    Node *l, *r;
    void init(int xx, int yy);
    void insert(int a, int b, int v) {
//        printf("Insert [%d,%d] %d do [%d,%d]\n", a, b, v, x, y);
        if (b < x || a > y) {
            return;
        }
        if (a <= x && b >= y) {
            w += v;
        } else {
            if (l != NULL) l->insert(a,b,v);
            if (r != NULL) r->insert(a,b,v);
        }

        if (l != NULL && r != NULL) W = w + max(l->W, r->W);
        else if (l != NULL) W = w + l->W;
        else if (r != NULL) W = w + r->W;
        else W = w;
//        printf("W [%d,%d] W=%d w=%d\n", x, y, W, w);
    }
};

Node nodes[2000100];
Node * root = NULL;
int nodeptr = 0;

void Node::init(int xx, int yy) {
    x = xx; y = yy; w = W = 0; l = r = NULL;
    int mid = (x+y)/2;
    if (x != y) {
        l = &nodes[nodeptr++];
        r = &nodes[nodeptr++];
        l->init(x, mid);
        r->init(mid+1, y);
    }
}

void init(int size) {
    root = &nodes[nodeptr++];
    root->init(0, size);
}

void insert(int a, int b, int v) {
    if (b < a) return;
    root->insert(a,b,v);
}

int maxi() {
    return root->W;
}
