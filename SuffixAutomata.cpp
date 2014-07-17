/* Suffix automata code O(n) time complexity */
/* This code is taken from http://e-maxx.ru/algo/suffix_automata */
/* Array Version and Map Version.
To convert to Map version comment the codes marked by 'Array version' and uncomment the codes marked by 'Map version'
*/

#define ALP 26 // Number of alphabets
#define MAXLEN 100100

struct state {
	int len, link;
	int next[ALP]; // Array Version //Stores next states for different transition symbols
	// map<int,int> next; // Map version
};

state st[MAXLEN*2];
int term[2*MAXLEN]; // Marks the terminal/final states.
int sz, last; // sz = size of the automata

void sa_init() // Initialize Suffix Automata
{
	sz = last = 0;
	st[0].len = 0;
	st[0].link = -1;
	++sz;
	
	// Array version
	for (int i=0; i<MAXLEN*2; ++i)
	{
		term[i]=0;
		for(int j=0;j<ALP;j++) st[i].next[j]=-1;
	}
	
	/*
	// Map version
	for (int i=0; i<MAXLEN*2; ++i) 
		term[i]=0,st[i].next.clear();
	*/
}

/*
	Progressively build the automata by adding a char to the end of the current string.
	NOTE: For the ARRAY Version, sa_extend() takes an int - the normalized value of the char. For e.g. if 'A'-> 0, 'B'-> 1 and so on.
*/
void sa_extend (int c)
{
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	int p;

	//Array version
	for (p=last; p!=-1 && st[p].next[c]==-1; p=st[p].link)
		st[p].next[c] = cur;

	/*
	// Map version
	for (p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
		st[p].next[c] = cur;
	*/

	if (p == -1)
		st[cur].link = 0;
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len)
			st[cur].link = q;
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;

			//Array version
			for(int i=0;i<ALP;i++) st[clone].next[i]=st[q].next[i];

			/* //Map Version
			st[clone].next = st[q].next;
			*/

			st[clone].link = st[q].link;
			for (; p!=-1 && st[p].next[c]==q; p=st[p].link)
				st[p].next[c] = clone;
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}

void mark_terminals() // Marks the terminal/final states of the automata
{
	int link=last;
	while(link!=-1)
	{
		term[link]=1;
		link=st[link].link;
	}
}
