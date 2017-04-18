#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& array, int start, int mid, int end) {
  int ls = start;
  int rs = mid + 1;

  int index = 0;
  vector<int> temp_array;
  while (ls <= mid && rs <= end) {
    if (array[ls] > array[rs])
      index = rs++;
    else
      index = ls++;

    temp_array.push_back(array[index]);
  }

  while (ls <= mid) {
    temp_array.push_back(array[ls++]);
  }

  while (rs <= end) {
    temp_array.push_back(array[rs++]);
  }

  index = start;
  for (int v : temp_array) {
    array[index++] = v;
  }
}

void mergesort(vector<int>& array, int start, int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    mergesort(array, start, mid);
    mergesort(array, mid+1, end);

    merge(array, start, mid, end);
  }
}

int main() {
  vector<int> unsorted_array = {4, 5, 1, 2, 3, 8, 10, 6, 9};

  int size = unsorted_array.size();

  mergesort(unsorted_array, 0, size-1);

  for (int v : unsorted_array)
    cout << v << " ";
}
