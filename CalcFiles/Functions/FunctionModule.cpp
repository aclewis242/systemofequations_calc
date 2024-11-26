#include "FunctionModule.hpp"
#include <unordered_map>

static std::unordered_map<std::string, Function> functionStrings
({
    {"+", Function::Add},
    {"<-", Function::AssignVariable},
    {"csc", Function::Cosecant},
    {"cot", Function::Cotangent},
    {"cos", Function::Cosine},
    {"/", Function::Divide},
    {"^", Function::Exponent},
    {"!", Function::Factorial},
    {"log", Function::Log},
    {"%", Function::Modulus},
    {"*", Function::Multiply},
    {"ln", Function::NaturalLogarithm},
    {"&-", Function::Negate},
    {"sec", Function::Secant},
    {"sin", Function::Sine},
    {"-", Function::Subtract},
    {"tan", Function::Tangent},
    {"sinh", Function::HyperSine},
	{"cosh", Function::HyperCosine},
	{"tanh", Function::HyperTangent},
	{"csch", Function::HyperCosecant},
	{"sech", Function::HyperSecant},
	{"coth", Function::HyperCotangent},
	{"arcsin", Function::Arcsine},
	{"arccos", Function::Arccosine},
	{"arctan", Function::Arctangent},
	{"arccsc", Function::Arccosecant},
	{"arcsec", Function::Arcsecant},
	{"arccot", Function::Arccotangent},
});

int precedence(Function func)
{
    switch (func)
    {
        case Function::AssignVariable:
            return -1;
        case Function::Add: case Function::Subtract:
            return 0;
        case Function::Multiply: case Function::Divide:
        case Function::Modulus:
            return 1;
        case Function::Exponent:
            return 2;
        default:
            return 3;
    }
}

int numberOfArguments(Function func)
{
    switch (func)
    {
        case Function::Identity:
            return 0;
        case Function::Add: case Function::Divide:
        case Function::Exponent: case Function::Multiply:
        case Function::Subtract: case Function::Log:
        case Function::AssignVariable: case Function::Modulus:
            return 2;
        default:
            return 1;
    }
}

bool leftAssociative(Function func)
{
    switch (func)
    {
        case Function::Exponent:
            return false;
        default:
            return true;
    }
}

Function stringToFunction(std::string input)
{
    auto findFunction = functionStrings.find(input);
    return (findFunction == functionStrings.end() ? Function::Identity : findFunction->second);
}
