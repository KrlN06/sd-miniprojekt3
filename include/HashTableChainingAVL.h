#ifndef HASHTABLECHAININGAVL_H
#define HASHTABLECHAININGAVL_H

#include <stdexcept>
#include <algorithm>

struct AVLNode {
    int key;
    int value;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int k, int v) {
        key = k;
        value = v;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class HashTableChainingAVL {
private:
    AVLNode** table;
    int capacity;

    int hash(int key) const;
    
    int height(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* minValueNode(AVLNode* node);
    
    AVLNode* insertAVL(AVLNode* node, int key, int value);
    AVLNode* removeAVL(AVLNode* node, int key, bool& isRemoved);
    void destroyTree(AVLNode* node);
    AVLNode* copyTree(AVLNode* node);

public:
    HashTableChainingAVL(int initialCapacity = 16);
    HashTableChainingAVL(const HashTableChainingAVL& other);
    HashTableChainingAVL& operator=(const HashTableChainingAVL& other);
    ~HashTableChainingAVL();

    void insert(int key, int value);
    void remove(int key);
};

#endif