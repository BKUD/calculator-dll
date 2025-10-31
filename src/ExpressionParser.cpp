//
// Created by 79835
//

#include "ExpressionParser.h"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cmath>

int precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool isOperator(const std:: string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" || token == "^";
}

std::vector<std::string> ExpressionParser::parse(const std::string& expr) {
    std::vector<std::string> output;
    std::stack<std::string> ops;
    size_t i = 0;

    while(i < expr.size()) {
        char c = expr[i];

        if(std::isspace(c)) { ++i; continue; }

        // число (поддержка отрицательных и с точкой)
        if(std::isdigit(c) || c == '.' || (c=='-' && i+1 < expr.size() && std::isdigit(expr[i+1]))) {
            std::string num;
            num += c;
            ++i;
            while(i < expr.size() && (std::isdigit(expr[i]) || expr[i]=='.')) {
                num += expr[i++];
            }
            output.push_back(num);
        }
        // оператор
        else if(isOperator(std::string(1, c))) {
            std::string op(1, c);
            while(!ops.empty() && precedence(ops.top()) >= precedence(op)) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(op);
            ++i;
        }
        // скобки
        else if(c=='(') { ops.push("("); ++i; }
        else if(c==')') {
            while(!ops.empty() && ops.top()!="(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if(ops.empty()) throw std::runtime_error("Mismatched parentheses");
            ops.pop(); // убрать "("
            ++i;
        }
        else {
            throw std::runtime_error(std::string("Unknown token: ") + c);
        }
    }

    while(!ops.empty()) {
        if(ops.top()=="(") throw std::runtime_error("Mismatched parentheses");
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

