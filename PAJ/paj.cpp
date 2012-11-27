#include <cstdio>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

//#define DEBUG
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

int w1 = 0, w2 = 0;
int siz;

struct Node {
    Node * n;
    int v;
};

Node * paj;

#ifdef DEBUG
void printpaj(Node * q) {
    Node *start = q;
    while (true) {
        dbg("%d ", q->v);
        q = q->n;
        if (q == start) break;
    }
    dbg("\n");
}
#else
#define printpaj(...)
#endif

void pajakjebiedronke(bool dir = false) {
    Node * q = paj;
    for (; siz > 3; q = q->n) {
        
        dbg("w1 %d w2 %d - CIAG: ", w1, w2);
        printpaj(q);
        
        if (q->n->v == 7 && (q->v + q->n->n->v) < 8) {
            q->v = q->v + q->n->n->v;
            q->n = q->n->n->n;
            siz-=2;
            w2--;
            dbg("Ruch 7 w1 %d w2 %d nowy %d\n", w1, w2, q->v);
        }
        else if (q->n->v == 0 && (q->v + q->n->n->v) < 8) {
            q->v = q->v + q->n->n->v;
            q->n = q->n->n->n;
            siz-=2;
            w1--;
            dbg("Ruch zero w1 %d w2 %d nowy %d\n", w1, w2, q->v);
        } else if (q->n->v == 1 && q->v > 0 && q->n->n->v > 0) {
            // ruchamy 1
            q->v = q->v - 1;
            q->n = q->n->n;
            q->n->v = q->n->v - 1;
            siz--;
            w2--;
            dbg("Ruch jeden w1 %d w2 %d\n", w1, w2);
        }
        else if (q->n->v == 2 && q->n->n->v == 2 && q->v > 0 && q->n->n->n->v > 0) {
            // ruchamy 2,2
            q->v = q->v - 1;
            q->n->v = 4;
            q->n->n = q->n->n->n;
            q->n->n->v = q->n->n->v - 1;
            w2 -= 2;
            w1 ++;
            siz--;
            dbg("Ruch 2,2 w1 %d w2 %d\n", w1, w2);
        }
        else if (q->n->v == 6 && q->v < 7 && q->n->n->v < 7) {
            // ruchamy 6
            q->v = q->v + 1;
            q->n = q->n->n;
            q->n->v = q->n->v + 1;
            siz--;
            w1--;
            dbg("Ruch 6 %d w2 %d\n", w1, w2);
        }
        else if (q->n->v == 5 && q->n->n->v == 5 && q->v < 7 && q->n->n->n->v < 7) {
            // ruchamy 5,5
            q->v = q->v + 1;
            q->n->v = 3;
            q->n->n = q->n->n->n;
            q->n->n->v = q->n->n->v + 1;
            w1 -= 2;
            w2 ++;
            siz--;
            dbg("Ruch 5,5 w1 %d w2 %d\n", w1, w2);
        }
    }
    dbg("Na koniec: ");
    printpaj(q);
}

int main() {
    int n;
    scanf("%d", &n);
    Node * q = NULL, *s;
    REP(i,n) {
        if (q != NULL) {
            q->n = new Node();
            q = q->n;
        } else {
            paj = q = new Node();
        }
        scanf("%d", &q->v);
    }
    siz = n;
    q->n = paj;
    pajakjebiedronke();
    printf("%d\n", max(w1, w2));
}
