
#include "MoveStack.h"
#include "Move.h"   // Move định nghĩa đầy đủ ở đây

// Constructor
MoveStack::MoveStack(int cap) {
    capacity = cap;
    data = new Move[capacity];
    topIndex = -1;
}

// Destructor
MoveStack::~MoveStack() {
    delete[] data;
}

bool MoveStack::isEmpty() const {
    return topIndex == -1;
}

bool MoveStack::isFull() const {
    return topIndex == capacity - 1;
}

void MoveStack::push(const Move& m) {
    if (isFull()) return; // hoặc mở rộng capacity nếu bạn muốn
    data[++topIndex] = m;
}

Move MoveStack::pop() {
    if (isEmpty()) return {}; 
    return data[topIndex--];
}

Move MoveStack::peek() const {
    if (isEmpty()) return {};
    return data[topIndex];
}

void MoveStack::clear() {
    topIndex = -1;
}

