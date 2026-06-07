#include "../include/HashTableChainingList.h"
#include <cmath>
#include <stdexcept>

HashTableChainingList::HashTableChainingList(int initialCapacity) {
    
    capacity = initialCapacity;
    table = new ListNode*[capacity];

    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

HashTableChainingList::~HashTableChainingList() {

    for (int i = 0; i < capacity; i++) {
        
        ListNode* current = table[i];

        while (current != nullptr) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }

    delete[] table;
}

int HashTableChainingList::hash(int key) const {
    return std::abs(key) % capacity;
}

void HashTableChainingList::insert(int key, int value) {

    int index = hash(key);
    ListNode* current = table[index];

    while (current != nullptr) {
        
        if (current->key == key) {
            current->value = value;
            return;
        }

        current = current->next;
    }

    ListNode* newNode = new ListNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;
}

void HashTableChainingList::remove(int key) {

    int index = hash(key);
    ListNode* current = table[index];
    ListNode* prev = nullptr;

    while (current != nullptr && current->key != key) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        throw std::runtime_error("Key not found");
    }

    if (prev == nullptr) {
        table[index] = current->next;
    } 
    else {
        prev->next = current->next;
    }

    delete current;
}