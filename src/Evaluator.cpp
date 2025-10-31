//
// Created by 79835
//

#include "Evaluator.h"

#include <cmath>
#include <stack>
#include <stdexcept>

#include "ExpressionParser.h"
#include "FunctionRegistry.h"

double applyOp(const std::string& op, double a, double b) {
    if(op == "+") return a + b;
    if(op == "-") return a - b;
    if(op == "*") return a * b;
    if(op == "/") {
        if(b == 0) throw std::runtime_error("Division by zero");
        return a / b;
    }
    if(op == "^") return std::pow(a, b);
    throw std::runtime_error("Invalid operator: " + op);
}

double Evaluator::evaluate(const std::string& expression) {
    ExpressionParser parser;
    std::vector<std::string> tokens = parser.parse(expression);
    std::stack<double> stack;

    for (auto& token : tokens) {
        if (token.empty()) continue;

        if (std::isdigit(token[0]) || (token[0]=='.' && token.size() > 1) || (token[0]=='-' && token.size()>1 && std::isdigit(token[1]))) {
            stack.push(std::stod(token));
        }

        else if (token=="+"||token=="-"||token=="*"||token=="/"||token=="^") {
            if (stack.size() < 2 ) throw std::runtime_error("Not enough operands for operator");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(applyOp(token, a, b));
        }

        else {
            try {
                auto func = FunctionRegistry::getInstance().getFunction(token);
                if(stack.empty()) throw std::runtime_error("No argument for function: " + token);
                double arg = stack.top(); stack.pop();
                stack.push(func({arg}));
            } catch(const std::exception& e) {
                throw std::runtime_error("Function error [" + token + "]: " + e.what());
            }
        }

    }

    if (stack.size() != 1) throw std::runtime_error("Invalid expression");
    return stack.top();
}
