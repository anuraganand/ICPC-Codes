/* Shortest Path Faster Algorithm Paths Based for Min-Cost-Max Flow
	Complexity O(EV^3) (practically much less than that, way better than using Dijsktra)
*/

/* Min-Cost Max Flow implementation */
const int INF = 0x3f3f3f3f;
// MaxFlow and MinCost are lli
// allows multiple edges between nodes
// To check actual flow through edge -> edge.flow (would have positive value)
struct edge{
	int u,v,flow,cost;
	edge(){}
	edge(int u,int v,int f,int c) : u(u),v(v),flow(f),cost(c){}
};

struct MinCostMaxFlow 
{
  	int N;
  	vvi G;
  	vector<edge> E;
  	int totedges;
  	vi found,dad;
  	vlli dist;

  	MinCostMaxFlow(int N): 
  	N(N),G(N),found(N),dist(N),dad(N),totedges(0) {}
  
  	void addEdge(int from, int to, int capacity, int cost) 
  	{
	  	G[from].pb(totedges++);
	  	E.pb(edge(from,to,capacity,cost));
	  	G[to].pb(totedges++);
	  	E.pb(edge(to,from,0,-1*cost));
  	}
  
	bool spfa(int s,int t)
	{
	    fill(all(dad),-1);
	    fill(all(dist),INF);
	    fill(all(found),0);
	    queue<int> Q;
	    dist[s] = 0;
	    Q.push(s);
	    found[s] = true;
	    
	    while(!Q.empty()) {
	      int u = Q.front(); Q.pop();
	      if(u==t) continue;
	      rep(i,sz(G[u])) {
	      	edge &pres = E[G[u][i]];
	      	int v = pres.v;
	      	if(pres.flow <=0 ) continue;
	      	if(dist[u]  + pres.cost < dist[v]){
	      		dad[v] = G[u][i];
	      		dist[v] = dist[u] + pres.cost;
	      		if(!found[v]) Q.push(v),found[v] = true;
	      	}
	      }
	      found[u] = false;
	    }
	    return (dad[t] != -1);
  	}
 
 	lli dfs(int s,int t)
 	{
 		lli flow = INF;
 		for(int  i = dad[t];i!=-1;i = dad[E[i].u]) {
 			if(E[i].flow < flow ) flow = E[i].flow;
 		}
 		for(int i = dad[t];i!=-1;i = dad[E[i].u]) {
 			E[i].flow -=flow;
 			E[i^1].flow +=flow;
 		}
 		return flow;
 	}

  	pll getMaxFlow(int s, int t) 
  	{
	    lli totflow = 0,totcost = 0;
	    while(spfa(s,t)) {
	    	lli amt = dfs(s,t);
	    	totflow+=amt;
	    	totcost+= dist[t]*amt;
	    }
	    return mp(totflow,totcost);
  	}
};
