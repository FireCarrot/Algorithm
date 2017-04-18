#include <iostream>
#include <stack>

using namespace std;

int main() {
    int base = 2;
    int x;

    int power = 0;

    cin >> x;

    if (x < base) {
        cout << "0";
    }

    stack<int> binary;
    while (x) {
        binary.push(x & 0x01);
        x = x >> 1;
    }

    cout << binary.size() - 1;

    while (!binary.empty()) {
        cout << binary.top();
        binary.pop();
    }

/*    while (x%base == 0) {
       power++;
       x = x/base;
    }*/

//    cout << power;

    return 0;
}
