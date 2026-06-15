#ifndef HASHTABLECHAININGLIST_H
#define HASHTABLECHAININGLIST_H

#include <stdexcept>

struct ListNode {
    int key;
    int value;
    ListNode* next;
    
    ListNode(int k, int v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTableChainingList {
private:
    ListNode** table;
    int capacity;

    int hash(int key) const;

public:
    HashTableChainingList(int initialCapacity = 16);
    HashTableChainingList(const HashTableChainingList& other);
    HashTableChainingList& operator=(const HashTableChainingList& other);
    ~HashTableChainingList();

    void insert(int key, int value);
    void remove(int key);
};

#endif