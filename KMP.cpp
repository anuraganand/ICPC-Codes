/*
    KMP string matching. O(n)
*/

#define NN 100100

int F[NN];

void computeFailure(char T[], int m) { // m is the length of T
    int i = 1,j = 0;
    F[0] = 0;
    while(i < m) {
        while(j < m && T[i] == T[j]) {
            ++j; F[i] = j; ++i;
        }
        if(i == m) break;
        if(j == 0) {
            F[i] = 0;
            ++i;
        } else {
            j = F[j-1];
        }
    }
}

int KMP(const string & S,char T[]) {  // search T in S
    int n = S.length();
    int m = strlen(T);
    int cnt = 0;
    if(m > n) return 0;
    computeFailure(T, m);
    int i = 0, j = 0;
    while((i-j) <= n - m) {
        while(j < m && S[i] == T[j]) {
          ++j; ++i;
        }
        if(j == m) cnt++;        // match found
        if(j == 0) ++i;
        else j = F[j-1];
    }
    return cnt;
}