#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
public:
    int key;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insertNode(root, key);
        printAVL();
        cout << "Root=" << root->key << endl;
    }

    void remove(int key) {
        root = deleteNode(root, key);
        printAVL();
        cout << "Root=" << (root ? to_string(root->key) : "None") << endl;
    }

    void printAVL() {
        vector<pair<int, int>> nodes;
        inOrderTraversal(root, nodes);
        for (const auto& p : nodes) {
            cout << p.first << "(" << p.second << ") ";
        }
        cout << endl;
    }

private:
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(TreeNode* node) {
        if (node) {
            node->height = 1 + max(height(node->left), height(node->right));
        }
    }

    TreeNode* rightRotate(TreeNode* y) {
        cout << "Right rotate (" << y->key << ")" << endl;
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        cout << "Left rotate (" << x->key << ")" << endl;
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode* insertNode(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);
        if (key < node->key) {
            node->left = insertNode(node->left, key);
        } else {
            node->right = insertNode(node->right, key);
        }

        updateHeight(node);
        return balanceNode(node, key);
    }

    TreeNode* deleteNode(TreeNode* node, int key) {
        if (!node) return node;
        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {
            if (!node->left || !node->right) {
                TreeNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                TreeNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        updateHeight(node);
        return balanceNode(node, key);
    }

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current->left) current = current->left;
        return current;
    }

    TreeNode* balanceNode(TreeNode* node, int key) {
        int bf = balanceFactor(node);
        // Left heavy
        if (bf > 1 && key < node->left->key) {
            cout << "Imbalance at node: " << node->key << " - LL Case" << endl;
            return rightRotate(node);
        }
        if (bf > 1 && key > node->left->key) {
            cout << "Imbalance at node: " << node->key << " - LR Case" << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        // Right heavy
        if (bf < -1 && key > node->right->key) {
            cout << "Imbalance at node: " << node->key << " - RR Case" << endl;
            return leftRotate(node);
        }
        if (bf < -1 && key < node->right->key) {
            cout << "Imbalance at node: " << node->key << " - RL Case" << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inOrderTraversal(TreeNode* node, vector<pair<int, int>>& nodes) {
        if (!node) return;
        inOrderTraversal(node->left, nodes);
        nodes.push_back({node->key, balanceFactor(node)});
        inOrderTraversal(node->right, nodes);
    }
};

// Main function to demonstrate the AVL Tree operations
int main() {
    AVLTree tree;
    vector<int> values = {12, 9, 5, 11, 20, 15, 7, 3, 6, 27};

    for (int val : values) {
        cout << "Inserting " << val << "..." << endl;
        tree.insert(val);
    }

    cout << "\nDeleting 27..." << endl;
    tree.remove(27);

    cout << "\nDeleting 15..." << endl;
    tree.remove(15);

    return 0;
}

