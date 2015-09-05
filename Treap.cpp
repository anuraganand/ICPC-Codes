struct node {
    int key, prior, size;
    node * l, * r;
    node() {}
    node() (int k, int p) : key(k), prior(p), l(NULL), r(NULL) {}

    inline void update() {
        size = 1 + l->size + r->size;
    }
};

typedef node * pNode;

void split(pNode x, int key, pNode & l, pNode & r) {
    if(!x)
        l = r = NULL;
    else if(key < x->key) {
        split(x->l, key, l, x->l);
        r = x;
    } else {
        split(x->r, key, x->r, r);
        l = x;
    }

    if(x) {
        if(x->l) x->l->update();
        if(x->r) x->r->update();
        x->update();
    }
}

void insert(pNode & x, pNode y) {
    if(!x)
        x = y;
    else if(y->prior > x->prior) {
        split(x, y->key, y->l, y->r);
        x = y;
    } else {
        insert(y->key < x->key ? x->l : x->r, y);
    }

    if(x) {
        if(x->l) x->l->update();
        if(x->r) x->r->update();
        x->update();
    }
}

void merge(pNode & x, pNode l, pNode r) {
    if(!l or !r)
        x = l ? l : r;
    else if(l->prior > r->prior) {
        merge(l->r, l->r, r);
        x = l;
    } else {
        merge(r->l, l, r->l);
        x = r;
    }

    if(x) {
        if(x->l) x->l->update();
        if(x->r) x->r->update();
        x->update();
    }
}

void erase(pNode & x, int key) {
    if(!x) return;
    if(x->key == key)
        merge(x, x->l, x->r);
    else
        erase(key < x->key ? x->l : x->r, key);

    if(x) {
        if(x->l) x->l->update();
        if(x->r) x->r->update();
        x->update();
    }
}

pNode join(pNode l, pNode r) {
    if(!l or !r) return l ? l : r;
    if(l->prior < r->prior) swap(l, r);
    pNode lt, rt;
    split(r, l->key, lt, rt);
    l->l = join(l->l, lt);
    l->r = join(l->r, rt);

    if(x) {
        if(x->l) x->l->update();
        if(x->r) x->r->update();
        x->update();
    }

    return l;
}
