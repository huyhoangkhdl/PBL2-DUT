#ifndef MOVESTACK_H
#define MOVESTACK_H

#include "Move.h"   // ✅ thêm dòng này

class MoveStack {
private:
    Move* data;
    int capacity;
    int topIndex;
public:
    MoveStack(int cap = 256);
    ~MoveStack();

    bool isEmpty() const;
    bool isFull() const;
    void push(const Move& m);
    Move pop();
    Move peek() const;
    void clear();
};

#endif // MOVESTACK_H
