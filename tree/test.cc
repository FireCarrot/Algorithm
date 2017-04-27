#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> arr = { 1, 2};

  vector<int> tmp(arr.begin()+1, arr.end());
  for (int v : tmp) {
    cout << v << " ";
  }

  return 0;
}
