stack <int> dfs_scc;
bool in_stack[NN]; // set to 0
int dfs_low[NN];
int dfs_num[NN];
int counter; // set to 0 before every call of this function
bool scc_vis[NN];    // set to 0 
vector<int> adl[NN];


// call while some node is not visited
void tarjanSCC(int u) {
	dfs_low[u] = dfs_num[u] = counter++; scc_vis[u] = true;
	dfs_scc.push(u); in_stack[u] = true;
	for(int i=0;i<adl[u].size();i++) {
		int v = adl[u][i];
		if(!scc_vis[v])
			tarjanSCC(v);
		if(in_stack[v])
			dfs_low[u] = min(dfs_low[u], dfs_low[v]);
	}

	if(dfs_low[u] == dfs_num[u]) {
		// u is the root
		while(dfs_scc.size()&&dfs_scc.top()!=u) {
			in_stack[dfs_scc.top()] = 0;
			// Do your action here
			dfs_scc.pop();
		}

		in_stack[u]=0;
		// Do action for the root here
		dfs_scc.pop();
	}
}