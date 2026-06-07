#include "../include/HashTableOpenAddressing.h"
#include <cmath>
#include <stdexcept>

HashTableOpenAddressing::HashTableOpenAddressing(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    table = new HashEntry[capacity];
}

HashTableOpenAddressing::~HashTableOpenAddressing() {
    delete[] table;
}

int HashTableOpenAddressing::hash(int key) const {
    return std::abs(key) % capacity;
}

void HashTableOpenAddressing::resize() {

    int oldCapacity = capacity;
    HashEntry* oldTable = table;

    capacity = capacity * 2;
    table = new HashEntry[capacity];
    size = 0;

    for (int i = 0; i < oldCapacity; i++) {
        
        if (oldTable[i].state == EntryState::OCCUPIED) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }

    delete[] oldTable;
}

void HashTableOpenAddressing::insert(int key, int value) {

    if (size >= capacity / 2) {
        resize();
    }

    int index = hash(key);
    int firstDeleted = -1;

    while (table[index].state != EntryState::EMPTY) {

        if (table[index].key == key && table[index].state == EntryState::OCCUPIED) {
            table[index].value = value; 
            return;
        }

        if (table[index].state == EntryState::DELETED && firstDeleted == -1) {
            firstDeleted = index;
        }

        index = (index + 1) % capacity;
    }

    if (firstDeleted != -1) {
        index = firstDeleted;
    }

    table[index].key = key;
    table[index].value = value;
    table[index].state = EntryState::OCCUPIED;
    size++;
}

void HashTableOpenAddressing::remove(int key) {

    int index = hash(key);
    int start = index;

    while (table[index].state != EntryState::EMPTY) {

        if (table[index].key == key && table[index].state == EntryState::OCCUPIED) {
            table[index].state = EntryState::DELETED;
            size--;
            return;
        }

        index = (index + 1) % capacity;

        if (index == start) {
            break;
        }
    }
    
    throw std::runtime_error("Key not found");
}