#pragma once

#include <unordered_map>
#include <string>

class CalculatorContext
{
    public:
        CalculatorContext();

        void setValue(std::string name, double value);
        double getValue(std::string name);
    private:
        std::unordered_map<std::string, double> savedValues;
};