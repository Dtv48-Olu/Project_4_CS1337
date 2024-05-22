// Olutoye Odufowokan
#include <iostream>
#include "Stack.h"
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>
#include <iomanip>

using namespace std;

// Function prototypes
bool postfix(Stack&, Node*);
double evaluatePostfix(const string& postfix_expression, Stack& stack);

int main() // Driver program
{
    // Prompting the user
    cout << "Enter Filename" << endl;

    // Setting up file stream
    string fileName;
    cin >> fileName;
    ifstream inputfile(fileName);

    // Grabbing the expression
    string infix_expression;
    vector<string> postfix_vector;
    Stack theStack;
    while (getline(inputfile, infix_expression))
    {
        postfix_vector.clear(); // Clear the vector for a new expression
        for (int cursor = 0; cursor < static_cast<int>(infix_expression.length()); cursor++)
        {
            char c = infix_expression[cursor];
            if (isdigit(c) || c == '.')
            { // Handle numbers and decimals
                string number;
                while (cursor < static_cast<int>(infix_expression.length()) && (isdigit(infix_expression[cursor]) || infix_expression[cursor] == '.'))
                {
                    number += infix_expression[cursor];
                    cursor++;
                }

                cursor--; // Adjust cursor back
                postfix_vector.push_back(number);

            }
            else if (c == '(')
            { // Handle opening parenthesis
                Data dataPoint;
                dataPoint.setOperator(c);
                Node* newNode = new Node(dataPoint);
                theStack << newNode;

            }
            else if (c == ')')
            { // Handle closing parenthesis
                Node* poppedNode = nullptr;
                while (theStack.getHead() && theStack.getHead()->getPayload().getOperator() != '(')
                {
                    theStack >> poppedNode;
                    postfix_vector.push_back(string(1, poppedNode->getPayload().getOperator()));
                    delete poppedNode;
                }
                if (theStack.getHead() && theStack.getHead()->getPayload().getOperator() == '(')
                {
                theStack >> poppedNode;
                delete poppedNode;
                }

            }else
            { // Handle operators
                Data dataPoint;
                dataPoint.setOperator(c);
                Node* stack_cursor = new Node(dataPoint);
                // Repeatedly pop from the stack while the top has higher or equal precedence
                while (postfix(theStack, stack_cursor))
                {
                    Node* poppedNode = nullptr;
                    theStack >> poppedNode;
                    postfix_vector.push_back(string(1, poppedNode->getPayload().getOperator()));
                    delete poppedNode;
                }
                // Push the new operator onto the stack after all relevant pops
                theStack << stack_cursor;
            }

        }
        // Pop remaining operators from the stack and add to postfix_vector
        Node* poppedNode = nullptr;
        while (theStack.getHead())
        {
            theStack >> poppedNode;
            postfix_vector.push_back(string(1, poppedNode->getPayload().getOperator()));
            delete poppedNode;
        }
        // Convert vector to postfix expression string
        string postfix_expression;
        for (size_t i = 0; i < postfix_vector.size(); i++)
        {
            postfix_expression += postfix_vector[i];
            if (i < postfix_vector.size() - 1)
            {
                postfix_expression += " "; // Add a single space between elements
            }

        }
        // Evaluate the postfix expression
        double result = evaluatePostfix(postfix_expression, theStack);
        cout << fixed;
        cout << setprecision(3);
        cout << postfix_expression << result << endl;

    }
    return 0;
}


bool postfix(Stack& theStack, Node* poping_Node)
{
    // Grabbing the current head of stack
    Node *current = theStack.getHead();

    if (!current)
    {
        return false; // If stack is empty, just push
    }

    // Checking precedence between current operator and one being pushed
    char current_op = current->getPayload().getOperator();
    char new_op = poping_Node->getPayload().getOperator();

    double current_precedence = 0;
    double new_precedence = 0;

    if (current_op == '^') current_precedence = 3;
    else if (current_op == '*' || current_op == '/') current_precedence = 2;
    else if (current_op == '+' || current_op == '-') current_precedence = 1;

    if (new_op == '^') new_precedence = 3;
    else if (new_op == '*' || new_op == '/') new_precedence = 2;
    else if (new_op == '+' || new_op == '-') new_precedence = 1;

    if (current_precedence >= new_precedence)
    {
        return true; // Pop if current precedence is greater or equal
    }
    else
    {
        if (!theStack.getHead()) // If stack is empty, push automatically
        {
            return false;
        }
        else
        {
            return false; // Otherwise, push
        }
    }
}

double evaluatePostfix(const string& postfix_expression, Stack& stack)
{
    string Astring;
    double operand1, operand2, result;
    size_t i = 0;

    while (i < postfix_expression.length())
    {
        char c = postfix_expression[i];

        if (isdigit(c)) // If it's a digit, read the whole number
        {
            Astring.clear();
            while (i < postfix_expression.length() &&
                   (isdigit(postfix_expression[i]) || postfix_expression[i] == '.'))
            {
                Astring += postfix_expression[i];
                i++;
            }

            // Converting the Astring to a double and push onto the stack
            Data dataPoint;
            dataPoint.setOperand(stod(Astring));
            Node* newNode = new Node(dataPoint);
            stack << newNode; // Push onto the stack
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            // Pop two operands from the stack
            Node* node1 = nullptr;
            stack >> node1;
            operand2 = node1->getPayload().getOperand();

            Node* node2 = nullptr;
            stack >> node2;
            operand1 = node2->getPayload().getOperand();

            // Perform the operation and push the result back onto the stack
            switch (c)
            {
                case '^':
                    result = pow(operand1, operand2);
                    break;
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0)
                        throw runtime_error("Division by zero error");
                    result = operand1 / operand2;
                    break;
            }

            Data dataPoint;
            dataPoint.setOperand(result);
            Node* resultNode = new Node(dataPoint);
            stack << resultNode; // Push the result back onto the stack
        }

        // Move to the next character
        i++;
    }

    // The final result should be the only item left in the stack
    Node* finalNode = nullptr;
    stack >> finalNode;
    double finalResult = finalNode->getPayload().getOperand();

    return finalResult;
}
