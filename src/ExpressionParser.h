//
// Created by 79835
//

#ifndef CALCULATOR_EXPRESSIONPARSER_H
#define CALCULATOR_EXPRESSIONPARSER_H

#endif //CALCULATOR_EXPRESSIONPARSER_H

#pragma once
#include <string>
#include <vector>

class ExpressionParser {
public:
    explicit ExpressionParser() = default;
    std::vector<std::string> parse(const std::string& expression);
};
