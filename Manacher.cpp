// O(n)
// length of odd palindrome centered at i = 2 * odd[i] + 1
// length of even palindrome centered at i and i - 1 = 2 * even[i]

#define N 100100
int odd[N], even[N];

void manacher(string s) {
    int n = (int)s.length();
    int l = 0, r = -1;

    // compute odd length palindromes centered at i
    for(int i = 0; i < n; i++) {
        int k = (i > r ? 0 : min(odd[l + r - i], r - i)) + 1;
        while(i + k < n && i - k >= 0 && s[i - k] == s[i + k]) k++;
        odd[i] = --k;
        if(i + k > r) l = i - k, r = i + k;
    }

    // compute even length palindromes centered at i and i - 1
    l = 0, r = -1;
    for(int i = 0; i < n; i++) {
        int k = (i > r ? 0 : min(even[l + r - i + 1], r - i + 1)) + 1;
        while(i + k - 1 < n && i - k >= 0 && s[i - k] == s[i + k - 1]) k++;
        even[i] = --k;
        if(i + k - 1 > r) l = i - k, r = i + k - 1;
    }
}