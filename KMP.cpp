/*
    KMP string matching. O(n)
*/

#define LEN 100100

int F[LEN]; // Failure function. F[i] denotes the length of the longest prefix of x which is also a PROPER suffix of x[0..i].

void kmp(string x) // Computes Failure function
{
    int len = 0,i=1;
    F[0] = 0;
    while(i < x.length())
    {
        if(x[i] == x[len])
        {
            len++;
            F[i] = len;
            i++;
        }
        else
        {
            if( len != 0 ) len = F[len-1];
            else
            {
                F[i] = 0;
                i++;
            }
        }
    }
}