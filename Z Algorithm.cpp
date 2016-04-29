// z[i] gives the maximum length of substring starting from i which is a prefix
// maintain l and r which gives the maximum prefix substring last found
// if i > r start fresh
// else compare with z[i - l]
// if(z[i - l] < r - i + 1) z[i] = z[i - l]
// else start fresh

#define N 100100
int z[N];

void calcZ(string s) {
    int n = (int)s.length();
    z[0] = n;
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i > r) {
            l = r = i;
            while(r < n && s[r - l] == s[r]) r++;
            z[i] = r - l; r--;
        } else {
            int k = i - l;
            if(z[k] < r - i + 1) z[i] = z[k];
            else {
                l = i;
                while(r < n && s[r - l] == s[r]) r++;
                z[i] = r - l; r--;
            }
        }
    }
}