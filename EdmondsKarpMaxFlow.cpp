/* Edmonds Karp algorithm (implementation of Ford Fulkerson method) for Max Flow
	Complexity O(EV^2) (practically much less than that)
*/

#define N 60 // Maximum number of nodes

struct MaxFlow
{
	int adm[N][N]; // Stores capacities of DIRECTED edges
	int radm[N][N];// Residual Graph
	int par[N];
	int visited[N];

	MaxFlow()
	{
		memset(adm,0,sizeof(adm));
		memset(radm,0,sizeof(radm));
	}

	void addEdge(int a, int b, int cap) // Adds DIRECTED edge (a->b) with capactity cap
	{
		adm[a][b]+=cap;
		radm[a][b]+=cap;
	}

	int bfsFlow(int a, int b)
	{
		int temp;
		queue<int> que;
		memset(visited,0,sizeof(visited));
		par[a]=-1; visited[a]=1;
		que.push(a);
		while(que.size())
		{
			temp=que.front();
			que.pop();
			for(int i=0;i<N;i++) if(!visited[i]&&radm[temp][i]>0)
			{
				que.push(i);
				par[i]=temp;
				visited[i]=1;
			}
		}
		if(visited[b]==0) return 0;
		int path_flow=INF;
		int v=b;
		while(par[v]!=-1)
		{
			path_flow=min(path_flow,radm[par[v]][v]);
			v=par[v];
		}
		v=b;
		while(par[v]!=-1)
		{
			radm[par[v]][v]-=path_flow;
			radm[v][par[v]]+=path_flow;
			v=par[v];
		}
		return path_flow;
	}

	int maxFlow(int a, int b)	// Returns max flow from a to b
	{
		int max_flow=0,path_flow=0;
		while((path_flow=bfsFlow(a,b))>0) max_flow+=path_flow;
		return max_flow;	
	}

};