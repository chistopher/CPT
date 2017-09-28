
//NOTE: This version of the dsf also tracks the size of each element

template<typename _V>
class DSF{
public:
    template<typename _Value>
    class _Element {
    public:
        _Element() : value() , size(1), rank(0) {
            parent = this;
        }

        size_t getSize() const {
            return size;
        }

        _Value value;
        size_t size;

        _Element* root() {
            return this->rootAndShrink(0);
        }

        bool operator <<(_Element& child) {
            _Element* myRoot = this->root();
            _Element* theirRoot = child.root();
            if(myRoot != theirRoot) {
                if(myRoot->rank >= theirRoot->rank){
                    myRoot->adopt(theirRoot);
                    //theirRoot->parent = myRoot;
                    if(myRoot->rank == theirRoot->rank)
                        myRoot->rank++;
                } else if (myRoot->rank < theirRoot->rank) {
                    theirRoot->adopt(myRoot);
                    //myRoot->parent = theirRoot;
                }
                return true;
            } else {
                return false;
            }
        }

    protected:
        _Element* rootAndShrink(size_t size) {
            if(this->parent != this) {
                _Element* root = this->parent->rootAndShrink(this->size);
                this->size -= size;
                if(root != parent) {
                    this->parent = root;
                }
                return root;
            } else {
                return this;
            }
        }

        void adopt(_Element* child) {
            child->parent = this;
            this->size += child->size;
        }

        _Element* parent;
        size_t rank;
    };

    typedef _Element<_V> Element;

    explicit DSF(size_t size) : size(size) {
        elements = new Element[size];
    }

    virtual ~DSF() {
        delete[] elements;
    }

    size_t getSize() const {
        return size;
    }

    Element& operator [](size_t index) const {
        return elements[index];
    }

protected:
    Element* elements;
    size_t size;
};