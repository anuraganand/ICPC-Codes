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
		if(_par[k]==k) return k;
		return _par[k]=getRoot(_par[k]);
	}

	void merge(int a, int b)
	{
		_par[getRoot(a)]=getRoot(b);
	}
};