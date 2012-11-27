#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <functional>
using namespace std;

#define FOR(i,s,e) for (int i=(s);i<(e);i++)
#define REP(i,n) FOR(i,0,n)
#define FOREACH(i,c) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define PB push_back

#define SING 0
#define DOUB 1
#define ROOT 2

#define DEBUG
#ifdef DEBUG
#define dbg printf
#else
#define dbg(...)
#endif

int level = 0;
int rot = 0;
int type = ROOT;
int pos = 0;
int offset = 0;

queue<int> kroki;

int pajac(int level = 0, int rot = 0, int type = ROOT, int pos = 0, int offset = 0, int *back = NULL) {
    if (kroki.empty()) return;
    int krok = kroki.front(); kroki.pop();
    
    if (level == 0) {
        return pajac(1, 1, SING, 0, 0);
    }
    
    int startpos = pos;
    
    while (!kroki.empty()) {
        krok = kroki.front(); kroki.pop();
        int realdir = (k+rot)%7;
        
        if (realdir == 0) {
            // idziemy w prawo po tym samym poziomie
            if (level != 1 && type == SING && offset == 2) {
                type = DOUB;
            } else if (type == DOUB) {
                type = SING;
            }
            if (type == SING) {
                rot = 2;
            } else {
                rot = 3;
            }
            offset = (offset+1)%3;
            pos += 1;
        } else if ((realdir == 2 && type == SING) || (realdir == 3 && type == DOUB)) {
            // idziemy przeciwnie do wsk zegara
            if (level != 1 && type == SING && offset == 1) {
                type = DOUB;
            } else if (type == DOUB) {
                type = SING;
            }
            rot = 0;
            offset = (offset+2)%3;
            pos -= 1;
        } else if (realdir == 1) {
            // cofamy sie do korzenia pierwsza sciezka
            if (back != NULL) *back = 1;
            return pos - startpos;
        } else if (realdir == 2 && type == DOUB) {
            // cofamy sie do korzenia druga sciezka
            if (back != NULL) *back = 2;
            return pos - startpos;
        } else if (type == SING) {
            // idziemy w dol do realdir - 3 sasiada (jest ich 4)
            int back = 0;
            int mov = pajac(level+1,realdir==6?2:1,?,?,(realdir-3)%3, &back);
            // TODO: uwaga, bo nie do konca tak bedzie...
            
            int movi = mov;
            while (movi != 0) {
                
            }
            
        } else if (type == DOUB) {
            // idziemy w dol do realdir - 4 sasiada (jest ich 3)
            int mov = pajac(level+1,realdir==6?2:1,?,?,(realdir-3)%3);
            // TODO: kokokoko eurospoko;
        }
        
    }
}

int main() {
    int n,z;
    scanf("%d", &n-1);
    REP(i,n) {
        scanf("%d", &z);
        kroki.push(z);
    }
    pajac();
    scanf("%z", &z);
    printf("Jeszcze z %d\n", z);
    return 0;
}