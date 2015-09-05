// Trie
// Insert, Query - O(logn)
// query and insert function needs to be changed according to need



#define CHILD_SIZE 26

int cnt[2][26];

struct node {
    node * child[CHILD_SIZE];
    int cnt;

    node() {
        cnt = 0;
        for(int i = 0; i < CHILD_SIZE; ++i)
            child[i] = NULL;
    }

    void clear() {
        cnt = 0;
        for(int i = 0; i < CHILD_SIZE; ++i) {
            child[i] = NULL;
        }
    }
};

struct Trie {
private:
    void insert(node * cur, string s) {
        cur->cnt++;
        for(int i = 0; i < sz(s); ++i) {
            int curPos = s[i] - 'a';
            if(cur->child[curPos] == NULL) {
                cur->child[curPos] = new node();
                ++cntNodes;
            }
            cur = cur->child[curPos];
            cur->cnt++;
        }
    }

public:

    int cntNodes;
    node * root;

    Trie() {
        cntNodes = 0;
        root = new node();
    }

    ~Trie() {
        delete root;
    }

    void clear() {
        cntNodes = 0;
        root = new node();
    }
};