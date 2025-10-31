//
// Created by 79835
//

#include "../include/ExpressionParser.h"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cmath>

#include "../include/FunctionRegistry.h"

int precedence(const std::string& op) {
    if(op == "+" || op == "-") return 1;
    if(op == "*" || op == "/") return 2;
    return 0;
}

static bool isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool isLeftAssociative(const std::string& op) {
    return op != "^";
}

std::vector<std::string> ExpressionParser::parse(const std::string& expression) {
    std::vector<std::string> output;
    std::stack<std::string> ops;
    size_t i = 0;

    while(i < expression.size()) {
        char c = expression[i];

        if(std::isspace(c)) { ++i; continue; }

        // числа
        if(std::isdigit(c) || c == '.' ||
           (c == '-' && (i==0 || expression[i-1]=='(') && i+1<expression.size() && std::isdigit(expression[i+1]))) {
            std::string num;
            num += c; ++i;
            while(i<expression.size() && (std::isdigit(expression[i]) || expression[i]=='.')) num += expression[i++];
            output.push_back(num);
        }

        // функции
        else if(std::isalpha(c)) {
            std::string name;
            name += c; ++i;
            while(i<expression.size() && std::isalpha(expression[i])) name += expression[i++];
            if(FunctionRegistry::getInstance().hasFunction(name))
                ops.push(name);
            else throw std::runtime_error("Unknown function: " + name);
        }

        // операторы
        else if(isOperator(std::string(1, c))) {
            std::string op(1, c);
            while(!ops.empty() && isOperator(ops.top()) &&
                  ((isLeftAssociative(op) && precedence(op) <= precedence(ops.top())) ||
                   (!isLeftAssociative(op) && precedence(op) < precedence(ops.top())))) {
                output.push_back(ops.top()); ops.pop();
            }
            ops.push(op); ++i;
        }

        // скобки
        else if(c=='(') { ops.push("("); ++i; }
        else if(c==')') {
            while(!ops.empty() && ops.top()!="(") { output.push_back(ops.top()); ops.pop(); }
            if(ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop();
            if(!ops.empty() && FunctionRegistry::getInstance().hasFunction(ops.top())) {
                output.push_back(ops.top()); ops.pop();
            }
            ++i;
        }

        // запятая
        else if(c==',') {
            while(!ops.empty() && ops.top()!="(") { output.push_back(ops.top()); ops.pop(); }
            ++i;
        }

        else throw std::runtime_error(std::string("Unknown token: ") + c);
    }

    while(!ops.empty()) {
        if(ops.top()=="(" || ops.top()==")") throw std::runtime_error("Mismatched parentheses");
        output.push_back(ops.top()); ops.pop();
    }

    return output;
}

