#include <vector>
#include <stack>
#include <iostream>

using namespace std;
//          _
//        _| |
//      _| | |_
//    _| | | | |_
//  _| | | | | | |
// | | | | | | | |
// --------------------------------
int maximum_area(vector<int>& heights) {
  stack<int> min_heights;

  heights.push_back(0);  // set minimum height at right most.

  int ret = 0;

  for (int i = 0; i < heights.size(); i++) {
    while (!min_heights.empty() &&
           heights[min_heights.top()] >= heights[i]) {
      int j = min_heights.top();
      min_heights.pop();

      int width = -1;
      if (min_heights.empty())
        width = i;
      else
        width = i - min_heights.top() - 1;

      ret = max(ret, (width * heights[j]));
    }

    min_heights.push(i);
  }

  return ret;
}

int main() {
  vector<int> h = { 1, 2, 3, 4, 5, 3, 2};

  // calculate maximum_area that includes ith
  // time complexity O(n)
  cout << maximum_area(h) << endl;
}
