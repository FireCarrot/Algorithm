#include <functional>
#include <iostream>

int foo() { return 5; }
int goo() { return 6; }

int main() {
    std::function<int()> fcnPtr;
    fcnPtr = goo;

    std::cout << fcnPtr();

    return 0;
}
