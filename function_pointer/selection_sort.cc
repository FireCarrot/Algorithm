#include <algorithm>
#include <iostream>

using namespace std;

using validateFcn = bool(*)(int, int);

bool ascending(int x, int y) {
    return x > y;
}

bool descending(int x, int y) {
    return x < y;
}

bool evensFirst(int x, int y) {
    // if x is even and y is odd, x goes first (no swap needed)
    if ((x % 2 == 0) && !(y % 2 == 0))
        return false;

    if (!(x % 2 == 0) && (y % 2 == 0))
        return true;

    return ascending(x, y);
}

void printArray(int* array, int size) {
    for (int index=0; index < size; index++) {
        cout << array[index] << " ";
    }

    cout << endl;
}

void SelectionSort(int* array, int size, validateFcn pFcn = ascending) {
    for (int startIndex = 0; startIndex < size; startIndex++) {
        int bestIndex = startIndex;

        for (int currentIndex = startIndex + 1; currentIndex < size; currentIndex++) {
            if (pFcn(array[bestIndex], array[currentIndex]))
                bestIndex = currentIndex;
        }

        swap(array[bestIndex], array[startIndex]);
    }
}

int main() {
    int array[9] = { 3, 7, 9, 5, 6, 1, 8, 2, 4};
    int size = sizeof(array)/sizeof(array[0]);

    SelectionSort(array, size, descending);
    printArray(array, size);

    SelectionSort(array, size, ascending);
    printArray(array, size);

    SelectionSort(array, size, evensFirst);
    printArray(array, size);

    SelectionSort(array, size);
    printArray(array, size);
    return 0;
}
