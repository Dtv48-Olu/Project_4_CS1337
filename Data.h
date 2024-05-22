#ifndef DATA_H
#define DATA_H

class Data {
private:
    // Attributes
    double Operand;
    char Operator;

public:
    // Default Constructor
    Data() : Operand(0.0), Operator('\0') {}

    // Overloaded Constructors
    Data(double operand) : Operand(operand), Operator('\0') {}
    Data(char op) : Operand(0.0), Operator(op) {}

    // Accessors
    double getOperand() { return Operand; }
    char getOperator() { return Operator; }

    // Mutators
    void setOperand(double operand) { Operand = operand; }
    void setOperator(char op) { Operator = op; }
};

#endif // DATA_H
