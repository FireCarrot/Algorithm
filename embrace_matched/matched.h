#include <iostream>
#include <string>
#include <stack>

using namespace std;

int get() {
  int v;
  cin >> v;
  return v;
}

bool wellMatched(string& formula) {
  const string opening("({[");
  const string closing(")}]");

  stack<char> openings;
  for (int i = 0; i < formula.size(); i++) {
    if (opening.find(formula[i]) != -1) {
      openings.push(formula[i]);
    } else {
      if (openings.empty()) return false;

      if (opening.find(openings.top()) != closing.find(formula[i]))
          return false;

      openings.pop();
    }
  }
  return openings.empty();
}
