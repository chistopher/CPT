
// NOT FUNCTIONING!!!

#import <vector>

template<typename value_type>
class hollow_heap;

class tree {
public:
    class edge;
    class node {
    public:
        bool marked1 = false;
        bool marked2 = false;
        std::list<edge*> edges;
        hollow_heap<node>* heap = nullptr;
    };
    class edge {
    public:
        node* node;
        unsigned int weight;
    };
    node* nodes;
    edge* edges;

    tree(size_t size) {
        nodes = new node[size];
        edges = new edge[size - 1];
    }
    virtual ~graph() {
        delete[] nodes;
        delete[] edges;
    }
};

template<typename value_type>
struct hollow_heap {
    typedef hollow_heap<value_type> heap;
    value_type* value;
    long long key;
    heap* child;
    heap* next;
    heap* second;
    int rank;

};

typedef tree::node node;
typedef hollow_heap<node> nheap;

template <typename vt>
void add_child(hollow_heap<vt>* parent, hollow_heap<vt>* child) {
    child->next = parent->child;
    parent->child = child;
}

nheap* make_node(node* value, long long key){
    nheap* u = new nheap();
    u->value = value;
    value->heap = u;
    u->child = nullptr;
    u->key = key;
    u->rank = 0;
    return u;
}

nheap* make_heap() {
    return nullptr;
}

template <typename vt>
hollow_heap<vt>* link(hollow_heap<vt>* v, hollow_heap<vt>* w) {
    if(v->key < w->key) {
        add_child(v, w);
        return v;
    } else {
        add_child(w, v);
        return w;
    }
}

template <typename vt>
hollow_heap<vt>* meld(hollow_heap<vt>* g, hollow_heap<vt>* h) {
    if(g == nullptr)
        return h;
    if(h == nullptr)
        return g;
    return link(g, h);
}

nheap* insert(node* n, long long key, nheap* heap) {
    return meld(make_node(n, key), heap);
}

template <typename vt>
vt* find_min(hollow_heap<vt>* heap) {
    if(heap == nullptr)
        return nullptr;
    return heap->value;
}

nheap* remove(node* item, nheap* heap) {
    item->heap->value = nullptr;
    item->heap->second = nullptr;
    item->heap = nullptr;
    //TODO: make this static or global in some form for more performance
    std::vector<nheap*> A(256);
    if(heap->value != nullptr)
        return heap;
    int maxr = 0;
    heap->next = nullptr;
    while(heap != nullptr) {
        nheap* w = heap->child;
        nheap* x = heap;
        heap = heap->next;
        while(w != nullptr) {
            nheap* u = w;
            w = w->next;
            if(u->value == nullptr) {
                if(u->second == nullptr) {
                    u->next = heap;
                    heap = u;
                } else {
                    if (u->second == x)
                        w = nullptr;
                    else
                        u->next = nullptr;
                    u->second = nullptr;
                }
            } else {
                while(A[u->rank] != nullptr) {
                    u = link(u, A[u->rank]);
                    A[u->rank] = nullptr;
                    u->rank++;
                }
                A[u->rank] = u;
                if (u->rank > maxr)
                    maxr = u->rank;
            }
        }
        delete x;
    }
    for (int i = 0; i <= maxr; ++i) {
        if(A[i] != nullptr) {
            if(heap != nullptr) {
                heap = link(heap, A[i]);
            } else {
                heap = A[i];
            }
            A[i] = nullptr;
        }
    }
    return heap;
}

nheap* remove_min(nheap* heap) {
    if(heap != nullptr)
        return remove(heap->value, heap);
    else
        return nullptr;
}

nheap* decrease_key(node* node, long long key, nheap* heap) {
    nheap* u = node->heap;
    if (u == heap) {
        u->key = key;
        return heap;
    }
    nheap* v = make_node(node, key);
    u->value = nullptr;
    if(u->rank > 2)
        v->rank = u->rank - 2;
    if(key > heap->key) {
        v->child = u;
        u->second = v;
    } else
        u->second = nullptr;
    return link(v, heap);
}

nheap* update(node* node, long long key, nheap* heap) {
    if(node->heap != nullptr) {
        if (node->heap->key > key) {
            return decrease_key(node, key, heap);
        } else {
            return heap;
        }
    } else {
        return insert(node, key, heap);
    }
}

char* getInputString(char* buffer) {
    fgets(buffer, BUFFER_SIZE, stdin);
    return buffer;
}
