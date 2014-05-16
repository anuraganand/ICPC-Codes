// N is the maximum length of string
// LG is the ceil of the log of max length
// rank[i] = rank of suffix starting from i in the sorted sequence
// sa[i] = position of the suffix in the string which is at i'th rank
// construciton - O(nlog^2n)
// lcp for two indices - O(logn)

#define N 10100
#define LG 18
int rank[N], sa[N], P[LG][N];

struct SuffixArray {
    int lg, len;
    struct node {
        int a, b, c;
        bool operator < (const node & r) const {
            if(a != r.a)
                return a < r.a;
            return b < r.b;
        }
    }L[N];

    // construct suffix array "sa" for given string
    void construct(string s) {
        len = (int)s.length(); lg = 1;
        for(int i = 0; i < len; i++) P[0][i] = int(s[i]);
        for(int shift = 1; shift < len; shift <<= 1, lg++) {
            for(int i = 0; i < len; i++) {
                L[i].a = P[lg - 1][i];
                L[i].b = i + shift < len ? P[lg - 1][i + shift] : -1;
                L[i].c = i;
            }
            sort(L, L + len);
            for(int i = 0; i < len; i++) 
                P[lg][L[i].c] = (i > 0 && L[i].a == L[i - 1].a && L[i].b == L[i - 1].b) ? P[lg][L[i - 1].c] : i;
        }
        lg--;
        for(int i = 0; i < len; i++) sa[P[lg][i]] = i;
        for(int i = 0; i < len; i++) rank[sa[i]] = i;
    }
    
    // construct longest common prefix for suffixes starting from i and j
    int lcp(int i, int j) {
        if(i == j) return len - i;
        int l = 0;
        for(int k = lg; k >= 0 && i < len && j < len; k--) {
            if(P[k][i] == P[k][j]) {
                i += 1 << k;
                j += 1 << k;
                l += 1 << k;
            }
        }
        return l;
    }
};