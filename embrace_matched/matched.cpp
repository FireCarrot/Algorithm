#include "matched.h"

int main() {
  int n = get();

  for (int i = 0; i < n; i++) {
    string input;
    cin >> input;
    if (wellMatched(input)) cout << "YES" << endl;
    else cout << "NO" << endl;
  }

  return 0;
}
