// parent[i] is the just immediate ancestor of i
// level[i] is the level (0, 1, 2, ...) in the tree
// P[i][j] is the 2^j th ancestor of i
// call init() for all x (nodes of the tree)
// Preprocessing - O(nlogn)
// lca(u, v) - O(logn)

#define N 100100
#define LG 20
int parent[N], P[N][LG], level[N];

inline void init(int x, int n) {
    for(int i = 0; i < LG; i++) P[x][i] = -1;
    P[x][0] = parent[x];
    for(int j = 1; (1 << j) < n; j++)
        if(P[x][j - 1] != -1) P[x][j] = P[P[x][j - 1]][j- 1];
}

inline int lca(int x, int y) {
    if(level[x] < level[y]) swap(x, y);
    int lg = 1;
    while((1 << lg) <= level[x]) lg++; lg--;
    for(int i = lg; i >= 0; i--) {
        if(level[x] - (1 << i) >= level[y]) x = P[x][i];
    }
    if(x == y) return x;
    for(int i = lg; i >= 0; i--) {
        if(P[x][i] != -1 && P[x][i] != P[y][i]) x = P[x][i], y = P[y][i];
    }
    return parent[x];
}
