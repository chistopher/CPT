
// map implemented as a treap
template<typename K, typename V>
class Map {
public:

    // access elements (non-existing keys are created with default value)
    V& operator[](const K& key) {
        auto node = find(m_root, key);
        if(!node) { // insert
            node = new Node(key);
            auto p = split(m_root, key);
            m_root = merge(p.first, node);
            m_root = merge(m_root, p.second);
        }
        return node->v;
    }

    void remove(const K& key) {
        if(!contains(key)) return;
        auto p = split(m_root, key);
        auto q = split_size(p.first, p.first->size - 1); // remove last element
        delete q.second;
        m_root = merge(q.first, p.second);
    }

    template<typename F> // F is function taking arguments of type K and V
    void forEach(const F& func) const {
        _forEach(m_root, func);
    }

    size_t size() { return m_root ? m_root->size : 0; }
    bool empty() { return size() == 0; }
    bool contains(const K& x) { return find(m_root, x); }

protected:
    struct Node {
        K x; //main key
        V v; // value
        int y; //heap key, secondary
        Node* left = nullptr;
        Node* right = nullptr;
        size_t size = 1;
        //T minimum; // OR OTHER STATISTICS
        explicit Node (K x, V v = V()) : x(x), y(rand()) {}
    };

    Node* m_root = nullptr;

    void update(Node* t) {
        t->size = 1;
        for(auto child : {t->left, t->right})
            if(child)
                t->size += child->size;
    }

    Node* merge(Node* a, Node* b) {
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

    pair<Node*, Node*> split(Node* t, const K& x) {
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

    std::pair<Node*, Node*> split_size(Node* t, size_t x) {
        if(t == nullptr) return {nullptr, nullptr};
        auto left_size = (t->left ? t->left->size : 0);
        if(1 + left_size <= x) {
            auto p = split_size(t->right, x - 1 - left_size);
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

    Node* find(Node* t, const K& key) {
        if(!t) return nullptr;
        if(t->x == key) return t;
        return find(t->x < key ? t->right : t->left, key);
    }

    template<typename F>
    void _forEach(const Node* t, const F& func) const {
        if(!t) return;
        _forEach(t->left, func);
        func(t->x, t-> v);
        _forEach(t->right, func);
    }
};
