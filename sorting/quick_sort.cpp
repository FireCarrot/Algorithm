#include <iostream>
#include <vector>

using namespace std;

void swap(vector<int>& array, int index1, int index2) {
  int tmp = array[index1];
  array[index1] = array[index2];
  array[index2] = tmp;
}

int partitioning(vector<int>& array, int start, int end) {
  int pivot = array[end];
  int index = 0;

  for (int i = 0; i < end; i++) {
    if (array[i] < pivot) {
      swap(array, index, i);
      index++;
    }
  }

  swap(array, index, end);
  return index;
}

int rand_partitioning(vector<int>& array, int start, int end) {
  int random = start + rand()%(end-start + 1);

  swap(array, random, end); // swap pivot with last element.
  return partitioning(array, start, end);
}

void quicksort(vector<int>& array, int start, int end) {
  if (start < end) {
    int p = rand_partitioning(array, start, end);

    quicksort(array, start, p-1);
    quicksort(array, p+1, end);
  }
}

int main() {
  vector<int> unsorted_array = {4, 5, 1, 2, 3, 8, 10, 6, 9};

  int size = unsorted_array.size();

  quicksort(unsorted_array, 0, size-1);

  for (int v : unsorted_array)
    cout << v << " ";
}
