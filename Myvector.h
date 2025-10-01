#pragma once
#include <stdexcept>

template <typename T>
class MyVector {
    T* data;
    int capacity;
    int length;

public:
    MyVector(int cap = 10) : capacity(cap), length(0) {
        data = new T[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (length == capacity) {
            capacity *= 2;
            T* newData = new T[capacity];
            for (int i = 0; i < length; i++) newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        data[length++] = value;
    }

    int size() const { return length; }

    void clear() { length = 0; }

    T& operator[](int i) {
        if (i < 0 || i >= length) throw std::out_of_range("Index out of range");
        return data[i];
    }

    const T& operator[](int i) const {
        if (i < 0 || i >= length) throw std::out_of_range("Index out of range");
        return data[i];
    }
};
