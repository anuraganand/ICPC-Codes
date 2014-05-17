#define MAXN 101000

/* z[i] denotes the length of the LCP of s[0..n-1] and s[i..n-1]. */
struct z_algorithm
{
    int z[MAXN];
    int n;

    void construct(char * s)
    {
        n=strlen(s);
        int l=0,r=0;
        z[0]=n;
        for(int i=1;i<n;i++)
        {
            if(i>r)
            {
                l=r=i;
                while(r<n&&arr[r]==arr[r-i]) r++;
                z[i]=r-l;
                r--;
            }
            else
            {
                if(z[i-l]<r-i+1) z[i]=z[i-l];
                else
                {
                    l=i;
                    while(r<n&& arr[r]==arr[r-i])r++;
                    z[i]=r-l;
                    r--;
                }
            }
        }
    }
};