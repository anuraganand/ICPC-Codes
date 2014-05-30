// Trie
// Insert, Query - O(logn)
// query and insert function needs to be changed according to need


#define CHILD_SIZE 2

struct Trie {
private:
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

        ~node() {
            for(int i = 0; i < CHILD_SIZE; ++i) {
                delete child[i];
            }
        }
    };

    node * root;


    void insert(node * cur, int num) {
        for(int pos = 31; pos >= 0; --pos) {
            int curBit = (num >> pos) & 1;
            if(cur->child[curBit] == NULL) {
                cur->child[curBit] = new node();
            }
            cur = cur->child[curBit];
        }
    }

    void query(node * cur, int num) {
        int ret = 0;
        for(int pos = 31; pos >= 0; --pos) {
            int curBit = (num >> pos) & 1;
            int canBit = curBit ^ 1;
            if(cur->child[canBit] != NULL) {
                canBit = curBit;
            }
            ret |= 1 << canBit;
            cur = cur->child[canBit];
        }
        return ret;
    }
public:
    Trie() {
        root = NULL;
    }

    ~Trie() {
        delete root;
    }

    void clear() {
        root = NULL;
    }

    void insert(int num) {
        insert(root, num);
    }

    int query(int num) {
        return query(root, num);
    }
};