#ifndef AVLTREE_H
#define AVLTREE_H
template <class K, class T>
class AVLTree {
private:
    int currentSize;
    class Node {
    public:
        Node* left; Node* right;
        K key;
        T value;
        int height;
        Node (K k, T v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
        friend class AVLTree;
    };
    friend class Node;
    Node* root;
private:
    int nodeHeight(Node* node)
    {
        return node ? node->height : 0;
    }

    void updateNodeHeight(Node* node)
    {
        if (node) node->height = 1 + std::max(nodeHeight(node->left), nodeHeight(node->right));
    }

    int balanceFactor(Node* node)
    {
        return node ? nodeHeight(node->left) - nodeHeight(node->right) : 0;
    }

    Node* rightRotate (Node* y)
    {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateNodeHeight(y);
        updateNodeHeight(x);
        return x;
    }
    Node* leftRotate (Node* x)
    {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }
    Node* insertNode (Node* node, K key, T value, bool &inserted)
    {
        if (!node) { inserted = true; return new Node(key, value); }
        if (key < node->key) node->left = insertNode(node->left, key, value, inserted);
        else if (key > node->key) node->right = insertNode(node->right, key, value, inserted);
        else { node->value = value; return node; }

        updateNodeHeight(node);
        int bf = balanceFactor(node);
        // Left Left
        if (bf > 1 && key < node->left->key) return rightRotate(node);
        // Left Right
        if (bf > 1 && key > node->left->key) { node->left = leftRotate(node->left); return rightRotate(node); }
        // Right Right
        if (bf < -1 && key > node->right->key) return leftRotate(node);
        // Right Left
        if (bf < -1 && key < node->right->key) { node->right = rightRotate(node->right); return leftRotate(node); }

        return node;
    }
    Node* minValueNode (Node* node)
    {
        Node* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    Node* removeNode (Node* root, K key, bool &removed)
    {
        if (root == nullptr) return root;

        if (key < root->key) root->left = removeNode(root->left, key, removed);
        else if (key > root->key) root->right = removeNode(root->right, key, removed);
        else {
            removed = true;
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) { delete root; return nullptr; }
                else { *root = *temp; delete temp; }
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = removeNode(root->right, temp->key, removed);
            }
        }

        updateNodeHeight(root);
        int bf = balanceFactor(root);
        // Left heavy
        if (bf > 1 && balanceFactor(root->left) >= 0) return rightRotate(root);
        if (bf > 1 && balanceFactor(root->left) < 0) { root->left = leftRotate(root->left); return rightRotate(root); }
        // Right heavy
        if (bf < -1 && balanceFactor(root->right) <= 0) return leftRotate(root);
        if (bf < -1 && balanceFactor(root->right) > 0) { root->right = rightRotate(root->right); return leftRotate(root); }

        return root;
    }
    void clearNode (Node* node)
    {
        if (node) {
            clearNode(node->left);
            clearNode(node->right);
            delete node;
        }
    }
    // replaced recursive height with stored heights; see nodeHeight/updateNodeHeight
    Node* lowerboundNode (Node* node, K key)
    {
        if (!node) return nullptr;
        if (node->key >= key) {
            Node* leftLowerbound = lowerboundNode(node->left, key);
            return leftLowerbound ? leftLowerbound : node;
        } else {
            return lowerboundNode(node->right, key);
        }
    }
    Node* upperboundNode (Node* node, K key)
    {       
        if (!node) return nullptr;
        if (node->key > key) {
            Node* leftUpperbound = upperboundNode(node->left, key);
            return leftUpperbound ? leftUpperbound : node;
        } else {
            return upperboundNode(node->right, key);
        }
    }
public:
    AVLTree () 
    {
        this->currentSize=0;
        this->root=nullptr;
    }
    ~AVLTree ()
    {
        clear();
    }
    void push (K key, T value)
    {
        bool inserted = false;
        this->root = insertNode(this->root, key, value, inserted);
        if (inserted) this->currentSize++;
    }
    bool find (const K& key, T& outValue)
    {
        Node* current = this->root;
        while (current) {
            if (key == current->key) { outValue = current->value; return true; }
            current = key < current->key ? current->left : current->right;
        }
        return false;
    }
    void remove (K key)
    {
        bool removed = false;
        this->root = removeNode(this->root, key, removed);
        if (removed) --this->currentSize;
    }
    int size() const
    {
        return this->currentSize;
    }
    void clear ()
    {
        clearNode(this->root);
        this->root = nullptr;
        this->currentSize = 0;
    }
    int height ()
    {
        return nodeHeight(this->root);
    }
    Node* lowerbound (K key)
    {
        return lowerboundNode(this->root, key);
    }
    Node* upperbound (K key)
    {
        return upperboundNode(this->root, key);
    }
};

#endif
