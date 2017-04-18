#include <iostream>

using namespace std;
class Person {
public:
    Person(int initialAge) {
        if (initialAge < 0) {
            age = 0;
            cout << "Age is not valid, setting age to 0." << endl;
        } else {
            age = initialAge;
        }
    }

    int yearPasses() { age++; }
    void amIOld() {
        if (age < 12) {
            cout << "You are young..";
        } else if (age >= 13 && age < 18) {
            cout << "You are a teenager..";
        } else {
            cout << "You are old..";
        }

        cout << endl;
    }
private:
    int age = 0;
};

int main() {
    return 0;
}
