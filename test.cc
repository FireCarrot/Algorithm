#include <iostream>
#include <vector>
#include <memory>

using namespace std;

typedef unsigned short byte;

class Item {
public:
  Item(int v, string n) : value_(v), name_(n) {}
  int value_;
  string name_;
};

int get() {
    int v;
    cin >> v;
    return v;
}

void print(vector<Item*>& items) {
  for (Item* item : items) {
    cout << item->value_ << endl;
    cout << item->name_ << endl;
  }
}

int main() {
    vector<Item*> items;

    Item* del = new Item(5, "five");
    items.push_back(del);

    delete del;
    print(items);

    return 0;
}
