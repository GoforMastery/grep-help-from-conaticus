#include <bits/stdc++.h>
using namespace std;

enum TokenType {
  Digit,
  AlphaNumeric,
  Character,
  PositiveGroup,
  NegativeGroup,
};

struct PatternToken {
  TokenType type;
  char character = '\0';
  unordered_set<char> positiveCharGroup;
  unordered_set<char> negativeCharGroup;
};
