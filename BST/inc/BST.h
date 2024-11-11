#pragma GCC optimize(2) 
#include <iostream>
/// 临时性的异常类，用于表示树为空的异常
class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };

/**
 * @brief 二叉搜索树模板类
 * 
 * @tparam Comparable 模板参数，表示树中存储的元素类型
 */
template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}
    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}
    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }
    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable &findMin() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if (isEmpty())
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
        if (this != &rhs) {
            BinarySearchTree temp(rhs);
            std::swap(root, temp.root);
        }
        return *this;
    }

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode
    {
        Comparable element;  ///< 节点存储的元素
        BinaryNode *left;    ///< 左子节点指针
        BinaryNode *right;   ///< 右子节点指针
        int height;          ///< 节点的高度

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{ theElement }, left{ lt }, right{ rt }, height{ h } {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt, int h = 0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt }, height{ h } {}
    };

    BinaryNode *root;  ///< 树的根节点指针

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } else if (x > t->element) {
            return contains(x, t->right);
        } else 
        {
            return true;  
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);
            out << t->element << std::endl;
            printTree(t->right, out);
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void insert(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }

        balance(t);  
    }

    void insert(Comparable &&x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        }

        balance(t);  
    }

    void remove(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            return;  
        }

        if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {  
            t->element = detachMin(t->right)->element;  
            balance(t);  
        } else {  
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);  
    }

    BinaryNode *detachMin(BinaryNode *&t) {
        if (t == nullptr) {
            return nullptr;  
        } else if (t->left != nullptr) {
            return detachMin(t->left);  
        } else {
            BinaryNode *minNode = t; 
            t = t->right;  
            return minNode;  
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right), t->height};
    }

    
    void balance(BinaryNode * &t) {
        if (t == nullptr) return;

        updateHeight(t);  

       
        int balanceFactor = getBalance(t);

        if (balanceFactor > 1) {
            if (getBalance(t->left) < 0) {
                rotateLeft(t->left);  
            }
            rotateRight(t);  
        } else if (balanceFactor < -1) {
            if (getBalance(t->right) > 0) {
                rotateRight(t->right);  
            }
            rotateLeft(t); 
        }
    }

    int getBalance(BinaryNode *t) const {
        if (t == nullptr) return 0;
        return height(t->left) - height(t->right);
    }

   
    void updateHeight(BinaryNode *t) {
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

   
    int height(BinaryNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

 
    void rotateRight(BinaryNode * &t) {
        BinaryNode *leftChild = t->left;
        t->left = leftChild->right;
        leftChild->right = t;
        updateHeight(t);
        updateHeight(leftChild);
        t = leftChild;
    }

   
    void rotateLeft(BinaryNode * &t) {
        BinaryNode *rightChild = t->right;
        t->right = rightChild->left;
        rightChild->left = t;
        updateHeight(t);
        updateHeight(rightChild);
        t = rightChild;
    }
};
