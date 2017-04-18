#include <functional>
#include <iostream>

using namespace std;

int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y;
}

int multiply(int x, int y) {
    return x * y;
}

int divide(int x, int y) {
    return x / y;
}

void calculator(int x, int y, function<int(int, int)> fcnPtr) {
    cout << fcnPtr(x, y) << endl;
}

int main() {
    int x, y;
    cout << "Enter numbers: " << endl;
    cin >> x >> y;

    cout << "Enter operator: +, -, x, / " << endl;
    char 
    calculator(x, y, add);
    calculator(x, y, subtract);
    calculator(x, y, multiply);
    calculator(x, y, divide);
}
