#include "ExpressionModule.hpp"
#include <cmath>

Evaluator buildEvaluator(Function func)
{
    switch (func)
    {
        case Function::Add:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return evaluate(*toEvaluate.arguments[0], context) + evaluate(*toEvaluate.arguments[1], context);
            };
        case Function::AssignVariable:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                auto varName = toEvaluate.arguments[0]->value;
                auto answer = evaluate(*toEvaluate.arguments[1], context);
                context.setValue(varName, answer);
                return answer;
            };
        case Function::Cosecant:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1 / std::sin(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Cosine:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::cos(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Cotangent:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1 / std::tan(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Divide:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return evaluate(*toEvaluate.arguments[0], context) / evaluate(*toEvaluate.arguments[1], context);
            };      
        case Function::Exponent:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::pow(evaluate(*toEvaluate.arguments[0], context), evaluate(*toEvaluate.arguments[1], context));
            };
        case Function::Factorial:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                double result = 1;
                for (int i = evaluate(*toEvaluate.arguments[0], context); i > 0; i--)
                {
                    result *= i;
                }
                return result;
            };
        case Function::Identity:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                try
                {
                    auto savedValue = context.getValue(toEvaluate.value);
                    return savedValue;
                }
                catch(const std::exception & e)
                {
                    return std::strtod(toEvaluate.value.c_str(), nullptr);
                }
            };
        case Function::Log:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::log(evaluate(*toEvaluate.arguments[1], context)) / std::log(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Modulus:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return (double) ((int) evaluate(*toEvaluate.arguments[0], context) % (int) evaluate(*toEvaluate.arguments[1], context));
            };
        case Function::Multiply:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return evaluate(*toEvaluate.arguments[0], context) * evaluate(*toEvaluate.arguments[1], context);
            };
        case Function::NaturalLogarithm:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::log(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Negate:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return -1 * evaluate(*toEvaluate.arguments[0], context);
            };
        case Function::Secant:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1 / std::cos(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Sine:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::sin(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Subtract:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return evaluate(*toEvaluate.arguments[0], context) - evaluate(*toEvaluate.arguments[1], context);
            };
        case Function::Tangent:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::tan(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperSine:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::sinh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperCosine:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::cosh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperTangent:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return std::tanh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperCosecant:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/sinh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperSecant:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/cosh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::HyperCotangent:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/tanh(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arcsine:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return asin(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arccosine:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return acos(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arctangent:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return atan(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arccosecant:
            return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/asin(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arcsecant:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/acos(evaluate(*toEvaluate.arguments[0], context));
            };
        case Function::Arccotangent:
        	return [](Expression & toEvaluate, CalculatorContext & context)
            {
                return 1/atan(evaluate(*toEvaluate.arguments[0], context));
            };
        default:
            break;
    }
    return [](Expression & toEvaluate, CalculatorContext & context)
    {
        return 69.69;
    };
}

double evaluate(Expression & expression, CalculatorContext & context)
{
    Evaluator evaluator = buildEvaluator(expression.function);
    return evaluator(expression, context);
}