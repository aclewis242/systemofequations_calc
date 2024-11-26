#pragma once

#include "../Tokens/Token.hpp"
#include <deque>

using namespace std;

/* Returns an infix list of Tokens based on a raw, unparsed, space separated input */
deque<Token> parse(string input);

/* Returns a postfix list of Tokens based on an infix list of Tokens.
 * Removes parenthesis, etc.
 */
deque<Token> infixToPostfix(deque<Token> infix);