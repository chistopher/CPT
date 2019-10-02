
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
    vector<int> tree; // sum of interval for all nodes in segment tree
    // tree.resize(4*arr.size(), 0);
    // construct(0,0,arr.size(),arr);
    int construct(int idx, int l, int r, vector<int>& arr) {
        if(l==r) return 0; // empty node
        if(r-l==1) return tree[idx] = arr[l]; // leaf
        return tree[idx] = construct(2*idx+1,l,l+(r-l)/2,arr) + construct(2*idx+2,l+(r-l)/2,r,arr);
    }
    int update(int idx, int l, int r, int index, int value) {
        if (index < l || r <= index) return tree[idx]; // index outside node segment
        if (r-l==1) return tree[idx] = value; // leaf
        return tree[idx] = update(2*idx+1,l,l+(r-l)/2,index,value) + update(2*idx+2,l+(r-l)/2,r,index,value);
    }
    int query(int idx, int l, int r, int ql, int qr) { // sum of values in arr[l..r); (exclusive)
        if (qr <= l || r <= ql) return 0; // node outside of range
        if (ql <= l && r <= qr) return tree[idx]; // node fully in range
        return query(2*idx+1,l,l+(r-l)/2,ql,qr) + query(2*idx+2,l+(r-l)/2,r,ql,qr);
    }
};
