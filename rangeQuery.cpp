// Range Query 
// O(nlogn) preprocessing, O(1) range query
// change op(x, y) to any associative function
// call init function before any query

const int N = 100100;
ll a[N];
ll dp[N][20];   // dp[i][j] stores function value of range of length 2^j starting from i
int logVal[N];  // value of floor of log2

ll gcd(ll x, ll y) {
    if(y == 0) return x;
    return gcd(y, x % y);
}

#define op(x, y) (gcd(x, y))

inline void init(int sz) {
    // initialize log table
    // in case of multiple test cases, use this just at the begining
    logVal[0] = -1;
    for(int i = 1; i < N; ++i) {
        logVal[i] = logVal[i - 1];
        if((i & (i - 1)) == 0) ++logVal[i];
    }

    for(int i = 0; i < sz; ++i) {
        dp[i][0] = a[i];
    }
    
    for(int j = 1; (1 << j) <= sz; j++) {
        for(int i = 0; i + (1 << j) <= sz; i++)
            dp[i][j] = op(dp[i][j - 1] , dp[i + (1 << (j - 1))][j - 1]);
    }
}

inline ll rangeQuery(int l, int r) {
    int k = logVal[r - l + 1];
    return op(dp[l][k], dp[r - (1 << k) + 1][k]);
}