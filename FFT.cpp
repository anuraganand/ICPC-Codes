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

// change long double in typedef to double if TLE
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);

void fft(vector <complex_t>& a, int s = 1) {
    int n = (int)a. size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1 ;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * s * PI / len;
        complex_t wlen(cos(ang), sin(ang));
        for (int i = 0 ; i < n ; i += len) {
            complex_t w(1);
            for (int j = 0 ; j < len / 2 ; ++ j) {
                complex_t u = a[i + j] ,  v = a[i + j + len / 2] * w ;
                a[i + j] = u + v ;
                a[i + j + len / 2] = u - v ;
                w *= wlen ;
            }
        }
    }
    if (s == -1)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

typedef long long ll;
// change ll to complex_t if needed
vector <ll> multiply (const vector<ll>& a, const vector<ll>& b) {
    vector <complex_t> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa), fft(fb);

    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];

    fft (fa, -1);

    vector <ll> res(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = (ll) (fa[i].real() + 0.5);
    return res;
}

int main() {
    return 0;
}