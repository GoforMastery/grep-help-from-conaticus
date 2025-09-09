/*goal of patternParser:

To take the pattern string from the user.
eg: "[abc]\d", "foo\d", "[^a-z]"
we want to convet it to list of vector.
1. Digit
2. AlphaNumeric
3. Character
4. PositiveGroup
5. NegativeGroup


*/
#include "PatternToken.h"
#include <unordered_set>
#include <vector>
vector<PatternToken> parse(const string &pattern) {
  string p = pattern;
  size_t stIdx = 0;
  vector<PatternToken> store;
  size_t ps = p.size();
  while (stIdx < ps) {
    if (stIdx + 1 < ps && p[stIdx] == '[' && p[stIdx + 1] != '^') {
      unordered_set<char> positiveCharGroup;
      stIdx++;
      while (stIdx < ps && p[stIdx] != ']') {
        positiveCharGroup.insert(pattern[stIdx]);
        stIdx++;
      }
      /*pattern[stIdx] == ']'*/
      PatternToken tok;
      tok.type = PositiveGroup;
      tok.positiveCharGroup = positiveCharGroup;
      store.emplace_back(tok);
      stIdx++;
    } else if (stIdx + 1 < ps && p[stIdx] == '[' && p[stIdx + 1] == '^') {
      unordered_set<char> negativeCharGroup;
      stIdx += 2;
      while (stIdx < ps && p[stIdx] != ']') {
        negativeCharGroup.insert(p[stIdx]);
        stIdx++;
      }
      PatternToken tok;
      tok.type = NegativeGroup;
      tok.negativeCharGroup = negativeCharGroup;
      store.emplace_back(tok);
      stIdx++;
    } else if (stIdx + 1 < ps && p[stIdx] == '\\' && p[stIdx + 1] == 'd') {
      PatternToken tok;
      tok.type = Digit;
      store.emplace_back(tok);
      stIdx += 2;
    } else if (stIdx + 1 < ps && p[stIdx] == '\\' && p[stIdx + 1] == 'w') {
      PatternToken tok;
      tok.type = AlphaNumeric;
      store.emplace_back(tok);
      stIdx += 2;
    } else {
      PatternToken tok;
      tok.type = Character;
      tok.character = p[stIdx];
      store.emplace_back(tok);
      stIdx++;
    }
  }
  cout << "debug store " << "\n";
  for (auto t : store) {
    cout << t.character << "\n";
  }
  return store;
}
