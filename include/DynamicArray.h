//
// Created by Karol Nalepa on 04/05/2026.
//

#ifndef PROJEKT_2_DYNAMICARRAY_H
#define PROJEKT_2_DYNAMICARRAY_H

#include <iostream>

template<typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void resize() {
        int newCapacity = 2 * capacity;
        T* newData = new T[newCapacity];

        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : size(0), capacity(1) {
        data = new T[capacity];
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray(const DynamicArray& other) {
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    void push_back(T value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void pop_back() {
        if (size == 0) {
            std::cout << "Pop error: array is empty\n";
            return;
        }
        size--;
    }

    void removeSwap(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Remove error: index out of range\n";
            return;
        }
        data[index] = data[size - 1];
        size--;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    void clear() {
        size = 0;
    }
};

#endif //PROJEKT_2_DYNAMICARRAY_H
