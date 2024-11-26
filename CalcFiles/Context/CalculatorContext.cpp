#include "CalculatorContext.hpp"
#include <iostream>
#include "math.h"

CalculatorContext::CalculatorContext()
{
    // initialize constants
    setValue("e", M_E);
    setValue("pi", M_PI);
}

void CalculatorContext::setValue(std::string name, double value)
{
    savedValues[name] = value;
}

double CalculatorContext::getValue(std::string name)
{
    return savedValues.at(name);
}