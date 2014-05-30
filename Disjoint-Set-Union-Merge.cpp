/* Disjoint Set Union Data Structure */

#define N 100100
int _par[N];

struct DisjointSet
{
	DisjointSet()
	{
		for(int i=0;i<N;i++) _par[i]=i;
	}

	int getRoot(int k)
	{
		if(par[k]==k) return k;
		return par[k]=getroot(par[k]);
	}

	void merge(int a, int b)
	{
		par[getroot(a)]=getroot(b);
	}
};