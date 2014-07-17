/* Longest increasing subsequence O(n log n) */
/* Taken from Topcoder SRM 623 Div 1 - 450 ptr solution */

int LIS(int n, const vector<int> & x)
{
    int M[n+1];
    int L = 0;
    for (int i = 0; i < n; i++) {
        // Binary search for the largest positive j ≤ L
        // such that X[M[j]] < X[i]
        int lo = 1;
        int hi = L;
        while (lo <= hi) {
            int mid = (lo + hi )/2;
            if (x[M[mid]] <= x[i]) {
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
         
        // After searching, lo is 1 greater than the
        // length of the longest prefix of X[i]
        int newL = lo;
         
        if (newL > L) {
            // If we found a subsequence longer than any we've
            // found yet, update M and L
            M[newL] = i;
            L = newL;
        } else if (x[i] <= x[M[newL]]) {
            // If we found a smaller last value for the
            // subsequence of length newL, only update M
            M[newL] = i;
        }
    }
    return L;
}