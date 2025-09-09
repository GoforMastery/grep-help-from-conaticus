#include "PatternToken.h"
#include <iostream>
#include <string>

using namespace std;

bool MatchToken(const char &ch, const PatternToken &token) {
  if (token.type == Digit) {
    return isdigit(ch);
  } else if (token.type == AlphaNumeric) {
    return isalnum(ch) or ch == '_';
  } else if (token.type == Character) {
    return ch == token.character;
  } else if (token.type == PositiveGroup) {
    return token.positiveCharGroup.find(ch) != token.positiveCharGroup.end();
  } else if (token.type == NegativeGroup) {
    return token.negativeCharGroup.find(ch) == token.negativeCharGroup.end();
  }
  return false;
}

bool Match(const string &input, const vector<PatternToken> &tokens) {
  if (input.size() == 0) {
    return false;
  }
  /*goal is to match all the tokens. */
  size_t tokenIdx = 0;
  size_t charIdx = 0;
  for (const char ch : input) {
    if (tokenIdx == tokens.size()) {
      return true;
    }
    auto currentToken = tokens[tokenIdx];
    if (MatchToken(ch, currentToken)) {
      tokenIdx++;
    } else {
      tokenIdx = 0;
    }
    charIdx++;
    /*if no match start checking again. */
  }
  return tokenIdx == tokens.size();
}
