#include "tree.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

/*uint64_t RandBytes(void* output, size_t output_length) {
  const int urandom_fd = g_urandom_fd.Pointer()->fd();
}

uint64_t RandUInt64() {
  uint64_t number;
  RandBytes(&number, sizeof(number));
  return number;
}

uint64_t RandGenerator(uint64_t range) {
  uint64_t max_acceptable_value =
      (std::numberic_limits<uint64_t>::max() / range) * range - 1;

  uint64_t value;
  do {
    value = RandUInt64();
  } while (value > max_acceptable_value);

  return value % range;
}

int RandInt(int min, int max) {
  uint64_t range = static_cast<uint64_t>(max) - min + 1;

  int result =
      static_cast<int>(min + static_cast<int64_t>(RandGenerator(range)));
  return result;
}*/

int main() {
  vector<int> input;
  input.reserve(10);

  cout << "Input value: ";
  for (int i = 0; i < 10; i++) {
    int r = rand()%100;
    cout << r << " ";
    input.push_back(r);
  }
  cout << endl;

  Tree tree;
  for (int v : input) {
    tree.insert(v);
  }

  cout << "InOrder: ";
  tree.traverse(Tree::TraverseType::InOrder);
  cout << endl;

  cout << "PreOrder: ";
  tree.traverse(Tree::TraverseType::PreOrder);
  cout << endl;

  cout << "PostOrder: ";
  tree.traverse(Tree::TraverseType::PostOrder);
  cout << endl;

  cout << "LevelOrder: ";
  tree.traverse(Tree::TraverseType::LevelOrder);
  cout << endl;
}
