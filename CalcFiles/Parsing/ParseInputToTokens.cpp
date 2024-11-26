#include "TokenParser.hpp"
#include "../Functions/FunctionModule.hpp"
#include <cstring>
#include <sstream>

deque<string> unparsedInputToStringList(string input)
{
    char delimiter = ' ';
    stringstream inputStream(input);

    string segment;
    deque<string> result;

    while (getline(inputStream, segment, delimiter))
    {
        result.push_back(segment);
    }

    return result;
}

TokenType stringToTokenType(string single)
{
    if (single == "(")
    {
        return TokenType::LeftParenthesis;
    }
    else if (single == ")")
    {
        return TokenType::RightParenthesis;
    }
    else if (stringToFunction(single) != Function::Identity)
    {
        return TokenType::Function;
    }

    return TokenType::Literal;
}

Token tokenizeSingle(string single)
{
    TokenType tokenType = stringToTokenType(single);
    Function function = stringToFunction(single);
    return Token(single, tokenType, function);
}

string fixNegative(deque<string> & stringList, int index, string single)
{
    if (single != "-")
    {
        return single;
    }
    if (index == 0)
    {
        return "&-";
    }
    else if ( stringList.at(index - 1) == "("
        || stringToFunction(stringList.at(index - 1)) == Function::Add
        || stringToFunction(stringList.at(index - 1)) == Function::Divide
        || stringToFunction(stringList.at(index - 1)) == Function::Modulus
        || stringToFunction(stringList.at(index - 1)) == Function::Multiply
        || stringToFunction(stringList.at(index - 1)) == Function::Subtract)
    {
        return "&-";
    }
    return single;
}

deque<Token> stringListToInfixTokenList(deque<string> stringList)
{
    deque<Token> result;
    for (int i = 0; i < stringList.size(); i++)
    {
        string single = fixNegative(stringList, i, stringList.at(i));
        result.push_back(tokenizeSingle(single));
    }
    return result;
}

deque<Token> parse(string input)
{
    return stringListToInfixTokenList(unparsedInputToStringList(input));
}
