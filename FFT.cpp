#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair <int,int> pii;
typedef vector <int> vi;

#define rep(i, n) for(int i = 0; i < (n); ++i)
#define forn(i, a, b) for(int i = (a); i < (b); ++i)
#define ford(i, a, b) for(int i = (a); i >= (b); --i)
#define fore(i, a, b) forn(i, a, b + 1)

#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(c) c.begin(), c.end()
#define mset(a, v) memset(a, v, sizeof(a))
#define sz(a) ((int)a.size())

#define gi(x) scanf("%d", &x)
#define pis(x) printf("%d ", x)
#define pin(x) printf("%d\n", x)
#define pnl printf("\n")
#define dbn cerr << "\n"
#define dbg(x) cerr << #x << " : " << (x) << " "
#define dbs(x) cerr << (x) << " "

#define foreach(c, it) for(__typeof(c.begin()) it = c.begin(); it != c.end(); ++it)

int key(int k,int p) {
    p = 1 << (p-1);
    int r = 0;
    while(k) {
        if(k & 1) r += p;
        p >>= 1;
        k >>= 1;
    }
    return r;
}


void FFT(vector < CD > &A,int s) {
    int n = A.size();
    int p = 0;
    while(n > 1) p++,n >>= 1;
    n = 1 << p;
    vector < CD > aa(A);
    rep(i,0,n) A[key(i,p)] = aa[i];
    CD w,wn,t,u;
    int m,r;
    rep(i,1,p+1) {
        m = 1 << i;
        r = m >> 1;
        wn = CD( cos(s*2*M_PI/(double)m), sin(s*2*M_PI/(double)m) );
        w = 1.0;
        rep(j,0,r){
            for(int k = j; k < n ; k += m) {
                t = w * A[k + r];
                u = A[k];
                A[k] = u + t;
                A[k + r] = u - t;
            }
            w = w * wn;
        }
    }
    if(s==-1){
    for(int i = 0;i<n;++i)
         A[i] /= (double)n;
    }
}

vector< CD > Multiply(vector< CD > &P, vector< CD > &Q){
    int n = P.size()+Q.size();
    int p = 1;
    while(p < n) p <<= 1;
    n = p;
    P.resize(n,0);
    Q.resize(n,0);
    FFT(P,1);
    FFT(Q,1);
    vector< CD > R;
    for(int i=0;i<n;i++) R.push_back(P[i]*Q[i]);
    FFT(R,-1);
    return R;
}

int main() {
    return 0;
}