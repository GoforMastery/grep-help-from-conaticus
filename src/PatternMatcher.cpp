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
  if (input.empty()) {
    return false;
  }
  /*goal is to match all the tokens. */
  size_t tokenIdx = 0;
  bool justFromStart = false, justFromBack = false;
  if (tokens[tokenIdx].character == '^') {
    justFromStart = true;
  }
  if (tokens.back().character == '$') {
    justFromBack = true;
  }
  if (justFromBack && justFromStart) {
    if (tokens.size() - 2 != input.size()) {
      return false;
    }
    int tokenIdx = tokens.size() - 2, k = input.size() - 1;
    while (k >= 0 && tokenIdx >= 1 && tokens[tokenIdx].character == input[k]) {
      k--, tokenIdx--;
    }
    return tokenIdx == 0;
  }
  if (justFromStart) {
    int k = 0, tokenIdx = 1;
    while (tokenIdx < tokens.size() && tokens[tokenIdx].character == input[k]) {
      k++, tokenIdx++;
    }
    return tokenIdx == tokens.size();
  }
  if (justFromBack) {
    int k = input.size() - 1, tokenIdx = tokens.size() - 2;
    while (k >= 0 && tokenIdx >= 0 && tokens[tokenIdx].character == input[k]) {
      k--, tokenIdx--;
    }
    return tokenIdx == -1;
  }
  if (!justFromStart && !justFromBack) {
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
      /*if no match start checking again. */
    }
  }
  return tokenIdx == tokens.size();
}
