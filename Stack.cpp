#include "Stack.h"
#include <iostream>

Stack::Stack() {
  // Set the head to nullptr for an empty stack
  Head = nullptr;
}

Stack::Stack(const Stack &otherStack) {
  // Handle the case of an empty list
  if (otherStack.Head == nullptr) {
    Head = nullptr;
    return;
  }

  // Create a new head node for the copied list
  Head =
      new Node(otherStack.Head->getPayload()); // Create a copy of the payload
  Node *current = otherStack.Head->getNext();
  Node *currentCopy = Head;
  while (current != nullptr) {
    // Create a new node for the copy and set its payload
    currentCopy->setNext(new Node(current->getPayload()));
    current = current->getNext();
    currentCopy = currentCopy->getNext();
  }
}

Stack::Stack(Node *ptr) {
  // Handle potential null pointer argument
  if (ptr == nullptr) {
    std::cout << "Stack::Stack(Node*): cannot construct from null pointer";
    return;
  }

  // Create a new node and set Head to point to it
  Head = ptr; // Create a new node with the same payload as the provided node
}

// Overloaded operator
// ... (other parts of the Stack class)

// Overloaded operator
Stack &Stack::operator>>(Node *&value) {
  if (Head == nullptr) {
    std::cout << "Cannot pop from an empty stack" << std::endl;
    value = nullptr; // Set the value to null
    return *this;
  }

  // Store the current head
  value = Head;
  // Move the head pointer to the next node
  Head = Head->getNext();
  // Set the next pointer of the popped node to null
  value->setNext(nullptr);

  return *this;
}

Stack &Stack::operator<<(Node *value) {
  if (value == nullptr) {
    std::cout << "Cannot push a null pointer onto the stack." << std::endl;
    return *this;
  }

  // Set the new node's `next` pointer to the current head
  value->setNext(Head);

  // Update the head pointer to point to the new node
  Head = value;

  return *this; // Return the current stack instance
}

std::ostream &operator<<(std::ostream &print, const Stack &stack) {
  Node *current = stack.getHead();

  // Handle the case of an empty list
  if (current == nullptr) {
    print << "Empty Stack";
    return print;
  }

  // We use a flag to determine if it's the first element
  bool isFirst = true;

  // Iterate through the list and print each payload
  while (current != nullptr) {
    if (!isFirst) {
      // Add a comma and space before each element except the first
      print << ", ";
    } else {
      // If it's the first node, set isFirst to false for the next iteration
      isFirst = false;
    }

    if (current->getPayload().getOperator() != '\0') {
      // Print the operator
      print << current->getPayload().getOperator();
    } else {
      // Print the operand
      print << current->getPayload().getOperand();
    }

    current = current->getNext();
  }
  return print;
}
