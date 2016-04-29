#include <bits/stdc++.h>
using namespace std;

/*Main code begins now */
const int alpha = 26;
const int MAXN = 100040;


struct node {
    int next[alpha];    // link to palindrome by adding alpha , 0 = NULL (not a palindrome)
    int len;            // length of palindrome
    int link;           // link to largest suffix palindrome
    int half_link;      // link to largest palindrome of length <= len/2 
    int cnt;            // frequency of palindrome
    node(){
        memset(next,0,sizeof(next));
        cnt = 0;
    }
};
/*
    Palindrome Tree : Creates all Palindromic Substrings with their Frequencies in O(n)
    T[1] = palindrome of length -1(Root for trie of odd length)
    T[0] = palindrome of length 0(Root for trie of even length)
    cnt : Contains frequency of palindrome of that node
*/
struct PalindromeTree{
    string s;           // string to work on
    node T[MAXN];
    int ind;            // present index in Tree
    int last;           // index of last suffix
    int n;              // present index in string
    void initTree(string A) {
        s = A;
        int len = s.length();
        for(int i = 0;i<len+4;i++) {
            memset(T[i].next,0,sizeof(T[i].next));
            T[i].cnt = 0;
        }
        last = 0;
        T[1].len = -1,T[0].len = 0;         
        T[0].link = T[0].half_link = 1;
        ind = 2;
        n = 0;
    }
    int getLink(int cur){
        while(s[n] != s[n - T[cur].len - 1]) cur = T[cur].link;
        return cur;
    }
    void addLetter(int pos) {
        n = pos;
        int let = s[pos] - 'a';
        last = getLink(last);
        if(!T[last].next[let]){             // Need to create new node (else such palindrome already exists)
            T[ind].len = T[last].len + 2;
            T[ind].link = T[getLink(T[last].link)].next[let];
            T[ind].half_link = T[getLink(T[last].half_link)].next[let];
            while(T[T[ind].half_link].len * 2 > T[ind].len){
                T[ind].half_link = T[T[ind].half_link].link;
            }
            T[last].next[let] = ind++;
        }
        last = T[last].next[let];
        T[last].cnt++;
    }
};
PalindromeTree PT;

// Driver Program : http://www.spoj.com/problems/NUMOFPAL/
int main() {
    string line;
    cin>>line;

    PT.initTree(line);
    for (int i = 0; i < line.length(); i++) {
        PT.addLetter(i);           
    }

    long long ans = 0;
    for(int i = PT.ind-1;i>1;i--){
        int link = PT.T[i].link;
        PT.T[link].cnt += PT.T[i].cnt;    // update cnt for subtree rooted at i
    
        ans += PT.T[i].cnt;
    }
    
    printf("%lld\n",ans);
    
    return 0;
}   