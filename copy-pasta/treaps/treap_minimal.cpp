
using T=int;
struct Node {
    T x; //main key
    int prio; //heap key, secondary
    Node* left = nullptr;
    Node* right = nullptr;
    size_t size = 1;
    explicit Node (T x) : x(x), prio(rand()) {}
};

size_t size(Node* t) { return t ? t->size : 0; }

void update(Node* t) {
    t->size = 1 + size(t->left) + size(t->right);
}

Node* merge(Node* left, Node* right) { // merges two treaps (order is important)
    if(!left || !right) return left ? left : right;
    if(left->prio < right->prio) {
        left->right = merge(left->right, right);
        update(left);
        return left;
    } else {
        right->left = merge(left, right->left);
        update(right);
        return right;
    }
}

pair<Node*,Node*> split(Node* t, T x) { // (left-)splits off all nodes smaller than x
    if(!t) return {nullptr, nullptr};
    if(t->x < x) {
        auto [smaller, larger] = split(t->right, x);
        t->right = smaller;
        update(t);
        return {t, larger};
    } else {
        auto [smaller, larger] = split(t->left, x);
        t->left = larger;
        update(t);
        return {smaller, t};
    }
}

// to get split_size (split off the first x nodes) take split and
// change if condition to '1+size(t->left) <= x' and do the first split at x-1-size(t->left)
// also don't forget to change recursive calls to split_size
