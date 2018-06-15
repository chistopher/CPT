
// WORK IN PROGRESS

int i_rand() {
    return rand() - (RAND_MAX / 2);
}

template<typename V>
struct treap {
    V x; //main key
    int y; //heap key, secondary
    treap* left = nullptr;
    treap* right = nullptr;
    size_t size = 1;
    //V minimum; // OR OTHER STATISTICS
    //MASS MODIFICATION FLAGS THAT CAN BE PASSED DOWN THE TREE ON UPDATE
    // MAYBE PASS MODIFICATION DOWN ON SEARCH
    // visit modification / arrange modification
    treap (V x) : x(x), y(i_rand()) {}
};

template<typename V>
size_t size(treap<V>* t) {
    return t == nullptr ? 0 : t->size;
}

template<typename V>
void update(treap<V>* t) {
    if(t == nullptr)
        return;
    t->size = 1 + size(t->left) + size(t->right);
    //TODO: MIN / MAX Tracking, statistics of all children
    // VERY POWERFUL
}

//NOTE: ORDER IS IMPORTANT
template<typename V>
treap<V>* merge(treap<V>* a, treap<V>* b) {
    if(a == nullptr) return b;
    if(b == nullptr) return a;
    if(a->y < b->y) {
        a->right = merge(a->right, b); //NOTE: Might cause bug if wrong order
        update(a); //NOTE: MOD SIZE
        return a;
    } else {
        b->left = merge(a, b->left);//NOTE: Might cause bug if wrong order
        update(b); //NOTE: MOD SIZE
        return b;
    }
}

template<typename V>
std::pair<treap<V>*, treap<V>*> split(treap<V>* t, V x) {
    if(t == nullptr) return {nullptr, nullptr};
    if(t->x <= x) {
        auto p = split(t->right, x);
        t->right = p.first;
        update(t); //NOTE: MOD SIZE
        p.first = t;
        return p;
    } else {
        auto p = split(t->left, x);
        t->left = p.second;
        update(t); //NOTE: MOD SIZE
        p.second = t;
        return p;
    }
}

//Split the first size elements
template<typename V>
std::pair<treap<V>*, treap<V>*> split_size(treap<V>* t, size_t x) {
    if(t == nullptr) return {nullptr, nullptr};
    if(1 + size(t->left) <= x) {
        auto p = split_size(t->right, x - 1 - size(t->left));
        t->right = p.first;
        update(t); //NOTE: MOD SIZE
        p.first = t;
        return p;
    } else {
        auto p = split_size(t->left, x);
        t->left = p.second;
        update(t); //NOTE: MOD SIZE
        p.second = t;
        return p;
    }
}



//OPTIMIZATION: SEARCH; THEN INSERT
template<typename V>
treap<V>* insert(treap<V>* t, V x) {
    auto n = new treap<V>(x);
    auto p = split(t, x);
    t = merge(p.first, n);
    t = merge(t, p.second);
    return t;
}

//OPTIMIZATION: SEARCH; THEN REMOVE
template<typename V>
treap<V>* remove(treap<V>* t, V x) {
    auto p = split(t, x);
    auto q = split(p.first, x - 1); //NOTE: Might want to switch operator instead
    delete q.second;
    return merge(q.first, p.second);
}

template<typename V>
struct treap_range {
    treap<V>* front;
    treap<V>* middle;
    treap<V>* back;
};

template<typename V>
treap_range<V> range(treap<V> t, size_t start, size_t end) {
    auto a = split_size(t, start);
    auto b = split_size(a.second, end - start);
    return {a.first, b.first, b.second};
}

//NOTE: DEBUG: Recursive print or self check

template<typename V>
treap<V>* lower_bound(treap<V>* t, V x) {
    return split(t, x - 1).second; //NOTE: THEN LEFT MOST
}

//NOTE: PERSISTENT TREAP
template<typename V>
treap<V>* mergep(treap<V>* a, treap<V>* b) {
    if(a == nullptr)
        return b;
    if(b == nullptr)
        return a;
    if(a->y < b->y) {
        auto t = new treap<V>(*a);
        t->right = mergep(a->right, b);
        update(t); //NOTE: MOD SIZE
        return t;
    } else {
        auto t = new treap<V>(*b);
        t->left = mergep(a, b->left);
        update(t); //NOTE: MOD SIZE
        return t;
    }
}


template<typename V>
std::pair<treap<V>*, treap<V>*> splitp(treap<V>* t, V x) {
    if(t == nullptr)
        return {nullptr, nullptr};
    if(t->x <= x) {
        auto a = new treap<V>(*t);
        auto p = splitp(a->right, x);
        a->right = p.first;
        update(a); //NOTE: MOD SIZE
        p.first = a;
        return p;
    } else {
        auto a = new treap<V>(*t);
        auto p = splitp(a->left, x);
        a->left = p.second;
        update(a); //NOTE: MOD SIZE
        p.second = a;
        return p;
    }
}
