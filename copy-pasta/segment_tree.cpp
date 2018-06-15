
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
