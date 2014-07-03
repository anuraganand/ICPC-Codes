/*
    Ford Fulkerson with finding augmenting paths using DFS.
    O((E+V)*V) (In practice, even faster)
*/

#define N 2020
int s;              // Number of nodes in a graph
vector<int> adj[N]; // Directed graph adjacency list
int done[N];
int match[N];

bool trym(int a)
{
    if(a<0) return 0;
    for(int i=0;i<adj[a].size();i++)
        if(!done[adj[a][i]])
        {
            done[adj[a][i]]=1;
            if(match[adj[a][i]]==-1||trym(match[adj[a][i]]))
            {
                match[adj[a][i]]=a;
                return 1;
            }
        }
    return 0;
}
 
int maxMatch()
{
    mset(match,-1);
    count=0;
    for(int i=0;i<s;i++)
    {
        mset(done,0);
        if(trym(i)) count++;
    }
    return count;
}