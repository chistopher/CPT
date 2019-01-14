
#include <bits/stdc++.h>

#define rep(a, b)   for(int a = 0; a < (b); ++a)
#define debug(x)    clog << #x << " = " << x << endl;
#define all(a)      (a).begin(),(a).end()
#define endl        '\n'

using namespace std;


// priority Q implemented as a treap
// binary search tree for keys (not priority!!!)
// min prio is found via aggregation
template<typename T>
class PriorityQueue {
public:

    void insert(const T& x, long long prio) {
        if(contains(x)) return;
        auto n = new Node(x, prio);
        auto p = split(m_root, x);
        m_root = merge(p.first, n);
        m_root = merge(m_root, p.second);
    }

    void remove(const T& x) {
        if(!contains(x)) return;
        auto p = split(m_root, x);
        auto q = split_size(p.first, p.first->size - 1); // remove last element
        delete q.second;
        m_root = merge(q.first, p.second);
    }

    pair<T, long long> extract_min(){
        if(empty()) throw std::out_of_range("PQ empty");
        auto ans = make_pair(m_root->minimum->x, m_root->minimum->prio);
        remove(m_root->minimum->x);
        return ans;
    }

    void decrease_key(const T& x, long long prio) {
        auto node = find(m_root, x);
        if(node && node->prio > prio) {
            auto p = split(m_root, x); // split in (q1, q2=x, p2)
            auto q = split_size(p.first, p.first->size - 1); // remove last element
            q.second->prio = prio; // update prio
            m_root = merge(q.first, q.second); // merge it again
            m_root = merge(m_root, p.second);
        }
    }

    template<typename F> // F is function taking arguments of type T and long long
    void forEach(const F& func) const {
        _forEach(m_root, func);
    }

    size_t size() { return m_root ? m_root->size : 0; }
    bool empty() { return size() == 0; }
    bool contains(const T& x) { return find(m_root, x); }

protected:
    struct Node {
        T x; //main key
        long long prio;
        int y; //heap key, secondary
        Node* left = nullptr;
        Node* right = nullptr;
        size_t size = 1;
        Node* minimum = this;
        explicit Node (T x, long long p) : x(x), prio(p), y(rand()) {}
    };

    Node* m_root = nullptr;

    void update(Node* t) {
        // add more aggregate values here
        t->size = 1;
        t->minimum = t;
        for(auto child : {t->left, t->right})
            if(child) {
                t->size += child->size;
                if(child->minimum->prio < t->minimum->prio)
                    t->minimum = child->minimum;
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

    pair<Node*, Node*> split(Node* t, const T& x) {
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

    Node* find(Node* t, const T& key) {
        if(!t) return nullptr;
        if(t->x == key) return t;
        return find(t->x < key ? t->right : t->left, key);
    }

    template<typename F>
    void _forEach(const Node* t, const F& func) const {
        if(!t) return;
        _forEach(t->left, func);
        func(t->x, t->prio);
        _forEach(t->right, func);
    }
};


int main(int argc, char* argv[]) {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);

    // build
    srand(15);
    PriorityQueue<pair<int,int>> pq;
    rep(i,3) rep(j, 3) pq.insert({i,j}, i+j);
    // do operations
    pq.decrease_key({1, 2}, -5);
    pq.decrease_key({2, 1}, -4);
    pq.remove({0,0});

    cout << "size: " << pq.size() << endl;
    cout << "treap contents..." << endl;
    pq.forEach([](pair<int,int> x, long long prio){
        cout << x.first << " " << x.second << " " << prio << endl;
    });

    cout << endl << "extraction order..." << endl;
    while(not pq.empty()) {
        auto x = pq.extract_min();
        cout << x.first.first << " " << x.first.second << " " << x.second << endl;
    }

    return 0;
}
