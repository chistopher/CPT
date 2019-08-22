
// iterative version from https://codeforces.com/blog/entry/18051
struct SegmentTree {
    explicit SegmentTree(vector<int>& arr) {
        m_n = arr.size();
        m_tree.resize(2*m_n, 0);
        // construct base values
        for (int i = 0; i < m_n; ++i)
            m_tree[m_n + i] = arr[i];
        //build tree
        for (int i = m_n - 1; i > 0; --i) m_tree[i] = m_tree[i<<1] + m_tree[i<<1|1];
    }

    void modify(int p, int value) {  // set value at position p
        for (m_tree[p += m_n] = value; p > 1; p >>= 1) m_tree[p>>1] = m_tree[p] + m_tree[p^1];
    }

    int query(int l, int r) {  // sum on interval [l, r)
        int res = 0;
        for (l += m_n, r += m_n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += m_tree[l++];
            if (r&1) res += m_tree[--r];
        }
        return res;
    }

    int m_n;
    vector<int> m_tree;
};

// segment tree adapted from https://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range
struct SegmentTree {

    struct Node { // represents a segment
        int index, begin, end; // data member
        int mid() { return begin + (end-begin)/2; };
        Node rightChild() { return {2*index+1, begin, mid()}; };
        Node leftChild() { return {2*index+2, mid()+1, end}; };
    };

    explicit SegmentTree(const vector<int>& arr) : n(arr.size()) {
        // size of tree is 2*x – 1 where x is smallest power of 2 greater than n
        tree = vector<int>(4*n);
        construct(arr, {0, 0, n-1});
    }

    int construct(const vector<int>& arr, Node node) {
        if (node.begin == node.end)
            tree[node.index] = arr[node.begin];
        else
            tree[node.index] = construct(arr, node.leftChild()) + construct(arr, node.rightChild()); // COMBINE
        return tree[node.index];
    }

    // sum of values in arr[l..r]; (inclusive)
    int query(int left, int right) { return query(left, right, {0, 0, n - 1}); }
    int query(int left, int right, Node node) {
        // node is completely in range
        if (left <= node.begin && right >= node.end) return tree[node.index];
        // node is outside of range
        if (node.end < left || node.begin > right) return 0; // NEUTRAL ELEMENT
        // node and range overlap
        return query(left, right, node.leftChild()) + query(left, right, node.rightChild()); // COMBINE
    }

    void update(int index, int value) { update(index, value, {0, 0, n-1}); }
    int update(int index, int value, Node node) {
        // index outside node segment
        if (index < node.begin || index > node.end) return tree[node.index];
        // index in node segment -> update node and children
        if (node.begin == node.end) // leaf
            tree[node.index] = value;
        else // parent of changed leaf
            tree[node.index] =
                    update(index, value, node.leftChild()) +
                    update(index, value, node.rightChild());
        return tree[node.index];
    }

    int n; // size of input array
    vector<int> tree; // sum of interval for all nodes in segment tree
};
