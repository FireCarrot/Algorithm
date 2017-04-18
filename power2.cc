#include <iostream>

using namespace std;

namespace {

int get() {
  int v;
  cin >> v;
  return v;
}

const char* check_power_of_two(int n) {
    return ( (n & (n-1)) == 0x0 ) ? "true":"false";
}

};

int main() {
  int n = get();
  cout << check_power_of_two(n) << endl;
  return 0;
}

