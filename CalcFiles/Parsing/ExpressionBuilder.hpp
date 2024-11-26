#include "../Expressions/Expression.hpp"
#include "../Tokens/Token.hpp"
#include <deque>

Expression buildExpressionFromPostfix(std::deque<Token> postfix);