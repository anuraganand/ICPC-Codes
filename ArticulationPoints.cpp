/*
  Articulation points, O(E+V)
*/

#define N 3010
vector <int> adl[N];    // Adjacency list
int art[N],visited[N]; // initialize art and visited by 0
int dn[N],parent[N];   // initialize parent to -1
int timer, tin[N], fup[N]; // initialize timer to 0

void dfsart(int v, int p = -1) {
    visited[v] = true;
    tin[v] = fup[v] = timer++;
    int children = 0;
    for (int i=0; i<adl[v].size(); ++i) {
        int to = adl[v][i];
        if (to == p)  continue;
        if (visited[to])
            fup[v] = min (fup[v], tin[to]);
        else {
            dfsart (to, v);
            fup[v] = min (fup[v], fup[to]);
            if (fup[to] >= tin[v] && p != -1)
                art[v] = 1;
            ++children;
        }
    }
    if (p == -1 && children > 1)
        art[v] = 1;
}
