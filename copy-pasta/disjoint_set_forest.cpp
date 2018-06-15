
struct DSF_Tree {
    DSF_Tree* parent = this;
    int id; // + more data

    DSF_Tree(int _id) : id(_id) {}

    DSF_Tree* find(DSF_Tree* tree) {
        if(tree->parent != tree)
            tree->parent = find(tree->parent);
        return tree->parent;
    }

    void join(DSF_Tree* first, DSF_Tree* second) {
        auto root1 = find(first);
        auto root2 = find(second);
        if(root1->id != root2->id)
            root1->parent = root2;
    }
};
