#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>

class Stack {
private:
    // Attributes
    Node* Head;

public:
    // Constructors
    Stack();
    Stack(Node* ptr);

    // Destructor
    // ~Stack();

    // Copy Constructor (implement to create deep copy)
    Stack(const Stack& otherStack);

    // Accessor
    Node* getHead() const { return Head; }

    // Mutators
    void setHead(Node* newHead) { Head = newHead; }

    // Overloaded '<<' operator for pushing
    Stack &operator<<(Node* value);

    // Overloaded '>>' operator for popping
    Stack& operator>>(Node*& value);

    // Friend ostream operator for printing (implement to print stack contents)
    friend std::ostream& operator<<(std::ostream&, const Stack&);

};

#endif // STACK_H
