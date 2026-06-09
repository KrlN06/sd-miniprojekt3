#include "../include/HashTableChainingAVL.h"
#include <cmath>
#include <stdexcept>

HashTableChainingAVL::HashTableChainingAVL(int initialCapacity) {

    // Initialize hash table capacity and allocate bucket array
    capacity = initialCapacity;
    table = new AVLNode*[capacity];

    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashTableChainingAVL::~HashTableChainingAVL() {

    // Destroy all AVL trees stored in hash table buckets
    for (int i = 0; i < capacity; i++) {
        destroyTree(table[i]);
    }

    // Release bucket array memory
    delete[] table;
}

void HashTableChainingAVL::destroyTree(AVLNode* node) {

    // Post-order traversal to safely delete all nodes
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int HashTableChainingAVL::hash(int key) const {
    // Map key to a bucket index
    return std::abs(key) % capacity;
}

int HashTableChainingAVL::height(AVLNode* node) {

    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

int HashTableChainingAVL::getBalance(AVLNode* node) {

    // Balance factor = left subtree height - right subtree height
    if (node == nullptr) {
        return 0;
    }

    return height(node->left) - height(node->right);
}

AVLNode* HashTableChainingAVL::rightRotate(AVLNode* y) {

    // Perform right rotation to restore AVL balance
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* HashTableChainingAVL::leftRotate(AVLNode* x) {

    // Perform left rotation to restore AVL balance
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* HashTableChainingAVL::minValueNode(AVLNode* node) {

    // Find the leftmost (smallest) node in the subtree
    AVLNode* current = node;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

AVLNode* HashTableChainingAVL::insertAVL(AVLNode* node, int key, int value) {

    // Standard BST insertion
    if (node == nullptr) {
        return new AVLNode(key, value);
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insertAVL(node->right, key, value);
    }
    else {
        node->value = value;
        return node;
    }

    // Update node height after insertion
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Check whether rebalancing is required
    int balance = getBalance(node);

    // AVL rotation cases: LL, RR, LR, RL
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void HashTableChainingAVL::insert(int key, int value) {
    // Compute bucket index and insert into corresponding AVL tree
    int index = hash(key);
    table[index] = insertAVL(table[index], key, value);
}

AVLNode* HashTableChainingAVL::removeAVL(AVLNode* node, int key, bool& isRemoved) {

    // Standard BST deletion
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = removeAVL(node->left, key, isRemoved);
    }
    else if (key > node->key) {
        node->right = removeAVL(node->right, key, isRemoved);
    }
    else {
        isRemoved = true;

        if (node->left == nullptr || node->right == nullptr) {

            AVLNode* temp = nullptr;

            if (node->left != nullptr) {
                temp = node->left;
            }
            else {
                temp = node->right;
            }

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            // Replace with inorder successor when node has two children
            AVLNode* temp = minValueNode(node->right);

            node->key = temp->key;
            node->value = temp->value;

            node->right = removeAVL(node->right, temp->key, isRemoved);
        }
    }

    if (node == nullptr) {
        return node;
    }

    // Update height and rebalance after deletion
    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void HashTableChainingAVL::remove(int key) {

    // Locate bucket and remove key from its AVL tree
    int index = hash(key);
    bool isRemoved = false;
    
    table[index] = removeAVL(table[index], key, isRemoved);
    
    if (isRemoved == false) {
        throw std::runtime_error("Key not found");
    }
}