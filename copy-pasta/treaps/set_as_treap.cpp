
// set implemented as a treap
template<typename T>
class Set {
public:
    void insert(T x) {
        if(contains(x)) return;
        auto n = new Node(x);
        auto p = split(m_root, x);
        m_root = merge(p.first, n);
        m_root = merge(m_root, p.second);
    }

    void remove(T x) {
        if(!contains(x)) return;
        auto p = split(m_root, x);
        auto q = split_size(p.first, p.first->size - 1); // remove last element
        delete q.second;
        m_root = merge(q.first, p.second);
    }

    template<typename F>
    void forEach(const F& func) const {
        _forEach(m_root, func);
    }

    size_t size() { return m_root ? m_root->size : 0; }
    bool empty() { return size() == 0; }
    bool contains(T x) { return find(m_root, x); }

protected:
    struct Node {
        T x; //main key
        int y; //heap key, secondary
        Node* left = nullptr;
        Node* right = nullptr;
        size_t size = 1;
        //T minimum; // OR OTHER STATISTICS
        explicit Node (T x) : x(x), y(rand()) {}
    };

    Node* m_root = nullptr;

    void update(Node* t) {
        // add more aggregate values here
        t->size = 1;
        for(auto child : {t->left, t->right})
            if(child) {
                t->size += child->size;
            }
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

    pair<Node*, Node*> split(Node* t, T x) {
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

    Node* find(Node* t, T key) {
        if(!t) return nullptr;
        if(t->x == key) return t;
        return find(t->x < key ? t->right : t->left, key);
    }

    template<typename F>
    void _forEach(const Node* t, const F& func) const {
        if(!t) return;
        _forEach(t->left, func);
        func(t->x);
        _forEach(t->right, func);
    }
};
