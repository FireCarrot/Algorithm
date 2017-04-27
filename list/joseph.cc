// c : number of test case
// n : number of people
// k : suicide interval

#include <list>
#include <iterator>
#include <iostream>

using namespace std;

int main() {
  int c;
  cin >> c;

  while (c-- > 0) {
    int n, k;
    cin >> n >> k;

    list<int> List;
    for (int i = 1; i <= n; i++) {
      List.push_back(i);
    }

    list<int>::iterator it = List.begin();
    it = List.erase(it);
    int cnt = 0;
    while (true) {
        if (it == List.begin() && std::next(it) == List.end())
            break;

        if (it == List.end()) {
          it = List.begin();
          ++cnt;
        } else {
          it++;
        }

        ++cnt;

        if (cnt == k) {
          it = List.erase(it);
          if (it == List.end())
            it = List.begin();

          cnt = 1;
        }
    }

    cout << *List.begin() << ' ' << *List.end() << endl;
  }

  return 0;
}
