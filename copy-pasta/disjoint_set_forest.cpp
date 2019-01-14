
struct DSF {
    DSF* parent = this;
    DSF* find() {
        if(parent != this)
            parent = parent->find();
        return parent;
    }
    void join(DSF& second) {
        find()->parent = second.find();
    }
};
