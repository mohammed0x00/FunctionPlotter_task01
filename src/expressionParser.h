#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H
#include <stack>
#include <vector>

#define DEFAULT_NUMBER_OF_POINTS    100

class ExpressionParser
{
public:
    ExpressionParser();
    ExpressionParser(const char * expressionString, size_t len);

    //check whether the symbol is an operator
    static bool isOperator(char symbol);

    //check whether the symbol is an number
    static bool isNumber(char symbol);

    //check whether the symbol is an variable
    static bool isVariable(char symbol);

    // Parse the expression string
    void parse(const char expressionString[], size_t len);

    // Calculate F(x)
    double calculate(double x);

private:
    // Enum that represent the type of the node (variable, constant, operation)
    enum Node_Type {constant, var, add, subtract, multiply, divide, power};

    // Represent a variable, constant or operation
    typedef struct node_struct {
        Node_Type type;
        double value;
    } Node;

    // Vector to store the result of parsed string
    std::vector<Node> parsedExpressionVector;

    // Temperory stack used during parsing
    std::stack<char> charactersStack;

    // Returns precedence of an operator
    int getPrecedence(char symbol);

    void addOperatorToVector(char symbol);

};

#endif // EXPRESSIONPARSER_H
