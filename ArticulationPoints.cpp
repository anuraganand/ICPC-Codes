/*
  Articulation points, O(E+V)
*/

#define N 3010
vector <int> adl[N];    // Adjacency list
int art[N],visited[N]; // initialize art and visited by 0
int dn[N],parent[N];   // initialize parent to -1
int low[N],cnt;        // initialize cnt to 0
// root is also an articulation point if it has > 1 child
int dfsart(int v)
{
    int c = -1;
    visited[v] = 1;
    dn[v] = cnt++;
    low[v] = dn[v];
    for(int i=0; i < adl[v].size(); i++)
    {
        if(visited[adl[v][i]])
        {
            if(adl[v][i] != parent[v]) low[v] = min(low[v], dn[adl[v][i]]);
        }
        else
        {
            c++;
            parent[adl[v][i]] = v;
            dfsart(adl[v][i]);
            if(low[adl[v][i]] >= dn[v]) art[v]=1;
            low[v] = min(low[v], low[adl[v][i]]);
        }
    }
    return c;
}