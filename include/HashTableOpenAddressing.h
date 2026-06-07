#ifndef HASHTABLEOPENADDRESSING_H
#define HASHTABLEOPENADDRESSING_H

#include <stdexcept>

enum class EntryState {
    EMPTY,
    OCCUPIED,
    DELETED
};

struct HashEntry {
    int key;
    int value;
    EntryState state;
    
    HashEntry() {
        key = 0;
        value = 0;
        state = EntryState::EMPTY;
    }
};

class HashTableOpenAddressing {
private:
    HashEntry* table;
    int capacity;
    int size;

    int hash(int key) const;
    void resize();

public:
    HashTableOpenAddressing(int initialCapacity = 16);
    ~HashTableOpenAddressing();

    void insert(int key, int value);
    void remove(int key);
};

#endif