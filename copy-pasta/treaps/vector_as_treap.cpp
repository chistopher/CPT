
// this treap uses the index in a conceptual array as search key
// can be modified to maintain aggregated metrics
template<typename T>
class Vector {
public:
    void push_back(T x) {
        auto n = new Node(x);
        m_root = merge(m_root, n);
    }

    void remove(size_t index) { // we could just as easily remove a range [r,l] of nodes in O(log(n))
        if(index + 1 > size())
            throw std::out_of_range("index out of range");
        auto p = split_size(m_root, index+1); // p.2 is all after i
        auto q = split_size(p.first, index); // q.1 is all before i, q.2 = i
        assert(q.second->size == 1);
        delete q.second;
        m_root = merge(q.first, p.second);
    }

    T& operator[](size_t index){
        if(index + 1 > size())
            throw std::out_of_range("index out of range");
        return get(m_root, index)->x;
    }

    size_t size() { return m_root ? m_root->size : 0; }

    vector<T> toVector() {
        vector<T> ans;
        ans.reserve(size());
        push_in_vector(m_root, ans);
        return ans;
    }

protected:
    struct Node {
        T x; //main key
        int y; //heap key, secondary
        Node* left = nullptr;
        Node* right = nullptr;
        size_t size = 1;
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

    Node* get(Node* t, size_t index) {
        auto left_size = (t->left ? t->left->size : 0u);
        if(left_size == index)
            return t;
        if(left_size < index)
            return get(t->right, index - 1u - left_size);
        else
            return get(t->left, index);
    }

    void push_in_vector(Node* t, vector<T>& v){
        if(!t) return;
        push_in_vector(t->left, v);
        v.push_back(t->x);
        push_in_vector(t->right, v);
    }
};