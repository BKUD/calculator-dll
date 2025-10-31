//
// Created by 79835
//

#include "Evaluator.h"

#include <cmath>
#include <stack>
#include <stdexcept>

#include "ExpressionParser.h"
#include "FunctionRegistry.h"



static bool isOperator(const std::string& token) {
    return token=="+"||token=="-"||token=="*"||token=="/";
}

double applyOperator(double a, double b, const std::string& op) {
    if(op=="+") return a+b;
    if(op=="-") return a-b;
    if(op=="*") return a*b;
    if(op=="/") {
        if(b==0) throw std::runtime_error("Division by zero");
        return a/b;
    }
    throw std::runtime_error("Unknown operator: "+op);
}

double Evaluator::evaluate(const std::string& expr) {
    ExpressionParser parser;
    auto tokens = parser.parse(expr);
    std::stack<double> st;

    for(const auto& token: tokens) {
        if(std::isdigit(token[0]) || (token.size()>1 && std::isdigit(token[1]))) {
            st.push(std::stod(token));
        }
        else if(isOperator(token)) {
            if(st.size()<2) throw std::runtime_error("Not enough operands");
            double b=st.top(); st.pop();
            double a=st.top(); st.pop();
            st.push(applyOperator(a,b,token));
        }
        else if(FunctionRegistry::getInstance().hasFunction(token)) {
            int argc = FunctionRegistry::getInstance().getArgCount(token);
            if(st.size()<argc) throw std::runtime_error("Not enough arguments for function "+token);

            std::vector<double> args(argc);
            for(int i=argc-1;i>=0;--i){ args[i]=st.top(); st.pop(); }

            try {
                double res = FunctionRegistry::getInstance().getFunction(token)(args);
                st.push(res);
            } catch(const std::exception& e) {
                throw std::runtime_error(std::string("Error in plugin function: ") + e.what());
            }
        }
        else throw std::runtime_error("Unknown token: "+token);
    }

    if(st.size()!=1) throw std::runtime_error("Invalid expression");
    return st.top();
}