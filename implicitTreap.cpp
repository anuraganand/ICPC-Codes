#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int,int> pii;
typedef vector <int> vi;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define forn(i, a, b) for(int i = (a); i < (b); ++i)
#define ford(i, a, b) for(int i = (a); i >= (b); --i)
#define fore(i, a, b) forn(i, a, b + 1)

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(c) c.begin(), c.end()
#define mset(a, v) memset(a, v, sizeof(a))
#define sz(a) ((int)a.size())

#define gi(x) scanf("%d", &x)
#define pis(x) printf("%d ", x)
#define pin(x) printf("%d\n", x)
#define pnl printf("\n")
#define dbn cerr << "\n"
#define dbg(x) cerr << #x << " : " << (x) << " "
#define dbs(x) cerr << (x) << " "

#define foreach(c, it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

const int N = 1000100;

// binary search tree w.r.t key and heap w.r.t priority
// implicitTreap has indices as keys
// x->update()              -> update values from its subtree
//
// printTreap(x)            -> print treap rooted at x
//
// split(x, l, r, key, add) -> split treap rooted at x into l and r such that all keys in l < key, add is the offset for index
//
// merge(x, l, r)           -> merge the subtrees rooted at l and r into x
//
// insert(x, pos, v)        -> insert a node at position pos with value v
//                             split the treap into [0, pos) and [pos, n)
//                             merge the left treap with new node and then merge the tree back  
//
// update                   -> first split [0, n) into [0, l) and [l, n)
//                          -> then split  [l, n) into [l, r] and [r + 1, n)
//                          -> then do the required operation on treap containing [l, r]
//                          -> lazy propagation can be implemented
//
// query                    -> repeat above procedure to obtain treap containing [l, r]    
//                          -> then return the corresponding value                                                     


struct node {
    int cnt, val, prior;
    ll sum;
    node * l, * r;

    inline void update() {
        cnt = 1 + (l ? l->cnt : 0) + (r ? r->cnt : 0);
        sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
    }
} mem[N];

typedef node * pNode;

inline pNode newNode() {
    static int memPtr = 0;
    return mem + memPtr++;
}

void print(pNode x, int level = 0) {
    if(!x) return;
    if(x->l) {
        print(x->l, level + 1);
    }
    printf("%*s(%d, %lld, %d)\n", level * 2, "", x->val, x->sum, x->prior);
    if(x->r) {
        print(x->r, level + 1);
    }
}

#define printTreap(x) { dbs(#x); dbn; print(x); puts(""); }

inline int size(pNode x) {
    return x ? x->cnt : 0;
}

inline ll sum(pNode x) {
    return x ? x->sum : 0;
}

void split(pNode x, pNode & l, pNode & r, int key, int add = 0) {
    if(!x) {
        l = r = NULL;
        return;
    }
    int curKey = add + size(x->l);
    if(key <= curKey) {
        split(x->l, l, x->l, key, add);
        r = x;
    } else {
        split(x->r, x->r, r, key, curKey + 1);
        l = x;
    }
    x->update();
}

void merge(pNode & x, pNode l, pNode r) {
    if(!l or !r)
        x = l ? l : r;
    else if(l->prior > r->prior) {
        merge(l->r, l->r, r);
        x = l;
    } else {
        merge(r->l, l, r->l);
        x = r;
    }
    if(x) x->update();
}

inline void insert(pNode & T, int pos, int v) {
    node * cur = newNode();
    cur->val = cur->sum = v;
    cur->prior = rand();
    cur->cnt = 1;
    cur->l = cur->r = NULL;
    pNode l, r;
    split(T, l, r, pos);
    merge(l, l, cur);
    merge(T, l, r);
}

inline void update(pNode & T, int pos, int v) {
    pNode l, m, r;
    split(T, l, m, pos);
    split(m, m, r, 1);

    if(m) {
        m->sum = m->val = v;
    }

    merge(T, l, m);
    merge(T, T, r);
}

inline ll getSum(pNode & T, int ql, int qr) {
    pNode l, m, r;

    split(T, l, m, ql);
    split(m, m, r, qr - ql + 1);

    ll ret = sum(m);

    merge(T, l, m);
    merge(T, T, r);

    return ret;
}