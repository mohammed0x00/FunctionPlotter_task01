#include "expressionParser.h"
#include <QDebug>
#include <string>
#include <cmath>

ExpressionParser::ExpressionParser()
{
    // Empty Constructor
}

ExpressionParser::ExpressionParser(const char * expressionString, size_t len)
{
    // Parse the parameter string
    parse(expressionString, len);
}

// Returns precedence of an operator
int ExpressionParser::getPrecedence(char symbol)
{
    switch(symbol) {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 2;
        break;
    case '^':
        return 3;
        break;
    }
    // Invalid Operator
    return 0;
}

// Check whether the symbol is an operator
bool ExpressionParser::isOperator(char symbol)
{
    switch(symbol) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
         return true;
         break;
      default:
         return false;
    }
}

// Check whether the symbol is a number?
bool ExpressionParser::isNumber(char symbol)
{
    if(symbol >= '0' && symbol <= '9') {
        return true;
    }
    // Dot symbol for decimal numbers
    else if(symbol == '.') {
        return true;
    }
    else {
        return false;
    }
}

// Check whether the symbol is a variable?
bool ExpressionParser::isVariable(char symbol)
{
    if(symbol == 'x' || symbol == 'X') {
        return true;
    }
    else {
        return false;
    }
}

void ExpressionParser::addOperatorToVector(char symbol)
{
    switch(symbol) {
    case '+':
        parsedExpressionVector.push_back({add, 0});
        break;
    case '-':
        parsedExpressionVector.push_back({subtract, 0});
        break;
    case '*':
        parsedExpressionVector.push_back({multiply, 0});
        break;
    case '/':
        parsedExpressionVector.push_back({divide, 0});
        break;
    case '^':
        parsedExpressionVector.push_back({power, 0});
        break;
    }
}

void ExpressionParser::parse(const char * expressionString, size_t len)
{
    size_t i = 0;
    switch(expressionString[0]) {
    case '+':
    case '-':
        // Push value 0 to the vector if your expression starts with a negative number
        parsedExpressionVector.push_back({constant, 0});
        break;
    default:
        break;
    }

    while(i < len) {
        std::string temp = "";
        double tempNumber;
        if(isVariable(expressionString[i])) {
            parsedExpressionVector.push_back({var, 0});
            i++;
        }
        else if(isOperator(expressionString[i])){
            if(charactersStack.empty()) {
                charactersStack.push(expressionString[i]);
            }
            else if(getPrecedence(expressionString[i]) > getPrecedence(charactersStack.top())) {
                charactersStack.push(expressionString[i]);
            }
            else {
                while(getPrecedence(expressionString[i]) <= getPrecedence(charactersStack.top())) {
                    addOperatorToVector(charactersStack.top());
                    charactersStack.pop();
                    if(charactersStack.empty())
                    {
                        break;
                    }
                }
                charactersStack.push(expressionString[i]);
            }

            i++;
        }
        else if(isNumber(expressionString[i])) {
            do {
                temp += expressionString[i];
                i++;
            } while(isNumber(expressionString[i]));

            tempNumber = stod(temp);
            parsedExpressionVector.push_back({constant, tempNumber});
        }
    }

    while (!charactersStack.empty()) {
        addOperatorToVector(charactersStack.top());
        charactersStack.pop();
    }
}

double ExpressionParser::calculate(double x)
{
    double parameter1, parameter2;
    std::stack<double> temp;

    for(size_t i = 0; i < parsedExpressionVector.size(); i++) {
        switch(parsedExpressionVector[i].type)
        {
        case add:
            parameter2 = temp.top();
            temp.pop();
            parameter1 = temp.top();
            temp.pop();
            temp.push(parameter1 + parameter2);
            break;
        case subtract:
            parameter2 = temp.top();
            temp.pop();
            parameter1 = temp.top();
            temp.pop();
            temp.push(parameter1 - parameter2);
            break;
        case multiply:
            parameter2 = temp.top();
            temp.pop();
            parameter1 = temp.top();
            temp.pop();
            temp.push(parameter1 * parameter2);
            break;
        case divide:
            parameter2 = temp.top();
            temp.pop();
            parameter1 = temp.top();
            temp.pop();
            temp.push(parameter1 / parameter2);
            break;
        case power:
            parameter2 = temp.top();
            temp.pop();
            parameter1 = temp.top();
            temp.pop();
            temp.push(pow(parameter1, parameter2));
            break;
        case constant:
            temp.push(parsedExpressionVector[i].value);
            break;
        case var:
            temp.push(x);
            break;
        default:
            break;
        }
    }
    return temp.top();
}
