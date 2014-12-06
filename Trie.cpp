// Trie
// Insert, Query - O(logn)
// query and insert function needs to be changed according to need


#define CHILD_SIZE 200

int cntNode = 0;

struct Trie {
private:
    struct node {
        node * child[CHILD_SIZE];
        int cnt;

        node() {
            cntNode++;
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

        ~node() {
            for(int i = 0; i < CHILD_SIZE; ++i) {
                delete child[i];
            }
        }
    };

    node * root;


    void insert(node * cur, string s) {
        for(int i = 0; i < sz(s); ++i) {
            int curPos = (int)s[i];
            if(cur->child[curPos] == NULL) {
                cur->child[curPos] = new node();
            }
            cur = cur->child[curPos];
        }
    }
public:
    Trie() {
        cntNode = 0;
        root = new node();
    }

    ~Trie() {
        delete root;
    }

    void clear() {
        cntNode = 0;
        root = new node();
    }

    void insert(int num) {
        insert(root, num);
    }

    int query(int num) {
        return query(root, num);
    }
};