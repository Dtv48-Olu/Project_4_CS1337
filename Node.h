#ifndef NODE_H
#define NODE_H

#include "Data.h"

class Node {
private:
    // Attributes
    Data Payload;
    Node* Next;

public:
    // Constructors
    Node() : Payload(), Next(nullptr) {}
    Node(Data obj) : Payload(obj), Next(nullptr) {}

    // Accessors
    Data getPayload() { return Payload; }
    Node* getNext() {return Next;}

    // Mutators
    void setNext(Node* newNext) {Next = newNext;}

    void setPayload(const Data& payloadData) {  // Use const reference to avoid copy
        Payload = payloadData;
    }
};

#endif // NODE_H
