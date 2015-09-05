// N is the maximum length of string
// LG is the ceil of the log of max length + 1
// rank[i] = rank of suffix starting from i in the sorted sequence
// sa[i] = position of the suffix in the string which is at i'th rank
// construciton - O(nlog^2n)
// lcp for two indices - O(logn)

#define N 100100
#define LG 20
int rank[N], sa[N], P[LG][N];

struct SuffixArray {
    int lg, len, cum[N];
    struct node {
        int a, b, c;

/*        bool operator < (const node & r) const {
            if(a != r.a)
                return a < r.a;
            return b < r.b;
        }
*/

    } L[N], tmp[N];

    //counting sort
    inline int cSort(int idx) {
        int n = max(300, len + 2), sum = 0;
        for(int i = 0; i < n; i++) cum[i] = 0;
        for(int i = 0; i < len; i++) {
            if(idx) cum[L[i].a + 1]++;
            else cum[L[i].b + 1]++;
        }
        for(int i = 0; i < n; i++) sum += cum[i], cum[i] = sum - cum[i];
        for(int i = 0; i < len; i++) {
            if(idx) tmp[cum[L[i].a + 1]++] = L[i];
            else tmp[cum[L[i].b + 1]++] = L[i];
        }
        for(int i = 0; i < len; i++) L[i] = tmp[i];
    }

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
            cSort(0);
            cSort(1);
            /* sort(L, L + len) */
            for(int i = 0; i < len; i++) 
                P[lg][L[i].c] = (i > 0 && L[i].a == L[i - 1].a && L[i].b == L[i - 1].b) ? P[lg][L[i - 1].c] : i;
        }
        lg--;
        for(int i = 0; i < len; i++) sa[i] = 0;
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

    // gives number of unique substrings
    long long numSubStrings() {
        long long cnt = ((long long) len * (len + 1)) / 2;
        for(int i = 1; i < len; i++) cnt -= lcp(sa[i], sa[i - 1]);
        return cnt;
    }
};