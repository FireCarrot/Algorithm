#include <iostream>

using namespace std;

namespace {

int get() {
  int v;
  cin >> v;
  return v;
}

const char* did_meet_in_the_future(int x1, int v1, int x2, int v2) {
    return (abs(x1-x2) % abs(v2 - v1) == 0) ? "true" : "false";
}

};

int main() {
  int x1 = get();
  int v1 = get();

  int x2 = get();
  int v2 = get();

  cout << did_meet_in_the_future(x1, v1, x2, v2) << endl;

  return 0;
}
